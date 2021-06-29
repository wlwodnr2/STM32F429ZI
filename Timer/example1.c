// TIM 예제 1 : 업 카운터를 이용하여 LED를 1초 간격으로 ON/OFF

/*******************************************************************************
  
  * File name :  TIM_1 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"		
#include "Nucleo_F429.h"		// Nucleo-F429 È®Àåº¸µå¿ë Çì´õ ÆÄÀÏ

// -------------------------------------------------------------------------------- //

int main(void) 
{

		HAL_Init(); 
		SystemClock_Config();
		LED_Config();

		// -- <1> TimerÀÇ ÃÊ±â¼³Á¤¿ë ÇÔ¼ö¸¦ È£Ãâ	
		TIM2_Config(8999,9999);
		
		LED_OnOff(GPIO_PIN_LedAll, 500);

	  // -- <2> ¹«ÇÑ ·çÇÁ·Î °è¼Ó µ¿ÀÛ
		while (1)  { }
	
}		

// -------------------------------------------------------------------------------- //
// -- <3> TIM ÀÎÅÍ·´Æ® Callback ÇÔ¼ö : Period Elapsed Callback in non blocking mode.

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)  
{
		// -- <3-1> TIM ÀÎÅÍ·´Æ®°¡ ¹ß»ýÇÏ¸é LED¸¦ ¸ðµÎ Toggle ½ÃÅ²´Ù.
		HAL_GPIO_TogglePin(GPIONucleo, GPIO_PIN_LedAll);
	  HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_LedAll);
}

// -------------------------------------------------------------------------------- //

