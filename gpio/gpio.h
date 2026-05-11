#include <stdint.h>

// gpio register base definitions
#define GPIOA_BASE 0x40010800
#define GPIOB_BASE 0x40010C00
#define GPIOC_BASE 0x40011000

// rcc register base definitions
#define RCC_BASE 0x40021000
#define ABP2ENR_OFFSET 0x18
#define RCC_ABP2ENR (*(volatile uint32_t *)(RCC_BASE + ABP2ENR_OFFSET))

// gpio register offsets in RCC
#define RCC_APB2ENR_IOPAEN (1 << 2) // IO port A clock enable
#define RCC_APB2ENR_IOPBEN (1 << 3) // IO port B clock enable
#define RCC_APB2ENR_IOPCEN (1 << 4) // IO port C clock enable

#define GPIOx_CRL 0x00 // 0 to 7 pins, total 8
#define GPIOx_CRH 0x04 // 8 to 15 pin, total 8
#define GPIOx_IDR 0x08
#define GPIOx_ODR 0x0C

#define GPIOA_CRL (*(volatile uint32_t *)(GPIOA_BASE + GPIOx_CRL))
#define GPIOA_CRH (*(volatile uint32_t *)(GPIOA_BASE + GPIOx_CRH))
#define GPIOA_IDR (*(volatile uint32_t *)(GPIOA_BASE + GPIOx_IDR))
#define GPIOA_ODR (*(volatile uint32_t *)(GPIOA_BASE + GPIOx_ODR))

#define GPIOB_CRL (*(volatile uint32_t *)(GPIOB_BASE + GPIOx_CRL))
#define GPIOB_CRH (*(volatile uint32_t *)(GPIOB_BASE + GPIOx_CRH))
#define GPIOB_IDR (*(volatile uint32_t *)(GPIOB_BASE + GPIOx_IDR))
#define GPIOB_ODR (*(volatile uint32_t *)(GPIOB_BASE + GPIOx_ODR))

#define GPIOC_CRL (*(volatile uint32_t *)(GPIOC_BASE + GPIOx_CRL))
#define GPIOC_CRH (*(volatile uint32_t *)(GPIOC_BASE + GPIOx_CRH))
#define GPIOC_IDR (*(volatile uint32_t *)(GPIOC_BASE + GPIOx_IDR))
#define GPIOC_ODR (*(volatile uint32_t *)(GPIOC_BASE + GPIOx_ODR))

#define GPIO_MODE_INPUT 0x0
#define GPIO_MODE_OUTPUT_10MHz 0x1
#define GPIO_MODE_OUTPUT_2MHz 0x2
#define GPIO_MODE_OUTPUT_50MHz 0x3

void gpio_init(uint32_t pin, char section, uint8_t mode);
void gpio_toggle_pin(uint32_t pin, uint8_t state, char section);
uint8_t gpio_read_pin(uint32_t pin);
