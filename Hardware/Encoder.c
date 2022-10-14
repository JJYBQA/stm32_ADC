#include "stm32f10x.h"                  // Device header

//Thid C file use 6 pins {ForwordEncode(PB15,PB12),LeftEncoder(PB14,PB5),RightEncoder(PB13,PA15)}.
//use 3pin to detect TTL;
//To detect motor(forword,left,right) running state.

void EXTI_TIM3_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_InternalClockConfig(TIM3);
	

	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=(50*(10))-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	TIM_Cmd(TIM3,ENABLE);

}


void Encoder_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15| GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12 | GPIO_Pin_5 ;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource15);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13);
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line15|EXTI_Line14|EXTI_Line13;	
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	
	NVIC_Init(&NVIC_InitStructure);
	
}


int16_t Motorf,Motorl,Motorr;
int8_t CF=0,CL=0,CR=0;
int8_t div=24;

void EXTI15_10_IRQHandler(void)
{
	
	if(EXTI_GetITStatus(EXTI_Line15)==SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==1)
		{
			CF++;
		}
		
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0)
		{
			CF--;
		}
		
		if(CF==div){
			Motorf+=1;
			CF=0;
		}
		if(CF==-div){
			Motorf-=1;
			CF=0;
		}
		
		EXTI_ClearITPendingBit(EXTI_Line15);
	}
	
	
	
	
	if(EXTI_GetITStatus(EXTI_Line14)==SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1)
		{
			CL--;
		}
		
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)
		{
			CL++;
		}
		if(CL==div){
			Motorl+=1;
			CL=0;
		}
		if(CL==-div){
			Motorl-=1;
			CL=0;
		}
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
	
	if(EXTI_GetITStatus(EXTI_Line13)==SET)
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==1)
		{
			CR--;
		}
		
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==0)
		{
			CR++;
		}
		if(CR==div){
			Motorr+=1;
			CR=0;
		}
		if(CR==-div){
			Motorr-=1;
			CR=0;
		}
		EXTI_ClearITPendingBit(EXTI_Line13);
	}
	
}


int16_t GetMf(void)
{
	int16_t temp;
	temp=Motorf;
	Motorf=0;
	return temp;
}

int16_t GetMl(void)
{
	int16_t temp;
	temp=Motorl;
	Motorl=0;
	return temp;
}

int16_t GetMr(void)
{
	int16_t temp;
	temp=Motorr;
	Motorr=0;
	return temp;
}
