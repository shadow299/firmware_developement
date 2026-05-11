
#include "core.h"

void delay_ms(uint32_t ms)
{
    for (uint32_t i = 0; i < ms * CYCLES_PER_MS; i++)
    {
        __asm__("nop");
    }
}