// TIM 예제 4 : 업 카운터와 OC 모드 (출력 펄스 폭 변경)


/*******************************************************************************
  
  * File name :  TIM_4 / main.c  
  
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
		// -- <2> SWÀÇ EXTI ÀÔ·Â ¹ß»ýÀ» À§ÇÑ ÃÊ±â¼³Á¤ ÇÔ¼ö
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
		// ÀÎÅÍ·´Æ®°¡ ¹ß»ýÇÏ¸é LED¸¦ ¸ðµÎ ON ½ÃÅ²´Ù.
		HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_All, GPIO_PIN_SET );
    HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_All, GPIO_PIN_SET );	
}

// -- <4>  TimerÀÇ OC ÀÎÅÍ·´Æ® Callback ÇÔ¼ö

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)		
{
		// ÀÎÅÍ·´Æ®°¡ ¹ß»ýÇÏ¸é LED¸¦ ¸ðµÎ OFF ½ÃÅ²´Ù.
		HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_All, GPIO_PIN_RESET );
    HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_All, GPIO_PIN_RESET );	
}

// -------------------------------------------------------------------------------- //
// -- <5> EXTI ÀÎÅÍ·´Æ® Callback ÇÔ¼öÀÇ ±¸Çö

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{	
		// -- <5-1> SW1 ~ SW4°¡ ´­·¯Áö¸é TIM_OCInit.Pulse °ªÀ» º¯°æ
	  if ( GPIO_PIN == GPIO_PIN_Nucleo_Sw) 	TIM_OCInit.Pulse =  999;	
		if ( GPIO_PIN == GPIO_PIN_Sw1) 							TIM_OCInit.Pulse =  999;	
		if ( GPIO_PIN == GPIO_PIN_Sw2)  						TIM_OCInit.Pulse = 2999;	
		if ( GPIO_PIN == GPIO_PIN_Sw3) 							TIM_OCInit.Pulse = 4999;	
		if ( GPIO_PIN == GPIO_PIN_Sw4)  						TIM_OCInit.Pulse = 9999;
	 
		// -- <5-2> TIM OCÀÇ ChannelÀ» TIM_OCInit¿¡ ¼³Á¤µÈ °ªÀ¸·Î ÃÊ±âÈ­ÇÔ     
		HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_1);
		// -- <5-3> TIM OC¸¦ µ¿ÀÛÇÔ
		HAL_TIM_OC_Start_IT(&TimHandle,TIM_CHANNEL_1);    
}

// -------------------------------------------------------------------------------- //
