#include "uart.h"
#include <stdarg.h>

void usart1_init(void)
{
    // enablen clock for gpioa and usart1
    RCC_APB2ENR |= (1 << GPIOA_EN_BIT);
    RCC_APB2ENR |= (1 << USART1_EN_BIT);

    // enable gpio pins for usart1 (PA9 -> TX, PA10 -> RX)
    // configure PA9 as alternate function push-pull (AF_PP) for TX
    // configure PA10 as input floating for RX
    // UART_GPIOA_CRH register controls pins 8-15
    UART_GPIOA_CRH &= ~(0xF << 4); // clear config for PA9
    UART_GPIOA_CRH |= (0xB << 4);  // set PA9 to alternate function push-pull

    // configure PA10 as input floating
    UART_GPIOA_CRH &= ~(0xF << 8); // clear config for PA10
    UART_GPIOA_CRH |= (0x4 << 8);  // set PA10 to input floating

    // set baud rate to 9600 bps
    USART_BRR = 0x341;

    // enable USART1, transmitter and receiver
    USART_CR1 |= (1 << USART1_UE_BIT); // USART enable
    USART_CR1 |= (1 << USART1_TE_BIT); // Transmitter enable
    USART_CR1 |= (1 << 2);             // Receiver enable (RE bit)
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

char usart1_receive_char(void)
{
    while (!(USART_SR & (1 << 5)))
        ; // wait until data received
    return USART_DR;
}

void usart1_receive_string(char *buffer, int max_len)
{
    int i = 0;
    char c;

    while (i < max_len - 1)
    {
        c = usart1_receive_char();

        // echo back (optional but useful)
        usart1_send_char(c);

        if (c == '\r' || c == '\n')
            break;

        buffer[i++] = c;
    }

    buffer[i] = '\0'; // null terminate
}
void uart_send_uint(uint32_t num)
{
    char buffer[10];
    int i = 0;

    if (num == 0)
    {
        usart1_send_char('0');
        return;
    }

    while (num > 0)
    {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    while (i > 0)
    {
        usart1_send_char(buffer[--i]);
    }
}

void uart_send_hex(uint32_t num)
{
    char hex_chars[] = "0123456789ABCDEF";

    usart1_send_string("0x");

    for (int i = 28; i >= 0; i -= 4)
    {
        uint8_t nibble = (num >> i) & 0xF;
        usart1_send_char(hex_chars[nibble]);
    }
}

void uart_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    while (*fmt)
    {
        if (*fmt == '%')
        {
            fmt++;

            switch (*fmt)
            {
            case 'c':
            {
                char c = va_arg(args, int);
                usart1_send_char(c);
                break;
            }

            case 's':
            {
                char *str = va_arg(args, char *);
                usart1_send_string(str);
                break;
            }

            case 'd':
            {
                int num = va_arg(args, int);

                if (num < 0)
                {
                    usart1_send_char('-');
                    num = -num;
                }

                uart_send_uint(num);
                break;
            }

            case 'x':
            {
                uint32_t num = va_arg(args, uint32_t);
                uart_send_hex(num);
                break;
            }

            case '%':
            {
                usart1_send_char('%');
                break;
            }

            default:
                usart1_send_char('%');
                usart1_send_char(*fmt);
                break;
            }
        }
        else
        {
            usart1_send_char(*fmt);
        }

        fmt++;
    }

    va_end(args);
}