
/*******************************************************************************
  
  * File name :  EXTI_4 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// ÇÁ·Î±×·¥ÀÇ ¼öÇà¿¡ ÇÊ¿äÇÑ Çì´õÆÄÀÏ 
#include "main.h"		
#include "Nucleo_F429.h"		// 	Nucleo-F429 È®Àåº¸µå¿ë Çì´õ ÆÄÀÏ

// -------------------------------------------------------------------------------- //

int main(void) 
{

		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		SwEXTI_Config();

		LED_OnOff(GPIO_PIN_LedAll, 500);

		// -- <1> ¹«ÇÑ ·çÇÁ·Î µ¿ÀÛÇÏÁö¸¸ ¿©±â¼­´Â ¾Æ¹«·± ÀÏµµ ÇÏÁö ¾ÊÀ½	
		while (1)  { }
	
}

// -------------------------------------------------------------------------------- //
// -- <2> EXTI ÀÎÅÍ·´Æ® Callback ÇÔ¼öÀÇ ±¸Çö
/*				ÀÌ ÇÔ¼ö´Â HAL_GPIO_TogglePin() ÇÔ¼ö¸¦ ÀÌ¿ëÇÏ¿© LED¸¦ On/Off ÇÑ´Ù.
				µû¶ó¼­ µ¿ÀÛ½Ã¿¡  SwitchÀÇ Chattering Çö»óÀ¸·Î LED On/Off°¡ ¿©·¯¹ø ¹ß»ýÇÒ ¼öµµ ÀÖ´Ù.
*/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
	// -- <3> SW1 ÀÌ ´­·¯Áö¸é -> LED 1, 2¸¦ Toggle
	if ( GPIO_PIN == GPIO_PIN_Sw1) {
			HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led1 | GPIO_PIN_Led2 );
	}
	// -- <4> SW2 ÀÌ ´­·¯Áö¸é -> LED 3, 4¸¦ Toggle	
	if ( GPIO_PIN == GPIO_PIN_Sw2) {
			HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led3 | GPIO_PIN_Led4);
	}
	// -- <5> SW3 ÀÌ ´­·¯Áö¸é -> LED 5, 6¸¦ Toggle	
	if ( GPIO_PIN == GPIO_PIN_Sw3) {
			HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led5 | GPIO_PIN_Led6);
	}
	// -- <6> SW4 ÀÌ ´­·¯Áö¸é -> LED 7, 8¸¦ Toggle	
	if ( GPIO_PIN == GPIO_PIN_Sw4) { 
			HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led7 | GPIO_PIN_Led8);
	}	
}

// -------------------------------------------------------------------------------- //
