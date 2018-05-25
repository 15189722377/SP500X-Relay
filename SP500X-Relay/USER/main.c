#include "stm32f10x.h"
#include "stm32f10x_iwdg.h"
#include "sys.h"
//#include "mb.h"
//#include "mbutils.h"
#include "flash.h"
#include "app.h"
#include "embreg.h"
#include "LTC2630ISC6.h"
#include "SWITCH.H"
#include "ADC.H"
#include "tur.h"
#include "temperature.h"

u8 bitmodbus;

void Configure_IWDG(void)
{
  RCC->CSR |= RCC_CSR_LSION; 
  while((RCC->CSR & RCC_CSR_LSIRDY) != RCC_CSR_LSIRDY) 
  { 
    /* add time out here for a robust application */
  }
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_256);
	IWDG_SetReload(1562);//10S
	
	IWDG_ReloadCounter();
	IWDG_Enable();	
}

u32 i=0;
int main()
{
	float TTTT=0;
	#define VECT_TAB_OFFSET  0x3000

	/* Set the Vector Table base address */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, VECT_TAB_OFFSET);
	
	/* Configure HCLK clock as SysTick clock source. */
	SysTick_CLKSourceConfig( SysTick_CLKSource_HCLK );

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
  
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
 	delay_init();
	
//	Configure_IWDG();  //≈‰÷√ø¥√≈π∑
	
 	RestoreModbusReg(); 
		
 	eMBInit(MB_RTU, comm_settings.modbusAddr, 0x02, comm_settings.modbusBaud, comm_settings.modbusParity);
  eMBEnable();  
	switch_GPIOInit();
	temperatureInit();
	//TIM2_MeasureInit();
	//TIM3_ModpollInit();
	
  while(1)
 { 	
		eMBPoll(); 
	  FunctionPoll(); 
	 TTTT=temperatureRead();
	 TTTT+=1;
	}
}

