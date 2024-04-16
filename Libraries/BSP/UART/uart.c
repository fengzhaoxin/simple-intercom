#include "main.h"
#include "uart.h"
#include "ui.h"
#include "key.h"
#include "at24c02.h"
#include <string.h>

UART_HandleTypeDef UartHandle;

//DMOGRP
uint8_t AT_CMD1[41]=
{	0x41, 0x54, 0x2B, 0x44, 0x4D, 0x4F, 0x47, 0x52, 0x50, 0x3D, 0x34, 0x30, 0x39, 0x2E, 0x37, 0x35, 0x30, 0x30, 0x30, 0x2C, 0x34, 0x30, 0x39, 0x2E, 0x37, 0x35, 0x30, 0x30, 0x30, 0x2C, 0x70, 0x06, 0x2C, 0x70, 0x06, 0x2C, 0x30, 0x2C, 0x30, 0x0D, 0x0A};
//DMOVOL
uint8_t AT_CMD2[13]=
{	0x41, 0x54, 0x2b, 0x44, 0x4d, 0x4f, 0x56, 0x4f, 0x4c, 0x3d, 0x38, 0x0d, 0x0a};
//DMOVOX
uint8_t AT_CMD3[13]=
{	0x41, 0x54, 0x2b, 0x44, 0x4d, 0x4f, 0x56, 0x4f, 0x58, 0x3d, 0x30, 0x0d, 0x0a};
//DMOFUN
uint8_t AT_CMD4[21]=
{	0x41, 0x54, 0x2b, 0x44, 0x4d, 0x4f, 0x46, 0x55, 0x4e, 0x3d, 0x38, 0x2c, 0x36, 0x2c, 0x35, 0x2c, 0x30, 0x2c, 0x30, 0x0d, 0x0a};

//亚音
const char subtone[5][2]={
	{0x70, 0x06},
	{0x23, 0x80},
	{0x44, 0x82},
	{0x23, 0xc0},
	{0x51, 0xc2}
};
	
uint8_t aRxBuffer[12] = {0};

void UART2_INIT(void)
{
		/* USART初始化 */
  UartHandle.Instance          = USART2;
  UartHandle.Init.BaudRate     = 9600;
  UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits     = UART_STOPBITS_1;
  UartHandle.Init.Parity       = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode         = UART_MODE_TX_RX;
  HAL_UART_Init(&UartHandle);
}

uint8_t Uart_SetFreq(uint8_t current_index, uint8_t direction)
{
	uint8_t next_index=0;
	if(direction == 0 && current_index>0)
	{
		next_index = current_index-1;
	}else if(direction == 0 && current_index == 0)
	{
		next_index = MAX_CHANNEL_INDEX;
	}else if(direction == 1 && current_index < MAX_CHANNEL_INDEX)
	{
		next_index = current_index+1;
	}else if(direction == 1 && current_index == MAX_CHANNEL_INDEX)
	{
		next_index = 0;
	}
	//uart
	strncpy(AT_CMD1+10, freq_list[next_index],8);
	strncpy(AT_CMD1+20, freq_list[next_index],8);
	if (HAL_UART_Transmit_IT(&UartHandle, AT_CMD1, 41) != HAL_OK) {
			Error_Handler();
	}
	AT24CXX_WriteOneByte(ADDR_FREQ, next_index);
	//oled
	OLED_Set_Freq(next_index);
	return next_index;
}

void Uart_TxData(uint8_t index, uint8_t level)
{
	uint8_t *aTxBuffer;
	uint8_t tx_len=0;
	switch(index)
	{
		case 0://音量
			AT_CMD2[10] = 0x31+level;
			aTxBuffer = AT_CMD2;
			tx_len=13;
			AT24CXX_WriteOneByte(ADDR_VOL, level);
			break;
		case 1://亚音
			strncpy(AT_CMD1+30, subtone[level],2);
			strncpy(AT_CMD1+33, subtone[level],2);
			aTxBuffer = AT_CMD1;
			tx_len=41;
			AT24CXX_WriteOneByte(ADDR_SUB, level);
			break;
		case 2://射频开关
			HAL_GPIO_WritePin(GPIOB, PD_PIN, level);
			AT24CXX_WriteOneByte(ADDR_SW, level);
			return;
			break;
		case 3://扰频
			AT_CMD4[16] = 0x30+level;
			aTxBuffer = AT_CMD4;
			tx_len=21;
			AT24CXX_WriteOneByte(ADDR_SCR, level);
			break;
		case 4://免提灵敏度
			AT_CMD3[10] = 0x30+level;
			aTxBuffer = AT_CMD3;
			tx_len=13;
			AT24CXX_WriteOneByte(ADDR_VOX, level);
			break;
		case 5://静噪级别
			AT_CMD4[10] = 0x30+level;
			aTxBuffer = AT_CMD4;
			tx_len=21;
			AT24CXX_WriteOneByte(ADDR_SQU, level);
			break;
		case 6://麦克灵敏度
			AT_CMD4[12] = 0x30+level;
			aTxBuffer = AT_CMD4;
			tx_len=21;
			AT24CXX_WriteOneByte(ADDR_MIC, level);
			break;
	}
	if (HAL_UART_Transmit_IT(&UartHandle, aTxBuffer, tx_len) != HAL_OK) {
			Error_Handler();
	}
}

/**
  * @brief  USART错误回调执行函数，输出错误代码
  * @param  huart：USART句柄
  * @retval 无
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  printf("Uart Error, ErrorCode = %d\r\n", huart->ErrorCode);
}

/**
  * @brief  USART发送回调执行函数
  * @param  huart：USART句柄
  * @retval 无
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
//  if (HAL_UART_Receive_IT(UartHandle, (uint8_t *)aRxBuffer, RX_LEN) != HAL_OK)
//  {
//    Error_Handler();
//  }
//	printf("Recive Data: %s", aRxBuffer);
}

/**
  * @brief  USART接收回调执行函数
  * @param  huart：USART句柄
  * @retval 无
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
//  /*通过中断方式接收数据*/
//  if (HAL_UART_Transmit_IT(UartHandle, (uint8_t *)aRxBuffer, 12) != HAL_OK)
//  {
//    Error_Handler();
//  }
}