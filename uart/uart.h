/* Header file for usart support on stm32 blue pill */

/*
1. identify the base address of the USART1 peripheral
enable clock RCC

0x40013800  → SR   (Status Register)
0x40013804  → DR   (Data Register)
0x40013808  → BRR  (Baud Rate Register)
0x4001380C  → CR1  (Control Register 1)


*/

#include <stdint.h>

// RCC register addresses
#define RCC_APB2ENR_BASE 0x40021000
#define RCC_APB2ENR (*(volatile uint32_t *)(0x40021000 + 0x18))

// USART1 register offsets
#define USART1_BASE 0x40013800
#define USART_SR (*(volatile uint32_t *)(USART1_BASE + 0x00))
#define USART_DR (*(volatile uint32_t *)(USART1_BASE + 0x04))
#define USART_BRR (*(volatile uint32_t *)(USART1_BASE + 0x08))
#define USART_CR1 (*(volatile uint32_t *)(USART1_BASE + 0x0C))

#define USRT_GPIO_BASE 0x40010800
#define UART_GPIOA_CRH (*(volatile uint32_t *)(USRT_GPIO_BASE + 0x04))

#define USART1_EN_BIT 14
#define GPIOA_EN_BIT 2

#define USART1_UE_BIT 13
#define USART1_TE_BIT 3

void usart1_init(void);
void usart1_send_char(char c);
void usart1_send_string(const char *str);
char usart1_receive_char(void);
void usart1_receive_string(char *buffer, int max_len);