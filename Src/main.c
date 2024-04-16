/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>
#include "OLED.h"
#include "ui.h"
#include "key.h"
#include "uart.h"
#include "at24c02.h"
#include "cw2015.h"

uint8_t display_on =1;//屏幕显示或息屏

MENU_LIST list[]=
{
	{4,2,0,7},//音量1-8
	{6,2,0,4},//亚音0-4
	{8,4,0,1},//射频开关0-1
	{12,2,0,7},//扰频0-7
	{14,5,0,8},//免提灵敏度0-8
	{19,4,0,9},//静噪级别0-9
	{23,5,0,7},//麦克灵敏度0-7
};

uint8_t channel_index=0;

void Get_Init_Data(void)
{
	uint8_t temp_data = 0;
	temp_data = AT24CXX_ReadOneByte(ADDR_VOL);
	AT_CMD2[10] = 0x31+temp_data;
	list[0].current_level = temp_data;
	HAL_Delay(10);
	temp_data = AT24CXX_ReadOneByte(ADDR_SUB);
	strncpy(AT_CMD1+30, subtone[temp_data],2);
	strncpy(AT_CMD1+33, subtone[temp_data],2);
	list[1].current_level = temp_data;
	HAL_Delay(100);
	temp_data = AT24CXX_ReadOneByte(ADDR_SW);
	list[2].current_level = temp_data;
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOB, PD_PIN, temp_data);
	
	temp_data = AT24CXX_ReadOneByte(ADDR_SCR);
	AT_CMD4[16] = 0x30+temp_data;
	list[3].current_level = temp_data;
	HAL_Delay(10);
	temp_data = AT24CXX_ReadOneByte(ADDR_VOX);
	AT_CMD3[10] = 0x30+temp_data;
	list[4].current_level = temp_data;
	HAL_Delay(10);
	temp_data = AT24CXX_ReadOneByte(ADDR_SQU);
	AT_CMD4[10] = 0x30+temp_data;
	list[5].current_level = temp_data;
	HAL_Delay(10);
	temp_data = AT24CXX_ReadOneByte(ADDR_MIC);
	AT_CMD4[12] = 0x30+temp_data;
	list[6].current_level = temp_data;
	HAL_Delay(10);
	
	channel_index = AT24CXX_ReadOneByte(ADDR_FREQ);
	strncpy(AT_CMD1+10, freq_list[channel_index],8);
	strncpy(AT_CMD1+20, freq_list[channel_index],8);
	HAL_Delay(10);
}
/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
	uint8_t page_index=0;//page index
	uint8_t current_index=0;//list index
	uint8_t temp_list_level = 0;
	uint8_t key_index = 0;//key index
	
	uint8_t i=0, list_len = (sizeof(list)/sizeof(MENU_LIST));
	
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();
	UART2_INIT();
	
	Get_Init_Data();
	
//	if (HAL_UART_Transmit_IT(&UartHandle, AT_CMD1, 41) != HAL_OK) {
//			Error_Handler();
//	}
//	if (HAL_UART_Transmit_IT(&UartHandle, AT_CMD2, 13) != HAL_OK) {
//			Error_Handler();
//	}
//	if (HAL_UART_Transmit_IT(&UartHandle, AT_CMD3, 21) != HAL_OK) {
//			Error_Handler();
//	}
//	if (HAL_UART_Transmit_IT(&UartHandle, AT_CMD4, 21) != HAL_OK) {
//			Error_Handler();
//	}
	
	Show_HomePage(list[0].current_level, list[2].current_level);
	
//	AT24CXX_WriteOneByte(ADDR_VOL,8);
//	HAL_Delay(500);
//	AT24CXX_WriteOneByte(ADDR_SUB,0);
//	HAL_Delay(500);
//	AT24CXX_WriteOneByte(ADDR_SW,0);
//	HAL_Delay(500);
//	AT24CXX_WriteOneByte(ADDR_SCR,0);
//	HAL_Delay(500);
//	AT24CXX_WriteOneByte(ADDR_VOX,0);
//	HAL_Delay(500);
//	AT24CXX_WriteOneByte(ADDR_SQU,5);
//	HAL_Delay(500);
//	AT24CXX_WriteOneByte(ADDR_MIC,5);
//	HAL_Delay(500);
	
	CW2015_WriteOneByte(0x0a,0xff);//wake up cw2015
	HAL_Delay(50);
	CW2015_WriteOneByte(0x0a,0x00);//wake up cw2015
	HAL_Delay(50);
	uint8_t battary_data = 0;
	battary_data = CW2015_ReadOneByte(0x08);
	battary_data = battary_data & 0x02;
	HAL_Delay(50);
	if(battary_data == 0)
	{
		Update_Bat_Info();
	}
//	OLED_ShowNum(127-24,16,battary_data,3,8,1);
//	if (HAL_UART_Transmit_IT(&UartHandle, &eeprom_data, 1) != HAL_OK) {
//		Error_Handler();
//	}
		
//oled_showlist(list_len, current_index, (MENU_LIST *)list, 2);
	temp_list_level = list[0].current_level;
  while (1)
  {
		if(page_index == 0 && display_on)
		{
			OLED_ShowChar(8, 0, list[0].current_level + 0x30, 8, 1);
//			battary_data = CW2015_ReadOneByte(0x08);
//			battary_data = battary_data & 0b00000010;
//			HAL_Delay(50);
//			OLED_ShowNum(127-24,16,battary_data,3,8,1);
			battary_data = CW2015_ReadOneByte(0x04);
			HAL_Delay(50);
			OLED_ShowNum(127-24,0,battary_data,3,8,1);
//			battary_data = CW2015_ReadOneByte(0x07);
//			HAL_Delay(50);
//			OLED_ShowNum(127-24,8,battary_data,3,8,1);
//			
//			battary_data = CW2015_ReadOneByte(0x06);
//			HAL_Delay(50);
//			OLED_ShowNum(127-24-24,8,battary_data & 0x1f,3,8,1);
//			
//			battary_data = CW2015_ReadOneByte(0x02);
//			HAL_Delay(50);
//			OLED_ShowNum(0,8,battary_data,3,8,1);
//			battary_data = CW2015_ReadOneByte(0x03);
//			HAL_Delay(50);
//			OLED_ShowNum(24,8,battary_data & 0x1f,3,8,1);
			
			OLED_ShowChar(127-6,0,'%',8,1);
			OLED_Refresh();
		}
		
		key_index=Key_Scan();
		if(key_index == 1)
		{
			switch(page_index)//key_select
			{
				case 0://enter menu
					if(display_on){
						page_index +=1;
						current_index=oled_showlist(list_len, current_index, (MENU_LIST *)list, 2);
					}else{
						Show_HomePage(list[0].current_level, list[2].current_level);
						display_on = 1;
					}
					break;
				case 1://select setting
					list[current_index].current_level = temp_list_level;
					Uart_TxData(current_index, list[current_index].current_level);
					break;
				default:
					break;
			}
		}else if(key_index == 2)//key_return
		{
			switch(page_index)
			{
				case 0://none
					display_on = 0;
					OLED_Clear();
					OLED_Refresh();
//					current_index=oled_showlist(list_len, current_index, (MENU_LIST *)list, 1);
					break;
				case 1://return home page
					page_index -= 1;
					Show_HomePage(list[0].current_level, list[2].current_level);
					current_index=0;
					break;
				default:
					break;
			}
		}else if(key_index == 3)//key_up
		{
			if(page_index == 1)//current is menu page
			{
				current_index=oled_showlist(list_len, current_index, (MENU_LIST *)list, 0);//previous(up)
				temp_list_level = list[current_index].current_level;
			}else
			{
				Set_Level_Silent((MENU_LIST *)list, 0, 1);
				Uart_TxData(0, list[0].current_level);
			}
		}else if(key_index == 4)//key_down
		{
			if(page_index == 1)
			{
				current_index=oled_showlist(list_len, current_index, (MENU_LIST *)list, 1);//next(down)
				temp_list_level = list[current_index].current_level;
			}else
			{
				Set_Level_Silent((MENU_LIST *)list, 0, 0);
				Uart_TxData(0, list[0].current_level);
			}
		}else if(key_index == 5)//key_left
		{
			if(page_index == 1)
			{
				temp_list_level= Set_Level((MENU_LIST *)list, current_index, temp_list_level, 0);
			}else{
				channel_index = Uart_SetFreq(channel_index, 0);
			}
		}else if(key_index == 6)//key_right
		{
			if(page_index == 1)
			{
				temp_list_level = Set_Level((MENU_LIST *)list, current_index, temp_list_level, 1);
			}else
			{
				channel_index = Uart_SetFreq(channel_index, 1);
			}
		}
		
		key_index = 0;
  }
}