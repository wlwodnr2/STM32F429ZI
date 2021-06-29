// TIM 예제 5 : 업 카운터와 OC 모드(2 채널 사용, 출력 펄스 폭 변경)


/*******************************************************************************
  
  * File name :  TIM_5 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"		
#include "Nucleo_F429.h"		// Nucleo_F429 È®Àåº¸µå¿ë Çì´õ ÆÄÀÏ

// -- <1> TimHandler, TIM_OCInit º¯¼ö¸¦ ¿ÜºÎÁ¤ÀÇ º¯¼ö·Î ¼±¾ð
extern TIM_HandleTypeDef    TimHandle;
extern TIM_OC_InitTypeDef		TIM_OCInit;		

// -------------------------------------------------------------------------------- //
int main(void) 
{
		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		SwEXTI_Config();	
		TIM2_Config(0,9999);	
		TIM_OC_Config(9999);	
		
		LED_OnOff(GPIO_PIN_LedAll, 500);

	  // ¹«ÇÑ ·çÇÁ·Î °è¼Ó µ¿ÀÛ
		while (1)  { }	
}		

// -------------------------------------------------------------------------------- //
// -- <3> TimerÀÇ TIM_Base ÀÎÅÍ·´Æ® Callback ÇÔ¼ö

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)  
{
		HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led1 | GPIO_PIN_Led2
													| GPIO_PIN_Led7 | GPIO_PIN_Led8, GPIO_PIN_SET );	
}

// -------------------------------------------------------------------------------- //
// -- <4>  TimerÀÇ OC ÀÎÅÍ·´Æ® Callback ÇÔ¼ö

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)		
{		
		// -- <4-1>  CHANNEL_1¿¡¼­ ÀÎÅÍ·´Æ®°¡ ¹ß»ýÇÑ °æ¿ì
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
			  HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led1 | GPIO_PIN_Led2, GPIO_PIN_RESET);
		}

		// <4-2>  CHANNEL_2¿¡¼­ ÀÎÅÍ·´Æ®°¡ ¹ß»ýÇÑ °æ¿ì
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
			  HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led7 | GPIO_PIN_Led8, GPIO_PIN_RESET);
		}
}

// -------------------------------------------------------------------------------- //
// -- <5>  EXTI ÀÎÅÍ·´Æ® Callback ÇÔ¼öÀÇ ±¸Çö

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{

		// -- <5-1> SW1ÀÌ ´­·¯Áö¸é channel 1, 2ÀÇ TIM_OCInit.Pulse = 9999·Î º¯°æ
		if ( GPIO_PIN == GPIO_PIN_Sw1 ) {
				TIM_OCInit.Pulse = 9999;
				HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_1);
				HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_2);
		}

		// -- <5-2> SW2°¡ ´­·¯Áö¸é channel 1ÀÇ TIM_OCInit.Pulse = 2500À¸·Î º¯°æ	
		else if ( GPIO_PIN == GPIO_PIN_Sw2 ) {
				TIM_OCInit.Pulse = 2500;
				HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_1);
		}

		// -- <5-3> SW3ÀÌ ´­·¯Áö¸é channel 2ÀÇ TIM_OCInit.Pulse = 5000À¸·Î º¯°æ
		else if ( GPIO_PIN == GPIO_PIN_Sw3 ) {
				TIM_OCInit.Pulse = 5000;
				HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_2);
		}

		// -- <5-4> SW4°¡ ´­·¯Áö¸é channel 2ÀÇ TIM_OCInit.Pulse = 1200À¸·Î º¯°æ	
		else if ( GPIO_PIN == GPIO_PIN_Sw4 ) {
				TIM_OCInit.Pulse = 1200;
				HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_2);
		}    
}

// -------------------------------------------------------------------------------- //

