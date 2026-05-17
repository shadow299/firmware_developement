#include <stdint.h>

#define I2C1_RCC_BASE 0x40021000
#define I2C1_BASE 0x40005400
// use APB1 clock
#define I2C1_EN_BIT 21

#define RCC_APB1ENR *((volatile uint32_t *)(I2C1_RCC_BASE + 0x1C))

// I2C registers
#define I2C1_CR1 \
    (*(volatile uint32_t *)(I2C1_BASE + 0x00))

#define I2C1_CR2 \
    (*(volatile uint32_t *)(I2C1_BASE + 0x04))

#define I2C1_OAR1 \
    (*(volatile uint32_t *)(I2C1_BASE + 0x08))

#define I2C1_DR \
    (*(volatile uint32_t *)(I2C1_BASE + 0x10))

#define I2C1_SR1 \
    (*(volatile uint32_t *)(I2C1_BASE + 0x14))

#define I2C1_SR2 \
    (*(volatile uint32_t *)(I2C1_BASE + 0x18))

#define I2C1_CCR \
    (*(volatile uint32_t *)(I2C1_BASE + 0x1C))

#define I2C1_TRISE \
    (*(volatile uint32_t *)(I2C1_BASE + 0x20))

// CR1 bits
#define I2C_CR1_PE 0
#define I2C_CR1_START 8
#define I2C_CR1_STOP 9
#define I2C_CR1_ACK 10

// SR1 bits
#define I2C_SR1_SB 0
#define I2C_SR1_ADDR 1
#define I2C_SR1_BTF 2
#define I2C_SR1_RXNE 6
#define I2C_SR1_TXE 7

// SR2 bits
#define I2C_SR2_BUSY 1

#define BMP280_ADDR 0x76

void i2c_init(void);
void i2c_start(void);
void i2c_send_address(uint8_t address, uint8_t read);
void i2c_write_byte(uint8_t data);
void i2c_stop(void);
uint8_t i2c_read_nack(void);

// BMP280 specific registers
uint8_t i2c_bmp280_read_register(uint8_t reg);
