#include "stm32f10x.h"                  // Device header
//This program use 6 pins to  drive 3 motors
//MotorF---Pin(PB8,PB9),MotorL---pin(PA0,PA1),MotorR---pin(PA2,PA3);
void PWM_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 |GPIO_Pin_1 | GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8 |GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);
	TIM_InternalClockConfig(TIM4);
	
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=255-1;		//arr
	TIM_TimeBaseInitStructure.TIM_Prescaler=20-1;			// psc-----1000驱动电机芯片不会发烫；
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,& TIM_TimeBaseInitStructure);
	TIM_TimeBaseInit(TIM4,& TIM_TimeBaseInitStructure);
	
	

	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=0;		//ccr
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);
	TIM_OC3Init(TIM2,&TIM_OCInitStructure);
	TIM_OC4Init(TIM2,&TIM_OCInitStructure);
	TIM_OC3Init(TIM4,&TIM_OCInitStructure);
	TIM_OC4Init(TIM4,&TIM_OCInitStructure);
	
	TIM_Cmd(TIM2,ENABLE);
	TIM_Cmd(TIM4,ENABLE);
	
}

void PWM_Set_F_F(uint16_t ZKB)
{
	TIM_SetCompare3(TIM4,ZKB);
}


void PWM_Set_F_R(uint16_t ZKB)
{
	TIM_SetCompare4(TIM4,ZKB);
}


void PWM_Set_L_R(uint16_t ZKB)
{
	TIM_SetCompare1(TIM2,ZKB);
}


void PWM_Set_L_F(uint16_t ZKB)
{
	TIM_SetCompare2(TIM2,ZKB);
}


void PWM_Set_R_R(uint16_t ZKB)
{
	TIM_SetCompare3(TIM2,ZKB);
}


void PWM_Set_R_F(uint16_t ZKB)
{
	TIM_SetCompare4(TIM2,ZKB);
}
