#include "../gpio/gpio.h"
#include "spi.h"
#include "../core/core.h"

void spi_init(void)
{
    // enable clock for spi1
    SPI1_RCC_APB2ENR |= (1 << SPI1_EN_BIT);

    // configure gpio pins for spi1
    gpio_init(5, 'A', GPIO_MODE_AF_PUSHPULL);     // PA5 - SCK
    gpio_init(6, 'A', GPIO_MODE_INPUT);           // PA6 - MISO
    gpio_init(7, 'A', GPIO_MODE_AF_PUSHPULL);     // PA7 - MOSI
    gpio_init(4, 'A', GPIO_MODE_OUTPUT_PUSHPULL); // PA4 - CS

    // set cs pin high (inactive)
    gpio_toggle_pin(4, 1, 'A');

    // configure spi1
    SPI1_CR1 |= (1 << SPI_CR1_MSTR_BIT);    // set master mode
    SPI1_CR1 |= (0b101 << SPI_CR1_BR_BITS); // set baud rate to fPCLK/64 (slow speed for bmp280)
    SPI1_CR1 |= (1 << SPI1_CR1_SSM_BIT);    // enable software slave management
    SPI1_CR1 |= (1 << SPI1_CR1_SSI_BIT);    // set internal slave select to avoid mode fault
    SPI1_CR1 |= (1 << SPI_CR1_SPE_BIT);     // enable spi
}

uint8_t spi_transfer(uint8_t data)
{
    // wait until transmit buffer empty
    while (!(SPI1_SR & (1 << SPI_SR_TXE_BIT)))
        ;

    // send byte
    SPI1_DR = data;

    // wait until receive buffer not empty
    while (!(SPI1_SR & (1 << SPI_SR_RXNE_BIT)))
        ;

    // wait until SPI finished shifting bits
    while (SPI1_SR & (1 << SPI_SR_BSY_BIT))
        ;

    // return received byte
    return (uint8_t)SPI1_DR;
}

void spi_send(uint8_t data)
{
    spi_transfer(data);
}

uint8_t spi_receive(void)
{
    return spi_transfer(0x00);
}

// BMP280 specific functions
uint8_t bmp280_read_register(uint8_t reg)
{
    uint8_t data;
    gpio_toggle_pin(4, 0, 'A'); // cs low
    spi_send(reg | 0x80);
    data = spi_receive();
    gpio_toggle_pin(4, 1, 'A'); // cs pin high
    return data;
}

void bmp280_write_register(uint8_t reg, uint8_t value)
{
    // set chip select high
    gpio_toggle_pin(4, 0, 'A');

    // set register for write
    spi_send(reg & 0x7F); // set 7th bit 0 to enable write 0x7F = 01111111

    // send value
    spi_send(value);

    // set cs high
    gpio_toggle_pin(4, 1, 'A');
}

// RC522 specific functions
void rc522_spi_init()
{
    // enable clock for spi1
    SPI1_RCC_APB2ENR |= (1 << SPI1_EN_BIT);

    // configure gpio pins for spi1
    gpio_init(5, 'A', GPIO_MODE_AF_PUSHPULL);     // PA5 - SCK
    gpio_init(6, 'A', GPIO_MODE_INPUT);           // PA6 - MISO
    gpio_init(7, 'A', GPIO_MODE_AF_PUSHPULL);     // PA7 - MOSI
    gpio_init(4, 'A', GPIO_MODE_OUTPUT_PUSHPULL); // PA4 - CS
    gpio_init(3, 'A', GPIO_MODE_OUTPUT_PUSHPULL); // PA3 - RST

    // configure spi1
    SPI1_CR1 = 0;
    SPI1_CR1 |= (1 << SPI_CR1_MSTR_BIT);     // set master mode
    SPI1_CR1 &= ~(0b001 << SPI_CR1_BR_BITS); // set baud rate to fPCLK/2 (fast speed for rc522)
    SPI1_CR1 |= (0b001 << SPI_CR1_BR_BITS);  // set baud rate to fPCLK/256 (slow speed for rc522)
    SPI1_CR1 |= (1 << SPI1_CR1_SSM_BIT);     // enable software slave management
    SPI1_CR1 |= (1 << SPI1_CR1_SSI_BIT);     // set internal slave select to avoid mode fault
    SPI1_CR1 &= ~(1 << SPI1_CR1_CPOL_BIT);   // set clock polarity to 0
    SPI1_CR1 &= ~(1 << SPI1_CR1_CPHA_BIT);   // set clock phase to 0
    SPI1_CR1 |= (1 << SPI_CR1_SPE_BIT);      // enable spi

    // set cs and rst pin high (inactive)
    gpio_toggle_pin(4, 1, 'A');

    // hard reset the rc522
    gpio_toggle_pin(3, 0, 'A');
    delay_ms(50);
    gpio_toggle_pin(3, 1, 'A');
    delay_ms(50);
    rc522_write_register(0x01, 0x0F); // set timer to 6.78ms
    delay_ms(50);
}

uint8_t rc522_read_register(uint8_t reg)
{
    uint8_t value;
    gpio_toggle_pin(4, 0, 'A'); // cs low
    spi_transfer(((reg << 1) & 0x7E) | 0x80);
    value = spi_transfer(0x00);
    delay_ms(1);
    gpio_toggle_pin(4, 1, 'A');
    return value;
}

void rc522_write_register(uint8_t reg, uint8_t value)
{
    gpio_toggle_pin(4, 0, 'A'); // cs low
    spi_send(reg << 1);
    spi_send(value);
    gpio_toggle_pin(4, 1, 'A');
}