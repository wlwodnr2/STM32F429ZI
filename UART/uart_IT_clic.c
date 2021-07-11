#include "main.h"

extern uint8_t key_value;
extern UART_HandleTypeDef huart3;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART3)
	{
		printf("==================================\r\n");
		printf("2. LD2 on/off\r\n");
		printf("3. LD3 on/off\r\n");
		printf("q. Exit\r\n");
		printf("==================================\r\n");

		if (key_value == '2')
		{
			printf("LD2 on/off\r\n");
			HAL_GPIO_TogglePin(GPIOB,LD2_Pin);
		}
		if (key_value == '3')
		{
			printf("LD3 on/off\r\n");
			HAL_GPIO_TogglePin(GPIOB,LD3_Pin);
		}
		if (key_value == 'q')
		{
			printf("종료 되었습니다.");
			exit(0);
		}
		HAL_UART_Receive_IT(&huart3, &key_value,1); //어떤 Uart ? 어떤 Data ? 몇 Byte ?
	}
}
