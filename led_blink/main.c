#include "main.h"

//
//ODR bit 0 -> LED ON
//ODR bit 1 -> Led OFF
//

void led_init(void){
  //enable clock for gpioc bit 4
  RCC_ABP2ENR |= ( 1 << 4 );

  //configure pc13 as output CRH register
  GPIOC_CRH &= ~(0xF << 28); //clear config pin 15
  GPIOC_CRH |= (0x2 << 28); //output push pull 2mhz pin 15
  GPIOC_ODR |= (1 << LED_PIN); //set initial state low (led off -> active low)
}

void delay_ms(int milliseconds)
{
    volatile long cycles = milliseconds * CYCLES_PER_MS;

    while (cycles--);
}

void led_toggle(void){
  if(GPIOC_ODR & (1 << LED_PIN)){
    GPIOC_ODR &= ~(1 << LED_PIN);
  } else{
    GPIOC_ODR |= (1 << LED_PIN);
  }
}


int main(void){
  // configure the green led pin
  //
  led_init();

  while(1){
    //change the status of green led
    led_toggle();

    //pause for 500 ms
    delay_ms(100);
  }
  return 0;
}
