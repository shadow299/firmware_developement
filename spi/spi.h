#include <stdint.h>

#define SPI1_BASE 0x40013000

#define SPI1_RCC_BASE 0x40021000
#define SPI1_RCC_APB2ENR (*(volatile uint32_t *)(SPI1_RCC_BASE + 0x18))
#define SPI1_RCC_APB2ENR_OFFSET 0x18
#define SPI1_EN_BIT 12

// spi requires gpio pins to function. on blue pill, spi1 uses PA5 (SCK), PA6 (MISO), PA7 (MOSI)

/*
SPI master
manual chip select
slow speed
BMP280 compatible
*/

#define SPI1_CR1 *((volatile uint32_t *)(SPI1_BASE + 0x00))
#define SPI1_CR2 *((volatile uint32_t *)(SPI1_BASE + 0x04))
#define SPI1_SR *((volatile uint32_t *)(SPI1_BASE + 0x08))
#define SPI1_DR *((volatile uint32_t *)(SPI1_BASE + 0x0C))

// bit definitions for SPI_CR1
#define SPI_CR1_MSTR_BIT 2
#define SPI_CR1_SPE_BIT 6
#define SPI_CR1_BR_BITS 3 // bits 5:3 for baud rate control
#define SPI1_CR1_SSM_BIT 9
#define SPI1_CR1_SSI_BIT 8

// bit definitions for SPI_SR
#define SPI_SR_TXE_BIT 1
#define SPI_SR_BSY_BIT 7
#define SPI_SR_RXNE_BIT 0

void spi_init(void);
uint8_t spi_transfer(uint8_t data);
void spi_send(uint8_t data);
uint8_t spi_receive(void);

// BMP280 specific functions
uint8_t bmp280_read_register(uint8_t reg);
void bmp280_write_register(uint8_t reg, uint8_t value);
