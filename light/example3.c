
/*******************************************************************************
  
  * File name :  GPIO_3 / main.c  
  
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
		// -- <2> LED¸¦ On/Off ÇÏ±â À§ÇÑ º¯¼ö  (0x01 = 0000 0001) 
		uint16_t led = 0x01;
		
		// -- <3> MCUÀÇ ÃÊ±âÈ­ ÇÔ¼ö
		HAL_Init(); 	
		// -- <4> system clockÀÇ ÃÊ±âÈ­ ÇÔ¼ö
		SystemClock_Config();	
		// --<5>  ½Ç½Àº¸µåÀÇ Ãâ·Â¿ë LEDÀÇ ÃÊ±âÈ­ ÇÔ¼ö	
		LED_Config();
		// --<6>  ½Ç½Àº¸µåÀÇ ÀÔ·Â¿ë SwitchÀÇ ÃÊ±âÈ­ ÇÔ¼ö	
		Sw_Config();

		LED_OnOff(GPIO_PIN_LedAll, 500);
		
		// -- <7> ¹«ÇÑ ·çÇÁ·Î µ¿ÀÛ
		while (1) {
				// -- <8>  º¯¼ö led ¸¦ 0À¸·Î ÃÊ±âÈ­
				led = 0x00;

			  // -- <9> Nucleo SW°¡ ´­·¯Áö¸é -> led ÀüÃ¼ bit À» 1·Î ¼³Á¤ (0xFF = 1111 1111)
				if( HAL_GPIO_ReadPin(GPIOSwNucleo, GPIO_PIN_Nucleo_Sw ) ==  SET )  led = led | 0xFF; 
			
				// -- <9-1> SW1 ÀÌ ´­·¯Áö¸é -> led ÀüÃ¼ bit À» 1·Î ¼³Á¤ (0xFF = 1111 1111)
				if( HAL_GPIO_ReadPin(GPIOSw1, GPIO_PIN_Sw1 ) ==  RESET )  led = led | 0xFF; 
				
				 // -- <10> º¯¼ö led¿¡ ÇØ´çÇÏ´Â LED¸¦ ONÇÑ ÈÄ¿¡ ´Ù½Ã OFF ÇÔ 
				LED_OnOff(led, 100);	
		}		
}

// -------------------------------------------------------------------------------- //

