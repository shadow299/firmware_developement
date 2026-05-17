#include "i2c.h"
#include "../gpio/gpio.h"

void i2c_init(void)
{
    // enable I2C1 clock
    RCC_APB1ENR |=
        (1 << I2C1_EN_BIT);

    // configure pins
    // PB6 -> SCL
    // PB7 -> SDA
    gpio_init(
        6,
        'B',
        GPIO_MODE_AF_OPENDRAIN);

    gpio_init(
        7,
        'B',
        GPIO_MODE_AF_OPENDRAIN);

    // disable peripheral before config
    I2C1_CR1 &= ~(1 << I2C_CR1_PE);

    /*
    CR2
    APB1 clock frequency in MHz

    APB1 = 8 MHz
    */
    I2C1_CR2 = 8;

    /*
    Standard mode (100kHz)

    CCR = Fpclk1 / (2 * Fscl)

    CCR = 8MHz / (2 * 100kHz)
        = 40
    */
    I2C1_CCR = 40;

    /*
    TRISE

    max rise time =
    Fpclk + 1

    = 8 + 1
    */
    I2C1_TRISE = 9;

    // enable I2C peripheral
    I2C1_CR1 |=
        (1 << I2C_CR1_PE);
}

void i2c_start(void)
{
    // generate START condition
    I2C1_CR1 |=
        (1 << I2C_CR1_START);

    // wait until START generated
    while (!(I2C1_SR1 &
             (1 << I2C_SR1_SB)))
        ;

    /*
    SB flag cleared by:
    1. reading SR1
    2. writing DR
    */
}

void i2c_send_address(uint8_t address, uint8_t read)
{
    uint8_t addr;

    /*
    I2C address format:

    bit7:1 -> address
    bit0   -> R/W
    */

    addr =
        (address << 1);

    if (read)
    {
        addr |= 1;
    }

    // write address to DR
    I2C1_DR = addr;

    // wait for address ACK
    while (!(I2C1_SR1 &
             (1 << I2C_SR1_ADDR)))
        ;

    /*
    Clear ADDR flag

    Required sequence:
    read SR1
    read SR2
    */

    volatile uint32_t temp;

    temp = I2C1_SR1;
    temp = I2C1_SR2;

    (void)temp;
}

void i2c_write_byte(
    uint8_t data)
{
    // write byte
    I2C1_DR = data;

    // wait until data register empty
    while (!(I2C1_SR1 &
             (1 << I2C_SR1_TXE)))
        ;

    /*
    optional:
    wait byte transfer finished
    safer for STM32
    */
    while (!(I2C1_SR1 &
             (1 << I2C_SR1_BTF)))
        ;
}

void i2c_stop(void)
{
    // generate STOP condition
    I2C1_CR1 |=
        (1 << I2C_CR1_STOP);
}

uint8_t i2c_read_nack(void)
{
    // disable ACK
    I2C1_CR1 &=
        ~(1 << I2C_CR1_ACK);

    // wait until data received
    while (!(I2C1_SR1 &
             (1 << I2C_SR1_RXNE)))
        ;

    // return received byte
    return (uint8_t)I2C1_DR;
}

uint8_t i2c_bmp280_read_register(
    uint8_t reg)
{
    uint8_t data;

    // START
    i2c_start();

    // send device address
    // write mode
    i2c_send_address(
        BMP280_ADDR,
        0);

    // send register address
    i2c_write_byte(reg);

    // repeated START
    i2c_start();

    // send address
    // read mode
    i2c_send_address(
        BMP280_ADDR,
        1);

    // read byte
    data =
        i2c_read_nack();

    // STOP
    i2c_stop();

    return data;
}