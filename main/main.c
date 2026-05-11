#include "../uart/uart.h"
#include "../core/core.h"
#include "main.h"
#include "../spi/spi.h"
#include "../gpio/gpio.h"

uint8_t id;
//
// ODR bit 0 -> LED ON
// ODR bit 1 -> Led OFF
//

int main(void)
{
  usart1_init();
  spi_init();

  usart1_send_string("START\n");

  while (1)
  {
    gpio_toggle_pin(4, 0, 'A'); // CS LOW

    spi_transfer(0xD0);      // send register address
    id = spi_transfer(0x00); // read response

    gpio_toggle_pin(4, 1, 'A'); // CS HIGH

    if (id == 0x58)
    {
      uart_printf("BMP280 detected! ID: %x\n", id);
    }
    else
    {
      uart_printf("NOT FOUND\n");
    }

    delay_ms(500);
  }
}