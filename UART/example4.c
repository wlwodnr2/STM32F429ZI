// UART 예제 4 : UART를 이용하여 PC와 통신하기 (인터럽트 방식)


/*******************************************************************************
  
  * File name :  UART_4 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"			
#include "Nucleo_F429.h"			

// UartHandle º¯¼ö¸¦ ¿ÜºÎÁ¤ÀÇ º¯¼ö·Î ¼±¾ð
extern UART_HandleTypeDef	UartHandle;		

// UART Åë½Å¿ë º¯¼ö ¼±¾ð
#define TxBufferSize   	(countof(TxBuffer) - 1)
#define TxBufferSize_3 	(countof(TxBuffer_3) - 1)
#define RxBufferSize   	0xFF
#define countof(a)   	(sizeof(a) / sizeof(*(a)))

// UART Åë½ÅÀ» À§ÇÑ Á¤ÀÇ   
uint8_t TxBuffer[] = "\n\rUART Example 4 (Transmission  Success !!)\n\r\n\r";
uint8_t TxBuffer_3[] = "\n\r A Message from HAL_UART_TxCpltCallback() !!\n\r\n\r";
uint8_t RxBuffer[RxBufferSize];

// -------------------------------------------------------------------------------- //

int main(void)
{
	HAL_Init(); 
	SystemClock_Config();
	LED_Config();
	UART3_Config();

	// TxBuffer¿¡ ÀúÀåµÇ¾î ÀÖ´Â ³»¿ëÀ» PC·Î º¸³½´Ù. 
	HAL_UART_Transmit(&UartHandle, (uint8_t*)TxBuffer, TxBufferSize , 0xFFFF); 

	while (1)  
	{
		// -- <1> PC·ÎºÎÅÍ µ¥ÀÌÅÍ¸¦ ¼ö½ÅÇÒ ¶§ ÀÎÅÍ·´Æ®·Î ±¸Çö
		HAL_UART_Receive_IT(&UartHandle, (uint8_t*)RxBuffer,1);	
	}
	
}

// -------------------------------------------------------------------------------- //

// -- <2> Interrupt ¸ðµå ¼Û½ÅÀÌ ¿Ï·áµÇ¸é È£ÃâµÇ´Â callback ÇÔ¼ö 
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandler)
{
	// -- <3> ¼Û½Å(INT ¸ðµå)ÀÌ ¿Ï·áµÇ¸é TxBuffer_3¿¡ ÀúÀåµÈ ¸Þ½ÃÁö¸¦ PC·Î ¼Û½Å 
	HAL_UART_Transmit(UartHandler, (uint8_t*)TxBuffer_3, TxBufferSize_3 , 0xFFFF);
}

// -------------------------------------------------------------------------------- //

// -- <4> Interrupt ¸ðµå ¼ö½ÅÀÌ ¿Ï·áµÇ¸é È£ÃâµÇ´Â callback ÇÔ¼ö 
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandler)
{
	/* -- <5> ¼ö½Å(INT ¸ðµå)ÀÌ ¿Ï·áµÇ¸é ¼ö½ÅµÈ µ¥ÀÌÅÍ(RxBuffer)¸¦ ±×´ë·Î ¼Û½Å */
	HAL_UART_Transmit_IT(UartHandler, (uint8_t*)RxBuffer, 1);	  
}


// -------------------------------------------------------------------------------- //
