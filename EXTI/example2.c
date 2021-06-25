
/*******************************************************************************
  
  * File name :  EXTI_2 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// ÇÁ·Î±×·¥ÀÇ ¼öÇà¿¡ ÇÊ¿äÇÑ Çì´õÆÄÀÏ 
#include "main.h"		
#include "Nucleo_F429.h"		// 	Nucleo-F429 È®Àåº¸µå¿ë Çì´õ ÆÄÀÏ

// -- <1> ÇÁ·Î±×·¥ ¼öÇà¿¡ ÇÊ¿äÇÑ Àü¿ªº¯¼öÀÇ ¼±¾ð
int	flag_Sw1 = 0, flag_Sw2 = 0;

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
				// -- <4> SW1 ÀÌ ´­·¯Áö¸é -> LED¸¦ 1¹ø ¡æ 2¹ø ¡æ 3¹ø ¡æ ¡¦ ¡æ 8¹ø ¼ø¼­·Î Á¡¸êÇÏ´Â µ¿ÀÛÀ» ¹Ýº¹
				if ( flag_Sw1 == 1 )  {
						led <<= 1;
						if ( led > 0x80 ) led = 0x01;
						LED_OnOff(led, 100);			
				}
				
				// -- <5> SW2 ÀÌ ´­·¯Áö¸é -> LED¸¦ 8¹ø ¡æ 7¹ø ¡æ ¡¦ ¡æ 1¹ø ¼ø¼­·Î Á¡¸êÇÏ´Â µ¿ÀÛÀ» ¹Ýº¹
				else if ( flag_Sw2 == 1 )  {
						led >>= 1; 
						if ( led < 0x01 ) led = 0x80;
						LED_OnOff(led, 100);
				}		
		}	
}

// -------------------------------------------------------------------------------- //
// -- <6> EXTI ÀÎÅÍ·´Æ® Callback ÇÔ¼öÀÇ ±¸Çö

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
		// -- <7> SW1ÀÌ ´­·¯Áö¸é flag_Sw1 = 1 , flag_Sw2 =  0 À¸·Î ¼³Á¤	
		if ( GPIO_PIN == GPIO_PIN_Sw1)  {
				flag_Sw1 = 1;
				flag_Sw2 = 0;
		}

		// -- <8> SW2ÀÌ ´­·¯Áö¸é flag_Sw1 = 0 , flag_Sw2 =  1 ·Î ¼³Á¤		
		else if ( GPIO_PIN == GPIO_PIN_Sw2)  {
				flag_Sw1 = 0;
				flag_Sw2 = 1;
		}	
}

// -------------------------------------------------------------------------------- //
