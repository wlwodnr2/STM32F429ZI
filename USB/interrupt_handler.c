/**
  ******************************************************************************
  * @file    USB_Device/HID_Standalone/Src/stm32f1xx_it.c 

  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
   */

#include "main.h"
#include "Nucleo_F429.h"
#include "stm32f4xx_it.h"

// -- <1> Key¸¦ ´©¸¦¶§ Mouse Ä¿¼­ÀÇ ÀÌµ¿·®À» 5 ·Î Á¤ÀÇÇÔ
#define CURSOR_STEP     5

extern void Toggle_Leds(void);

extern USBD_HandleTypeDef		USBD_Device;
extern PCD_HandleTypeDef		hpcd;
extern uint32_t							Joy_Key;

// -- <2> ¸¶¿ì½ºÀÇ ÀÌµ¿·®À» ÀúÀåÇÏ´Â º¯¼ö
uint8_t     				HID_Buffer[4];

static void GetMoveData(uint8_t *pbuf);

// ----------------------------------------------------------------------------- //

void SysTick_Handler(void)
{
	
  static __IO uint32_t counter=0;
    
  HAL_IncTick();
  
	// -- <3> HID Å¬·¡½ºÀÇ Æú¸µ½Ã°£ ¼³Á¤°ª(10ms)ÀÌ µÇ¸é  
	if ( counter++ == USBD_HID_GetPollingInterval(&USBD_Device) )  {
			// -- <3-1> ¸¶¿ì½ºÀÇ ÀÌµ¿·®(HID_Buffer)À» ¹Þ¾Æ¿Â´Ù
			GetMoveData(HID_Buffer);
			
			// -- <3-2> ¸¶¿ì½ºÀÇ ÀÌµ¿·®(HID_Buffer)ÀÌ 0ÀÌ ¾Æ´Ï¸é
			if ( (HID_Buffer[1] != 0) || (HID_Buffer[2] != 0) ) {
						// -- <3-3> HID_Buffer °ªÀ» PC·Î º¸³¿.
						USBD_HID_SendReport(&USBD_Device, HID_Buffer, 4);
			}
			counter =0;
	}

  // -- <4> LED¸¦ Toggle ½ÃÅ´		
  Toggle_LED();
  
}

/******************************************************************************/
/*                 STM32F1xx Peripherals Interrupt Handlers                   */
/******************************************************************************/


 // This function handles USB-On-The-Go FS global interrupt request.
void OTG_FS_IRQHandler(void)
{
	HAL_PCD_IRQHandler(&hpcd);
}


// This function handles USB OTG FS Wakeup IRQ Handler.
void OTG_FS_WKUP_IRQHandler(void)
{
  if((&hpcd)->Init.low_power_enable)  {
		/* Reset SLEEPDEEP bit of Cortex System Control Register */
		SCB->SCR &= (uint32_t)~((uint32_t)(SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));  
		
		//  -- <5>  System clockÀ» ¼³Á¤ 
	    // Configures system clock after wake-up from STOP */
		SystemClock_Config(); 
	  
		/* ungate PHY clock */
		__HAL_PCD_UNGATE_PHYCLOCK((&hpcd)); 
  }
  
  /* Clear EXTI pending Bit*/
  __HAL_USB_OTG_FS_WAKEUP_EXTI_CLEAR_FLAG();
}

// ----------------------------------------------------------------------------- //
// -- <6> MouseÀÇ ÀÌµ¿·® pbuf ¸¦ ¼³Á¤ÇÏ´Â ÇÔ¼ö

static void GetMoveData(uint8_t *pbuf)
{
	  int8_t  x = 0, y = 0 ;

	  // -- <6-1> ´­·¯Áø KeyÀÇ Á¾·ù¿¡ µû¶ó ´ëÀÀµÇ´Â x, y °ªÀ» ¼³Á¤ÇÔ		
	  switch( Joy_Key )	  {
					case JOY_LEFT:
						x -= CURSOR_STEP;			//¸¶¿ì½º Ä¿¼­¸¦  ¿ÞÂÊÀ¸·Î 5  ÀÌµ¿
					break;  
					
					case JOY_RIGHT:
						x += CURSOR_STEP;			//¸¶¿ì½º Ä¿¼­¸¦ ¿À¸¥ÂÊÀ¸·Î 5  ÀÌµ¿
					break;
					
					case JOY_UP:
						y -= CURSOR_STEP;			//¸¶¿ì½º Ä¿¼­¸¦ À§·Î 5  ÀÌµ¿
					break;
					
					case JOY_DOWN:
						y += CURSOR_STEP;			//¸¶¿ì½º Ä¿¼­¸¦ ¾Æ·¡·Î 5 ÀÌµ¿
					break;
					
					case JOY_NONE:					
					break;
		}

	// -- <6-2> pbufÀÇ °ªÀ» ¼³Á¤ÇÔ
	//			pbuf[1] : x ¹æÇâ(¿À¸¥ÂÊ, ¿ÞÂÊ)À¸·Î ÀÌµ¿ÇÒ °ª
	//			pbuf[2] : y ¹æÇâ(À§, ¾Æ·¡)À¸·Î ÀÌµ¿ÇÒ °ª
	pbuf[0] = 0;
	pbuf[1] = x;
	pbuf[2] = y;
	pbuf[3] = 0;
		
}

void EXTI0_IRQHandler(void)
{	
		// -- <3-1> GPIO_PIN_0¿¡¼­ EXTI°¡ ¹ß»ýÇÑ °æ¿ì´Â
		//				 ÇÔ¼ö HAL_GPIO_EXTI_Callback(GPIO_PIN_0) ¸¦ È£Ãâ
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);	
}

// -------------------------------------------------------------------------------- //
// -- <4>  EXTI1 ÀÎÅÍ·´Æ®ÀÇ ÇÚµé·¯ ÇÔ¼ö

void EXTI1_IRQHandler(void)
{
		// -- <4-1> GPIO_PIN_1¿¡¼­ EXTI°¡ ¹ß»ýÇÑ °æ¿ì´Â
		//				 ÇÔ¼ö HAL_GPIO_EXTI_Callback(GPIO_PIN_1) ¸¦ È£Ãâ	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);	
}

// -------------------------------------------------------------------------------- //
// -- <5>  EXTI2 ÀÎÅÍ·´Æ®ÀÇ ÇÚµé·¯ ÇÔ¼ö

void EXTI2_IRQHandler(void)
{
		// -- <5-1> GPIO_PIN_2¿¡¼­ EXTI°¡ ¹ß»ýÇÑ °æ¿ì´Â
		//				 ÇÔ¼ö HAL_GPIO_EXTI_Callback(GPIO_PIN_2) ¸¦ È£Ãâ		
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);	
}

// -------------------------------------------------------------------------------- //
// -- <5>  EXTI3 ÀÎÅÍ·´Æ®ÀÇ ÇÚµé·¯ ÇÔ¼ö

void EXTI3_IRQHandler(void)
{
		// -- <5-1> GPIO_PIN_3¿¡¼­ EXTI°¡ ¹ß»ýÇÑ °æ¿ì´Â
		//				 ÇÔ¼ö HAL_GPIO_EXTI_Callback(GPIO_PIN_3) ¸¦ È£Ãâ		
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);	
}

// -------------------------------------------------------------------------------- //
// -- <6>  EXTI13 ÀÎÅÍ·´Æ®ÀÇ ÇÚµé·¯ ÇÔ¼ö

void EXTI15_10_IRQHandler(void)
{	
		// -- <6-1> GPIO_PIN_13¿¡¼­ EXTI°¡ ¹ß»ýÇÑ °æ¿ì´Â
		//				 ÇÔ¼ö HAL_GPIO_EXTI_Callback(GPIO_PIN_13) ¸¦ È£Ãâ		
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

// ----------------------------------------------------------------------------- //


