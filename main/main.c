#include "../uart/uart.h"
#include "../core/core.h"
#include "main.h"
#include "../gpio/gpio.h"
#include "../i2c/i2c.h"

//
// ODR bit 0 -> LED ON
// ODR bit 1 -> Led OFF
//

// calibration value variables
// uint16_t dig_T1;
// int16_t dig_T2;
// int16_t dig_T3;

// void bmp280_read_calib(void)
// {
//   // calibration values
//   dig_T1 =
//       bmp280_read_register(0x88) |
//       (bmp280_read_register(0x89) << 8);

//   dig_T2 =
//       bmp280_read_register(0x8A) |
//       (bmp280_read_register(0x8B) << 8);

//   dig_T3 =
//       bmp280_read_register(0x8C) |
//       (bmp280_read_register(0x8D) << 8);
// }

// void bmp280_detect_device(void)
// {
//   uint8_t id;
//   gpio_toggle_pin(BMP280_CS_PIN, 0, 'A'); // CS LOW

//   spi_transfer(0xD0);      // send register address
//   id = spi_transfer(0x00); // read response

//   gpio_toggle_pin(BMP280_CS_PIN, 1, 'A'); // CS HIGH

//   if (id == 0x58)
//   {
//     uart_printf("\r\nBMP280 detected! ID: %x\r\n", id);
//   }
//   else
//   {
//     uart_printf("\r\nNOT FOUND\r\n");
//   }

//   delay_ms(500);
// }

// void bmp280_show_raw_temp(void)
// {
//   uint8_t msb = bmp280_read_register(0xFA);
//   uint8_t lsb = bmp280_read_register(0xFB);
//   uint8_t xlsb = bmp280_read_register(0xFC);

//   uint32_t raw_temp = (msb << 12) | (lsb << 4) | (xlsb >> 4);
//   uart_printf("\r\nRAW TEMP : %d\r\n", raw_temp);
//   delay_ms(200);
// }

// void bmp280_show_temp(void)
// {
//   uint8_t msb = bmp280_read_register(0xFA);
//   uint8_t lsb = bmp280_read_register(0xFB);
//   uint8_t xlsb = bmp280_read_register(0xFC);

//   int32_t adc_T =
//       ((int32_t)msb << 12) |
//       ((int32_t)lsb << 4) |
//       ((int32_t)xlsb >> 4);

//   int32_t var1, var2, t_fine;
//   int32_t temperature;

//   var1 =
//       ((((adc_T >> 3) -
//          ((int32_t)dig_T1 << 1))) *
//        ((int32_t)dig_T2)) >>
//       11;

//   var2 =
//       (((((adc_T >> 4) -
//           ((int32_t)dig_T1)) *
//          ((adc_T >> 4) -
//           ((int32_t)dig_T1))) >>
//         12) *
//        ((int32_t)dig_T3)) >>
//       14;

//   t_fine = var1 + var2;

//   temperature = (t_fine * 5 + 128) >> 8;

//   uart_printf(
//       "Temp: %d.%d C\r\n",
//       temperature / 100,
//       temperature % 100);
// }

/*
int main(void)
{
  uint8_t previous_state = 0;

  usart1_init();
  rc522_init();

  uart_printf("START\r\n");

  // led operation test
  gpio_init(0, 'A', GPIO_MODE_OUTPUT_PUSHPULL); // RED LED
  gpio_init(1, 'A', GPIO_MODE_OUTPUT_PUSHPULL); // green led

  // red led on bydefault
  gpio_toggle_pin(0, 1, 'A'); // red led on
  gpio_toggle_pin(1, 0, 'A'); // green led off

  while (1)
  {
    uint8_t current_state =
        rc522_card_present();

    // card inserted
    if (current_state &&
        !previous_state)
    {
      uart_printf(
          "CARD DETECTED\r\n");
      gpio_toggle_pin(0, 0, 'A'); // red led off
      gpio_toggle_pin(1, 1, 'A'); // green led on

      delay_ms(150); // debounce
    }

    // card removed
    if (!current_state &&
        previous_state)
    {
      uart_printf(
          "CARD REMOVED\r\n");
      gpio_toggle_pin(0, 1, 'A'); // red led on
      gpio_toggle_pin(1, 0, 'A'); // green led off
      delay_ms(150);              // debounce
    }

    previous_state =
        current_state;

    delay_ms(5);
  }
}
*/

// char get_mode(void)
// {
//   char mode;

//   uart_printf(
//       "\r\n==========\r\n");
//   uart_printf(
//       "1. READ MODE\r\n");
//   uart_printf(
//       "2. WRITE MODE\r\n");
//   uart_printf(
//       "Select Mode: ");

//   mode = usart1_receive_char();

//   uart_printf("%c\r\n", mode);

//   return mode;
// }

// void read_mode(void)
// {
//   uint8_t previous_state = 0;

//   uart_printf(
//       "\r\nREAD MODE\r\n");
//   uart_printf(
//       "Press q to quit\r\n");

//   while (1)
//   {
//     uint8_t current_state =
//         rc522_card_present();

//     // card inserted
//     if (current_state &&
//         !previous_state)
//     {
//       uart_printf(
//           "CARD DETECTED\r\n");

//       gpio_toggle_pin(0, 0, 'A');
//       gpio_toggle_pin(1, 1, 'A');

//       // read UID here later
//       // rc522_print_uid();

//       delay_ms(150);
//     }

//     // card removed
//     if (!current_state &&
//         previous_state)
//     {
//       uart_printf(
//           "CARD REMOVED\r\n");

//       gpio_toggle_pin(0, 1, 'A');
//       gpio_toggle_pin(1, 0, 'A');

//       delay_ms(150);
//     }

//     previous_state =
//         current_state;

//     // quit option
//     if (USART_SR & (1 << 5))
//     {
//       char c =
//           usart1_receive_char();

//       if (c == 'q')
//       {
//         uart_printf(
//             "Leaving read mode\r\n");
//         return;
//       }
//     }

//     delay_ms(5);
//   }
// }

// void write_mode(void)
// {
//   uart_printf(
//       "\r\nWRITE MODE\r\n");
//   uart_printf(
//       "Tap card...\r\n");

//   while (!rc522_card_present())
//   {
//     delay_ms(20);
//   }

//   uart_printf(
//       "CARD DETECTED\r\n");

//   gpio_toggle_pin(0, 0, 'A');
//   gpio_toggle_pin(1, 1, 'A');

//   // later:
//   // rc522_write_text("HELLO");

//   uart_printf(
//       "WRITE COMPLETE\r\n");

//   delay_ms(1000);

//   gpio_toggle_pin(0, 1, 'A');
//   gpio_toggle_pin(1, 0, 'A');
// }

/*
int main(void)
{
  usart1_init();
  rc522_init();

  uart_printf("START\r\n");

  // LEDs
  gpio_init(0, 'A',
            GPIO_MODE_OUTPUT_PUSHPULL);

  gpio_init(1, 'A',
            GPIO_MODE_OUTPUT_PUSHPULL);

  while (1)
  {
    char mode = get_mode();

    if (mode == '1')
    {
      read_mode();
    }
    else if (mode == '2')
    {
      write_mode();
    }
    else
    {
      uart_printf(
          "Invalid mode\r\n");
    }
  }
}
*/

// void uart_print_hex8(uint8_t value)
// {
//   if (value < 0x10)
//   {
//     uart_printf("0");
//   }

//   uart_printf("%x", value);
// }

// int main(void)
// {
//   usart1_init();
//   rc522_init();
//   uint8_t uid[4];

//   while (1)
//   {
//     if (rc522_card_present())
//     {
//       if (rc522_read_uid(uid))
//       {
//         uart_printf("UID: ");

//         uart_print_hex8(uid[0]);
//         uart_printf(" ");

//         uart_print_hex8(uid[1]);
//         uart_printf(" ");

//         uart_print_hex8(uid[2]);
//         uart_printf(" ");

//         uart_print_hex8(uid[3]);

//         uart_printf("\r\n");
//       }

//       delay_ms(5);
//     }
//   }
// }

int main(void)
{
  uint8_t id;

  usart1_init();
  i2c_init();

  uart_printf(
      "START\r\n");

  while (1)
  {
    id =
        i2c_bmp280_read_register(
            0xD0);

    uart_printf(
        "ID: 0x%x\r\n",
        id);

    delay_ms(200);
  }
}