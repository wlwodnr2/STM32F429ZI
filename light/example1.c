
/*******************************************************************************
  
  * File name :  GPIO_1 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// -- <1> ÇÁ·Î±×·¥ÀÇ ¼öÇà¿¡ ÇÊ¿äÇÑ Çì´õÆÄÀÏ 
#include "main.h"		
#include "Nucleo_F429.h"		// 	Nucleo_F429 º¸µå »ç¿ëÀ» À§ÇÑ Çì´õ ÆÄÀÏ

// -------------------------------------------------------------------------------- //

int main(void) 
{	
		// -- <2> MCUÀÇ ÃÊ±âÈ­ ÇÔ¼ö
		HAL_Init(); 	
		// -- <3> system clockÀÇ ÃÊ±âÈ­ ÇÔ¼ö
		SystemClock_Config();	
		// --<4>  ½Ç½Àº¸µåÀÇ Ãâ·Â¿ë LEDÀÇ ÃÊ±âÈ­ ÇÔ¼ö	
		LED_Config();

		// -- <5>  500msec µ¿¾È LED¸¦ ¸ðµÎ OnÇÑ ÈÄ¿¡ Off ÇÏ´Â ÇÔ¼ö
		LED_OnOff(GPIO_PIN_LedAll, 500);
		
		// -- <6> ¹«ÇÑ ·çÇÁ·Î µ¿ÀÛ
		while (1)  {		
				// -- <7> Nucleo Board¿¡ ÁöÁ¤µÈ LED¸¦ Åä±Û ¸ðµå·Î µ¿ÀÛ 
				HAL_GPIO_TogglePin(GPIONucleo, GPIO_PIN_LedAll);
			
			  // -- <8> È®Àå IO º¸µå¿¡ ÁöÁ¤µÈ LED¸¦ Åä±Û ¸ðµå·Î µ¿ÀÛ 
			  HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_LedAll);
			
				// -- <9> ½Ã°£Áö¿¬ ÇÔ¼ö 
				HAL_Delay(200);		
		}		
}

// -------------------------------------------------------------------------------- //

