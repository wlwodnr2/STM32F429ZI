
/*******************************************************************************
  
  * File name :  EXTI_1 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// ÇÁ·Î±×·¥ÀÇ ¼öÇà¿¡ ÇÊ¿äÇÑ Çì´õÆÄÀÏ 
#include "main.h"		
#include "Nucleo_F429.h"		// 	Nucleo_F429  È®Àåº¸µå¿ë Çì´õÆÄÀÏ

// -- <1> ÇÁ·Î±×·¥ ¼öÇà¿¡ ÇÊ¿äÇÑ Àü¿ªº¯¼öÀÇ ¼±¾ð
int		flag_Sw1 =0 ;

// -------------------------------------------------------------------------------- //

int main(void) 
{
		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		// -- <2> ½ºÀ§Ä¡°¡ ´­·¯Áö¸é EXTI¸¦ ¹ß»ý½ÃÅ°µµ·Ï ¼³Á¤
		SwEXTI_Config();
		
		LED_OnOff(GPIO_PIN_LedAll, 500);
		
		// ¹«ÇÑ ·çÇÁ·Î µ¿ÀÛ
		while (1)  {
					if ( flag_Sw1 == 1 )  {
							// -- <3> SW1 ÀÌ ´­·¯Áö¸é LED¸¦ ¸ðµÎ On/Off ÇÏ°í,  flag_SW1 = 0 À¸·Î ¼³Á¤
							LED_OnOff(GPIO_PIN_LedAll, 500);
							flag_Sw1 = 0;
					}		
		}	
}

// -------------------------------------------------------------------------------- //
// -- <4> EXTI ÀÎÅÍ·´Æ® Callback ÇÔ¼öÀÇ ±¸Çö

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
	  // -- <5> Nucleo-64 º¸µå SW°¡ ´­·¯Áö¸é flag_Sw1 = 1 ·Î ¼³Á¤
		if ( GPIO_PIN == GPIO_PIN_Nucleo_Sw)  flag_Sw1 = 1;	
	
	 // -- <5-1> SW1ÀÌ ´­·¯Áö¸é flag_Sw1 = 1 ·Î ¼³Á¤
		if ( GPIO_PIN == GPIO_PIN_Sw1)  flag_Sw1 = 1;
}

// -------------------------------------------------------------------------------- //

