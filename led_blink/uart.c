#include "uart.h"

void usart1_init(void)
{
    // enablen clock for gpioa and usart1
    RCC_APB2ENR |= (1 << GPIOA_EN_BIT);
    RCC_APB2ENR |= (1 << USART1_EN_BIT);

    // enable gpio pins for usart1 (PA9 -> TX, PA10 -> RX)
    // configure PA9 as alternate function push-pull (AF_PP) for TX
    // configure PA10 as input floating for RX
    // GPIOA_CRH register controls pins 8-15
    GPIOA_CRH &= ~(0xF << 4); // clear config for PA9
    GPIOA_CRH |= (0xB << 4);  // set PA9 to alternate function push-pull

    // configure PA10 as input floating
    GPIOA_CRH &= ~(0xF << 8); // clear config for PA10
    GPIOA_CRH |= (0x4 << 8);  // set PA10 to input floating

    // set baud rate to 9600 bps
    USART_BRR = 0x341;

    // enable USART1, transmitter and receiver
    USART_CR1 |= (1 << USART1_UE_BIT); // USART enable
    USART_CR1 |= (1 << USART1_TE_BIT); // Transmitter enable
}

void usart1_send_char(char c)
{
    while (!(USART_SR & (1 << 7)))
        ;         // wait until TXE (Transmit Data Register Empty) is set
    USART_DR = c; // write the character to the data register
}

void usart1_send_string(const char *str)
{
    while (*str)
    {
        usart1_send_char(*str++);
    }
}