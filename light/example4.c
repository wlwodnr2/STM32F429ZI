
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
			
				// -- <9-1> SW1 ÀÌ ´­·¯Áö¸é -> led ÀÇ 1, 2¹øÂ° bit À» 1·Î ¼³Á¤ (0x03 = 0000 0011)
				if( HAL_GPIO_ReadPin(GPIOSw1, GPIO_PIN_Sw1 ) ==  RESET )  led = led | 0x03; 
				
				// -- <9-2> SW2 ÀÌ ´­·¯Áö¸é -> led ÀÇ 3, 4¹øÂ° bit À» 1·Î ¼³Á¤ (0x0c = 0000 1100)
				if( HAL_GPIO_ReadPin(GPIOSw2, GPIO_PIN_Sw2 ) ==  RESET )  led = led | 0x0c; 
				
				// -- <9-3> SW3 ÀÌ ´­·¯Áö¸é -> led ÀÇ 5, 6¹øÂ° bit À» 1·Î ¼³Á¤  (0x30 = 0011 0000)
				if( HAL_GPIO_ReadPin(GPIOSw3, GPIO_PIN_Sw3 ) ==  RESET )  led = led | 0x30; 
				
				// -- <9-4> SW4 ÀÌ ´­·¯Áö¸é -> led ÀÇ 7, 8¹øÂ° bit À» 1·Î ¼³Á¤  (0xc0 = 1100 0000)
				if( HAL_GPIO_ReadPin(GPIOSw4, GPIO_PIN_Sw4 ) ==  RESET )  led = led | 0xc0; 
				
				 // -- <10> º¯¼ö led¿¡ ÇØ´çÇÏ´Â LED¸¦ ONÇÑ ÈÄ¿¡ ´Ù½Ã OFF ÇÔ 
				LED_OnOff(led, 100);	
		}		
}

// -------------------------------------------------------------------------------- //

