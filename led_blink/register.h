/****************************************************************
 *
 *
 *  STM32 F103C8T6 ARm Processor ON-Chip Peripherals
 *
 *
 * *************************************************************/
 #include <stdint.h>

#define GPIOC_ODR (*(volatile uint32_t *)(0x40011000 + 0x0C))
#define RCC_ABP2ENR (*(volatile uint32_t *)(0x40021018))
#define GPIOC_CRH   (*(volatile uint32_t *)(0x40011000 + 0x04))

#define LED_PIN 15
#define CYCLES_PER_MS 8000
