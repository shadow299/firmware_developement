#include "../uart/uart.h"
#include "../core/core.h"
#include "main.h"
#include "../spi/spi.h"
#include "../gpio/gpio.h"

//
// ODR bit 0 -> LED ON
// ODR bit 1 -> Led OFF
//

// calibration value variables
uint16_t dig_T1;
int16_t dig_T2;
int16_t dig_T3;

void bmp280_read_calib(void)
{
  // calibration values
  dig_T1 =
      bmp280_read_register(0x88) |
      (bmp280_read_register(0x89) << 8);

  dig_T2 =
      bmp280_read_register(0x8A) |
      (bmp280_read_register(0x8B) << 8);

  dig_T3 =
      bmp280_read_register(0x8C) |
      (bmp280_read_register(0x8D) << 8);
}

void bmp280_detect_device(void)
{
  uint8_t id;
  gpio_toggle_pin(4, 0, 'A'); // CS LOW

  spi_transfer(0xD0);      // send register address
  id = spi_transfer(0x00); // read response

  gpio_toggle_pin(4, 1, 'A'); // CS HIGH

  if (id == 0x58)
  {
    uart_printf("\r\nBMP280 detected! ID: %x\r\n", id);
  }
  else
  {
    uart_printf("\r\nNOT FOUND\r\n");
  }

  delay_ms(500);
}

void bmp280_show_raw_temp(void)
{
  uint8_t msb = bmp280_read_register(0xFA);
  uint8_t lsb = bmp280_read_register(0xFB);
  uint8_t xlsb = bmp280_read_register(0xFC);

  uint32_t raw_temp = (msb << 12) | (lsb << 4) | (xlsb >> 4);
  uart_printf("\r\nRAW TEMP : %d\r\n", raw_temp);
  delay_ms(200);
}

void bmp280_show_temp(void)
{
  uint8_t msb = bmp280_read_register(0xFA);
  uint8_t lsb = bmp280_read_register(0xFB);
  uint8_t xlsb = bmp280_read_register(0xFC);

  int32_t adc_T =
      ((int32_t)msb << 12) |
      ((int32_t)lsb << 4) |
      ((int32_t)xlsb >> 4);

  int32_t var1, var2, t_fine;
  int32_t temperature;

  var1 =
      ((((adc_T >> 3) -
         ((int32_t)dig_T1 << 1))) *
       ((int32_t)dig_T2)) >>
      11;

  var2 =
      (((((adc_T >> 4) -
          ((int32_t)dig_T1)) *
         ((adc_T >> 4) -
          ((int32_t)dig_T1))) >>
        12) *
       ((int32_t)dig_T3)) >>
      14;

  t_fine = var1 + var2;

  temperature = (t_fine * 5 + 128) >> 8;

  uart_printf(
      "Temp: %d.%d C\r\n",
      temperature / 100,
      temperature % 100);
}

int main(void)
{
  usart1_init();
  spi_init();

  usart1_send_string("\r\nSTART\r\n");

  bmp280_write_register(0xF4, 0x27);
  delay_ms(100);
  bmp280_read_calib();

  while (1)
  {
    bmp280_show_temp();
    delay_ms(200);
  }
}