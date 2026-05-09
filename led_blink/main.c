#include "main.h"
#include "uart.h"

char cmd[20];

//
// ODR bit 0 -> LED ON
// ODR bit 1 -> Led OFF
//

int str_equal(const char *a, const char *b)
{
  while (*a && *b)
  {
    if (*a != *b)
      return 0;
    a++;
    b++;
  }
  return (*a == '\0' && *b == '\0');
}

void led_init(void)
{
  // enable clock for gpioc bit 4
  RCC_ABP2ENR |= (1 << 4);

  // configure pc13 as output CRH register
  GPIOC_CRH &= ~(0xF << 28);   // clear config pin 15
  GPIOC_CRH |= (0x2 << 28);    // output push pull 2mhz pin 15
  GPIOC_ODR |= (1 << LED_PIN); // set initial state low (led off -> active low)
}

int main(void)
{
  led_init();
  usart1_init();

  while (1)
  {
    usart1_send_string("\r\nEnter command: ");

    usart1_receive_string(cmd, sizeof(cmd));

    if (str_equal(cmd, "on"))
    {
      GPIOC_ODR |= (1 << LED_PIN);
      usart1_send_string("\r\nLED ON\r\n");
    }
    else if (str_equal(cmd, "off"))
    {
      GPIOC_ODR &= ~(1 << LED_PIN); // active low

      usart1_send_string("\r\nLED OFF\r\n");
    }
    else
    {
      usart1_send_string("\r\nUnknown command\r\n");
    }
  }
}
