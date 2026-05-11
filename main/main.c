#include "../gpio/gpio.h"
#include "../uart/uart.h"
#include "../core/core.h"
#include "main.h"

//
// ODR bit 0 -> LED ON
// ODR bit 1 -> Led OFF
//

int main(void)
{
  usart1_init();
  gpio_init(GREEN_LED_PIN, 'C', GPIO_MODE_OUTPUT_2MHz);
  gpio_init(RED_LED_PIN, 'A', GPIO_MODE_OUTPUT_2MHz);

  while (1)
  {
    gpio_toggle_pin(GREEN_LED_PIN, 1, 'C'); // turn on green led
    gpio_toggle_pin(RED_LED_PIN, 0, 'A');   // turn off red led
    delay_ms(200);                          // delay for 1 second

    gpio_toggle_pin(GREEN_LED_PIN, 0, 'C'); // turn off green led
    gpio_toggle_pin(RED_LED_PIN, 1, 'A');   // turn on red led
    delay_ms(200);                          // delay for 1 second
  }
}