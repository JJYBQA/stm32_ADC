#include "led.h"

void led_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

    GPIO_Init(GPIOC,&GPIO_InitStructure);
    GPIO_SetBits(GPIOC,GPIO_Pin_13);

}

void led_blink(uint8_t blink_times,uint32_t on_time_ms)  //on_time_ms range 0 to 1000;
{
    while(blink_times)
    {
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);
    Delay_ms(on_time_ms);
    GPIO_SetBits(GPIOC,GPIO_Pin_13);
    Delay_ms(1000-on_time_ms);
		blink_times--;
    }
}

