
/*******************************************************************************
  
  * File name :  EXTI_3 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// ÇÁ·Î±×·¥ÀÇ ¼öÇà¿¡ ÇÊ¿äÇÑ Çì´õÆÄÀÏ 
#include "main.h"		
#include "Nucleo_F429.h"		// 	Nucleo-F429 È®Àåº¸µå¿ë Çì´õ ÆÄÀÏ

// -- <1> ÇÁ·Î±×·¥ ¼öÇà¿¡ ÇÊ¿äÇÑ Àü¿ªº¯¼öÀÇ ¼±¾ð
int	flag_Sw1, flag_Sw2, flag_Sw3, flag_Sw4;

// -------------------------------------------------------------------------------- //

int main(void) 
{
		// -- <2> LED¸¦ ÄÑ±âÀ§ÇÑ º¯¼ö
		uint16_t  led = 0x01;	

		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		// -- <3> ½ºÀ§Ä¡°¡ ´­·¯Áö¸é EXTI¸¦ ¹ß»ý½ÃÅ°µµ·Ï ¼³Á¤
		SwEXTI_Config();
		
		LED_OnOff(GPIO_PIN_LedAll, 500);
		
		// ¹«ÇÑ ·çÇÁ·Î µ¿ÀÛ
		while (1)  {
				led = 0x00;					// º¯¼ö led¸¦ ÃÊ±âÈ­
					
				// -- <4> SW1 ÀÌ ´­·¯Áö¸é -> led ÀÇ 1, 2¹øÂ° bit À» 1·Î ¼³Á¤ (0x03 = 0000 0011)
				if ( flag_Sw1 == 1 )  {
								led = led | 0x03;
								LED_OnOff(led, 300);
								flag_Sw1 = 0;
				}				
				// -- <5> SW2 ÀÌ ´­·¯Áö¸é -> led ÀÇ 3, 4¹øÂ° bit À» 1·Î ¼³Á¤ (0x0c = 0000 1100)
				if ( flag_Sw2 == 1 )  {
								led = led | 0x0c;
								LED_OnOff(led, 300);
								flag_Sw2 = 0;
				}				
				// -- <6> SW3 ÀÌ ´­·¯Áö¸é -> led ÀÇ 5, 6¹øÂ° bit À» 1·Î ¼³Á¤  (0x30 = 0011 0000)
				if ( flag_Sw3 == 1 )  {
								led = led | 0x30;
								LED_OnOff(led, 300);
								flag_Sw3 = 0;
				}				
				// -- <7> SW4 ÀÌ ´­·¯Áö¸é -> led ÀÇ 7, 8¹øÂ° bit À» 1·Î ¼³Á¤  (0xc0 = 1100 0000)
				if ( flag_Sw4 == 1 )  {
								led = led | 0xc0; 
								LED_OnOff(led, 300);
								flag_Sw4 = 0;
				}		
		}	
}

// -------------------------------------------------------------------------------- //
// -- <8> EXTI ÀÎÅÍ·´Æ® Callback ÇÔ¼öÀÇ ±¸Çö

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
		// -- <9> SW1ÀÌ ´­·¯Áö¸é flag_Sw1 = 1 À¸·Î ¼³Á¤	
		if ( GPIO_PIN == GPIO_PIN_Sw1)  flag_Sw1 = 1;
		// -- <10> SW2ÀÌ ´­·¯Áö¸é flag_Sw2 = 1 À¸·Î ¼³Á¤			
		if ( GPIO_PIN == GPIO_PIN_Sw2)  flag_Sw2 = 1;
		// -- <11> SW3ÀÌ ´­·¯Áö¸é flag_Sw3 = 1 À¸·Î ¼³Á¤			
		if ( GPIO_PIN == GPIO_PIN_Sw3)  flag_Sw3 = 1;
		// -- <12> SW4ÀÌ ´­·¯Áö¸é flag_Sw4 = 1 À¸·Î ¼³Á¤			
		if ( GPIO_PIN == GPIO_PIN_Sw4)  flag_Sw4 = 1;	
}

// -------------------------------------------------------------------------------- //
