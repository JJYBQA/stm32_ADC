#ifndef  __led_h_
#define  __led_h_

#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void led_Init(void);
void led_blink(uint8_t blink_times,uint32_t on_time_ms) ; //on_time_ms range 0 to 1000;

#endif
