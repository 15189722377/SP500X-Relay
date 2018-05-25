#include "SWITCH.h"

void switch_GPIOInit(void)
{
	GPIO_InitTypeDef g;
	g.GPIO_Mode=GPIO_Mode_Out_PP;
	g.GPIO_Speed=GPIO_Speed_50MHz;
	
	g.GPIO_Pin=GPIO_Pin_4;   //SW2
	GPIO_Init(GPIOB,&g);
	
	g.GPIO_Pin=GPIO_Pin_5;   //SW2
	GPIO_Init(GPIOB,&g);
	
	g.GPIO_Pin=GPIO_Pin_6;   //SW2
	GPIO_Init(GPIOB,&g);
	
	g.GPIO_Pin=GPIO_Pin_7;   //SW2
	GPIO_Init(GPIOB,&g);
	
}

