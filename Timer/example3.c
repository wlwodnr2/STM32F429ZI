// TIM 예제 3 : 업 카운터와 OC (출력 비교) 모드를 이용한 LED의 On/Off


/*******************************************************************************
  
  * File name :  TIM_3 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"		
#include "Nucleo_F429.h"		// 	Nucleo_F429 È®Àåº¸µå¿ë Çì´õ ÆÄÀÏ

// -------------------------------------------------------------------------------- //

int main(void) 
{

		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		SwEXTI_Config();				//	ÀÌ ÇÔ¼ö´Â ÀÌ ¿¹Á¦¿¡¼­´Â »ç¿ëµÇÁö ¾Ê´Â´Ù.
	
		// -- <1> TimerÀÇ ÃÊ±â¼³Á¤¿ë ÇÔ¼ö¸¦ È£Ãâ	
		TIM2_Config(8999,9999);						
	
		// -- <2> TimerÀÇ Output Compare ÃÊ±â¼³Á¤¿ë ÇÔ¼ö¸¦ È£Ãâ	
		TIM_OC_Config(999);

		// -- <3> ¹«ÇÑ ·çÇÁ·Î °è¼Ó µ¿ÀÛ
		while (1)  { }
	
}		
		
// -------------------------------------------------------------------------------- //

// -- <4> TimerÀÇ TIM_Base ÀÎÅÍ·´Æ® Callback ÇÔ¼ö

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)  
{
		// -- <4-1> ÀÎÅÍ·´Æ®°¡ ¹ß»ýÇÏ¸é LED¸¦ ¸ðµÎ ON ½ÃÅ²´Ù.
		HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_All, GPIO_PIN_SET );	
	  HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_All, GPIO_PIN_SET );	
}

// -- <5>  TimerÀÇ OC ÀÎÅÍ·´Æ® Callback ÇÔ¼ö

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)		
{
		// -- <5-1> ÀÎÅÍ·´Æ®°¡ ¹ß»ýÇÏ¸é LED¸¦ ¸ðµÎ OFF ½ÃÅ²´Ù.
		HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_All, GPIO_PIN_RESET );	
	  HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_All, GPIO_PIN_RESET );	
}

// -------------------------------------------------------------------------------- //
