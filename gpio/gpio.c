#include "gpio.h"

uint8_t get_binary_value(uint8_t mode)
{
    switch (mode)
    {
    // ---------- INPUT ----------
    case GPIO_MODE_INPUT:
        return 0x4; // Floating input
        // CNF=01 MODE=00 → 0100

    // ---------- GENERAL OUTPUT PUSH-PULL ----------
    case GPIO_MODE_OUTPUT_10MHz:
        return 0x1; // GP Push-Pull 10MHz
        // CNF=00 MODE=01 → 0001

    case GPIO_MODE_OUTPUT_2MHz:
        return 0x2; // GP Push-Pull 2MHz
        // CNF=00 MODE=10 → 0010

    case GPIO_MODE_OUTPUT_50MHz:
        return 0x3; // GP Push-Pull 50MHz
        // CNF=00 MODE=11 → 0011

    // ---------- GENERAL OUTPUT ----------
    case GPIO_MODE_OUTPUT_PUSHPULL:
        return 0x2; // GP Push-Pull 2MHz
        // CNF=00 MODE=10 → 0010

    case GPIO_MODE_OUTPUT_OPENDRAIN:
        return 0x6; // GP Open-Drain 2MHz
        // CNF=01 MODE=10 → 0110

    // ---------- ALTERNATE FUNCTION ----------
    case GPIO_MODE_AF_PUSHPULL:
        return 0xB; // AF Push-Pull 50MHz
        // CNF=10 MODE=11 → 1011

    case GPIO_MODE_AF_OPENDRAIN:
        return 0xF; // AF Open-Drain 50MHz
        // CNF=11 MODE=11 → 1111

    default:
        return 0x4; // Safe default = floating input
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