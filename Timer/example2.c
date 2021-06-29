#시간 지연 함수 HAL_Delay()를 이용하여 LED를 1초 간격으로 ON/OFF


/*******************************************************************************
  
  * File name :  TIM_2 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"		
#include "Nucleo_F429.h"		// 	Nucleo_F429 È®Àåº¸µå¿ë Çì´õ ÆÄÀÏ

// --------------------------------------------------------------------------------- //

int main(void) 
{
		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		
		LED_OnOff(GPIO_PIN_LedAll, 500);

	  // ¹«ÇÑ ·çÇÁ·Î °è¼Ó µ¿ÀÛ
		while (1)  {
				// -- <1> HAL_Delay() ÇÔ¼ö¸¦ ÀÌ¿ëÇÏ¿© 1000msec ½Ã°£ Áö¿¬À» ÇÔ
				HAL_Delay(1000);
			
				// -- <2>  LED¸¦ ¸ðµÎ Toggle ½ÃÅ²´Ù.
				HAL_GPIO_TogglePin(GPIONucleo, GPIO_PIN_LedAll);
				HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_LedAll);
		}	
}

// -------------------------------------------------------------------------------- //

