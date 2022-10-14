#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"						//加入TIM3定时10ms;给编码器记速
#include "led.h"
#include "NTC.h"

int main(void)
{
	
	OLED_Init();
	led_Init();
	Ntc_Init();
	
	


	while (1)
	{
		OLED_ShowNum(2,1,AD_GetVal(),10);
		Delay_ms(200);
		led_blink(5,200);
		OLED_ShowString(1,1,"Helloworld");
		
	}
	
}




