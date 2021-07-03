// USB 예제 1 : HID 클래스를 이용한 마우스 제어


/*******************************************************************************
  
  * File name :  HID_Standalone / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */
 

#include "main.h"
#include "Nucleo_F429.h"

// --<1> USB µð¹ÙÀÌ½º¸¦ ÇÚµéÇÏ±â À§ÇÑ ±¸Á¶Ã¼ º¯¼ö¸¦ ¼±¾ð
USBD_HandleTypeDef    USBD_Device;			// USB Device¿ë ÇÚµé

uint32_t                        	Joy_Key = 0;				// º¸µåÀÇ ½ºÀ§Ä¡ ÀÔ·Â¿ë º¯¼ö

// -----------------------------------------------------------------------------

int main(void)
{
		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		Sw_Config();	
		//SwEXTI_Config();
		
		LED_OnOff(GPIO_PIN_LedAll, 1000);
		
		/* -- <2>  USB µð¹ÙÀÌ½º¸¦ ÃÊ±âÈ­ : Device stackÀ» ÃÊ±âÈ­ÇÏ°í class driver¸¦ ·ÎµåÇÔ */
		//			- USBD_Device, HID_Desc¸¦ ÃÊ±âÈ­ ÇÔ	
		//			- HID_Desc´Â USBD_HIDDescriptorsTypeDef ±¸Á¶Ã¼Çü º¯¼öÀÓ
			USBD_Init(&USBD_Device, &HID_Desc, 0);
		
		/* -- <3> class µå¶óÀÌ¹ö¸¦ device core¿¡ ¸µÅ©ÇÔ */
			USBD_RegisterClass(&USBD_Device, USBD_HID_CLASS);	

		/* -- <4> USB Device µ¿ÀÛÀ» ½ÃÀÛÇÔ */
			USBD_Start(&USBD_Device);  											
		
		/* -- <5> Infinite loop */
			while (1) {
					 
					// -- <5-1> Nucleo SW°¡ ´­·¯Áö´Â °æ¿ì
					if (HAL_GPIO_ReadPin(GPIOSwNucleo, GPIO_PIN_Nucleo_Sw ) == SET) {
										HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led1 );		// LED1 ¹ÝÀü							
										Joy_Key = JOY_LEFT;													// ¸¶¿ì½º ¿ÞÂÊÀ¸·Î  ¼³Á¤							
					}
					// -- <5-2> Key1 ÀÌ ´­·¯Áö´Â °æ¿ì
					else if (HAL_GPIO_ReadPin(GPIOSw1, GPIO_PIN_Sw1 ) == RESET) {         
										HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led1 );		// LED1 ¹ÝÀü		
										Joy_Key = JOY_LEFT;													// ¸¶¿ì½º ¿ÞÂÊÀ¸·Î  ¼³Á¤							
					}
						
						// -- <5-3> Key2 ÀÌ ´­·¯Áö´Â °æ¿ì					
					else if (HAL_GPIO_ReadPin(GPIOSw2, GPIO_PIN_Sw2 ) ==  RESET)  {       
										HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led2);			// LED2 ¹ÝÀü		
										Joy_Key = JOY_UP;													// ¸¶¿ì½º À§ÂÊÀ¸·Î ¼³Á¤
					}
						
					// -- <5-5> Key3 ÀÌ ´­·¯Áö´Â °æ¿ì
					else if ( HAL_GPIO_ReadPin(GPIOSw3, GPIO_PIN_Sw3 ) == RESET)   {    
										HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led3  );		// LED3 ¹ÝÀü			
										Joy_Key = JOY_DOWN;												// ¸¶¿ì½º ¾Æ·¡ÂÊÀ¸·Î  ¼³Á¤
					}
						
					// -- <5-6> Key4 ÀÌ ´­·¯Áö´Â °æ¿ì
					else if (HAL_GPIO_ReadPin(GPIOSw4, GPIO_PIN_Sw4 ) == RESET)  { 
										HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led4  );		// LED4 ¹ÝÀü		
										Joy_Key = JOY_RIGHT;												// ¸¶¿ì½º ¿À¸¥ÂÊÀ¸·Î ¼³Á¤
					}
						
					// -- <5-6>Key°¡ ´­·¯ÁöÁö ¾ÊÀº °æ¿ì	
					else
										Joy_Key = JOY_NONE;       
			}  
}

// -----------------------------------------------------------------------------
/* -- <6> LED 8À» Toggle·Î °è¼Ó ON/OFF ÇÏ´Â ÇÔ¼ö
 *			-- ÇÁ·Î±×·¥ÀÌ µ¿ÀÛÇÏ¸é LED8Àº °è¼Ó ON/OFF ÇÑ´Ù.
 */

void Toggle_LED(void)
{
  static uint32_t ticks;

  if (ticks++ == 100) {
			// -- <6-1> tick = 100ÀÏ¶§ (Áï, 100msec °£°ÝÀ¸·Î) LED 8À» toggle ½ÃÅ´ 
				HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led8);	  
				ticks = 0;
  }	
}

// ----------------------------------------------------------------------------- //

