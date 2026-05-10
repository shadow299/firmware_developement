#include "../uart/uart.h"
#include "gpio.h"

uint8_t get_binary_value(uint8_t mode)
{
    if (mode == GPIO_MODE_INPUT)
    {
        return 0b0000; // input mode
    }
    else if (mode == GPIO_MODE_OUTPUT_10MHz)
    {
        return 0b0001; // output mode, max speed 10 MHz
    }
    else if (mode == GPIO_MODE_OUTPUT_2MHz)
    {
        return 0b0010;
    }
    else if (mode == GPIO_MODE_OUTPUT_50MHz)
    {
        return 0b0011; // output mode, max speed 50 MHz
    }
    else
    {
        return 0b0000; // default to input mode if invalid mode is provided
    }
}

void gpio_init(uint32_t pin, char section, uint8_t mode)
{
    if (section == 'A' || section == 'a')
    {
        RCC_ABP2ENR |= RCC_APB2ENR_IOPAEN; // enable clock for gpioa
        if (pin < 8)
        {
            GPIOA_CRL &= ~(0xF << (pin * 4));                   // clear config for pin
            GPIOA_CRL |= (get_binary_value(mode) << (pin * 4)); // set mode for pin
        }
        else
        {
            GPIOA_CRH &= ~(0xF << ((pin - 8) * 4));                   // clear config for pin
            GPIOA_CRH |= (get_binary_value(mode) << ((pin - 8) * 4)); // set mode for pin
        }
    }
    else if (section == 'B' || section == 'b')
    {
        RCC_ABP2ENR |= RCC_APB2ENR_IOPBEN; // enable clock for gpiob
        if (pin < 8)
        {
            GPIOB_CRL &= ~(0xF << (pin * 4));                   // clear config for pin
            GPIOB_CRL |= (get_binary_value(mode) << (pin * 4)); // set mode for pin
        }
        else
        {
            GPIOB_CRH &= ~(0xF << ((pin - 8) * 4));                   // clear config for pin
            GPIOB_CRH |= (get_binary_value(mode) << ((pin - 8) * 4)); // set mode for pin
        }
    }
    else if (section == 'C' || section == 'c')
    {
        RCC_ABP2ENR |= RCC_APB2ENR_IOPCEN; // enable clock for gpioc
        if (pin < 8)
        {
            GPIOC_CRL &= ~(0xF << (pin * 4));                   // clear config for pin
            GPIOC_CRL |= (get_binary_value(mode) << (pin * 4)); // set mode for pin
        }
        else
        {
            GPIOC_CRH &= ~(0xF << ((pin - 8) * 4));                   // clear config for pin
            GPIOC_CRH |= (get_binary_value(mode) << ((pin - 8) * 4)); // set mode for pin
        }
    }
}

void gpio_toggle_pin(uint32_t pin, uint8_t state, char section)
{
    if (state)
    {
        if (section == 'A' || section == 'a')
        {
            GPIOA_ODR |= (1 << pin); // set pin high
        }
        else if (section == 'B' || section == 'b')
        {
            GPIOB_ODR |= (1 << pin); // set pin high
        }
        else if (section == 'C' || section == 'c')
        {
            GPIOC_ODR |= (1 << pin); // set pin high
        }
    }
    else
    {
        if (section == 'A' || section == 'a')
        {
            GPIOA_ODR &= ~(1 << pin); // set pin low
        }
        else if (section == 'B' || section == 'b')
        {
            GPIOB_ODR &= ~(1 << pin); // set pin low
        }
        else if (section == 'C' || section == 'c')
        {
            GPIOC_ODR &= ~(1 << pin); // set pin low
        }
    }
}