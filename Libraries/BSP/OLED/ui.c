#include "main.h"
#include "OLED.h"
#include "ui.h"
#include "bmp.h"



const char freq_list[20][9]=
{
	{'4','0','9','.','7','5','0','0',0},
	{'4','0','9','.','7','6','2','5',0},
	{'4','0','9','.','7','7','5','0',0},
	{'4','0','9','.','7','8','7','5',0},
	{'4','0','9','.','8','0','0','0',0},
	{'4','0','9','.','8','1','2','5',0},
	{'4','0','9','.','8','2','5','0',0},
	{'4','0','9','.','8','3','7','5',0},
	{'4','0','9','.','8','5','0','0',0},
	{'4','0','9','.','8','6','2','5',0},
	{'4','0','9','.','8','7','5','0',0},
	{'4','0','9','.','8','8','7','5',0},
	{'4','0','9','.','9','0','0','0',0},
	{'4','0','9','.','9','1','2','5',0},
	{'4','0','9','.','9','2','5','0',0},
	{'4','0','9','.','9','3','7','5',0},
	{'4','0','9','.','9','5','0','0',0},
	{'4','0','9','.','9','6','2','5',0},
	{'4','0','9','.','9','7','5','0',0},
	{'4','0','9','.','9','8','7','5',0}
};

const char sw_state[2][4]={
	{'O', 'F', 'F', 0},
	{'O', 'N', ' ', 0}
};

/**
	* @brief  SHOW HOME PAGE
	* @param  NONE
  * @retval NONE
	*/
void Show_HomePage(uint8_t vol_level, uint8_t sw_level)
{
	//clean buff
	OLED_Clear();
	//show status bar
	OLED_ShowPicture(0,0,volume_bmp_sizex,volume_bmp_sizey,(uint8_t *)volume_bmp,1);
	OLED_ShowChar(volume_bmp_sizex, 0, vol_level + 0x30, 8, 1);
	
	OLED_ShowPicture(volume_bmp_sizex+8*2+4,0,signal_bmp_sizex,signal_bmp_sizey,(uint8_t *)signal_bmp,1);
	OLED_ShowString(volume_bmp_sizex+8*2+4+signal_bmp_sizex+4,0, (uint8_t *)sw_state[sw_level],8,1);
//	OLED_ShowPicture(0,0,silence_bmp_sizex,silence_bmp_sizey,(uint8_t *)silence_bmp,1);
//	OLED_ShowPicture(silence_bmp_sizex+8*2+4,0,signal_bmp_sizex,signal_bmp_sizey,(uint8_t *)signal_bmp,1);
	OLED_ShowPicture(127-24-battery_full_bmp_sizex,0,battery_full_bmp_sizex,battery_full_bmp_sizey,(uint8_t *)battery_full_bmp,1);
//	OLED_Refresh();
//	HAL_Delay(1000);
//	OLED_ClearPart(silence_bmp_sizex+8*2+4,0,signal_bmp_sizex,signal_bmp_sizey,1);
//	OLED_ShowPicture(silence_bmp_sizex+8*2+4,0,no_signal_bmp_sizex,no_signal_bmp_sizey,(uint8_t *)no_signal_bmp,1);
//	OLED_Refresh();
	//show freq
	OLED_ShowString(3,16,(uint8_t *)freq_list[channel_index],24,1);
	OLED_ShowString(101,24,(uint8_t *)"Mhz",16,1);
	//show menu button
	OLED_ShowChinese(0,48,0,16,1);
	OLED_ShowChinese(16,48,1,16,1);
	//show return button
	OLED_ShowChinese(96,48,2,16,1);
	OLED_ShowChinese(112,48,3,16,1);
	//display
	OLED_Refresh();
}

void OLED_Set_Freq(uint8_t index)
{
	OLED_ClearPart(3,16,96,24,1);
	OLED_ShowString(3,16,(uint8_t *)freq_list[index],24,1);
	OLED_Refresh();
}

/**
	* @brief  show list
	* @param  list_len
	* @param  current_index
	* @param  list:current list
	* @param  moving direction 0:down;1:up;2:current
  * @retval next_index
  * @test
						oled_showlist(list_len, current_index, list, 2);
						HAL_Delay(1000);
						current_index = oled_showlist(list_len, current_index, list, 0);
						HAL_Delay(1000);
						current_index = oled_showlist(list_len, current_index, list, 1);
  */
uint8_t oled_showlist(uint8_t list_len, uint8_t current_index, MENU_LIST *list, uint8_t direction)
{
	uint8_t next_index, list_index, i,j;
	if(direction == 0 && current_index  > 0)//0:down
	{
		next_index = current_index - 1;
		for(i=0;i<=CHAR_HEIGHT;i+=4)
		{
			OLED_Clear();
			for(list_index=0; list_index<list_len; list_index++)
			{
				for(j=0;j<list[list_index].str_len;j++)
				{
					OLED_ShowChinese(j*CHAR_HEIGHT,-current_index*CHAR_HEIGHT+i+list_index*CHAR_HEIGHT,list[list_index].str_num+j,CHAR_HEIGHT,1);
					OLED_ShowChar(112,-current_index*CHAR_HEIGHT+i+list_index*CHAR_HEIGHT,list[list_index].current_level+'0',CHAR_HEIGHT,1);
				}
			}
			OLED_DrawRect(0,0,127,16,1);
			OLED_Refresh();
			HAL_Delay(10);
		}
	}
	else if(direction == 1 && current_index  < list_len-1)//1:up
	{
		next_index = current_index + 1;
		for(i=0;i<=CHAR_HEIGHT;i+=4)
		{
			OLED_Clear();
			for(list_index=0; list_index<list_len; list_index++)
			{
				for(j=0;j<list[list_index].str_len;j++)
				{
					OLED_ShowChinese(j*CHAR_HEIGHT,-current_index*CHAR_HEIGHT-i+list_index*CHAR_HEIGHT,list[list_index].str_num+j,CHAR_HEIGHT,1);
					OLED_ShowChar(112,-current_index*CHAR_HEIGHT-i+list_index*CHAR_HEIGHT,list[list_index].current_level+'0',CHAR_HEIGHT,1);
				}
			}
			OLED_DrawRect(0,0,127,16,1);
			OLED_Refresh();
			HAL_Delay(10);
		}
	}
	else//2:current
	{
		next_index = current_index;
		OLED_Clear();
		for(list_index=0; list_index<list_len; list_index++)
		{
			for(j=0;j<list[list_index].str_len;j++)
			{
				OLED_ShowChinese(j*CHAR_HEIGHT,-current_index*CHAR_HEIGHT+list_index*CHAR_HEIGHT,list[list_index].str_num+j,CHAR_HEIGHT,1);
				OLED_ShowChar(112,-current_index*CHAR_HEIGHT+list_index*CHAR_HEIGHT,list[list_index].current_level+'0',CHAR_HEIGHT,1);
			}
		}
		OLED_DrawRect(0,0,127,16,1);
		OLED_Refresh();
	}
	return next_index;
}

/**
	* @brief  Set_Level
	* @param  current_index
	* @param  list:current list
	* @param  direction 0:down;1:up;2:current
  * @retval next_index
  * @test
						oled_showlist(list_len, current_index, list, 2);
						HAL_Delay(1000);
						current_index = oled_showlist(list_len, current_index, list, 0);
						HAL_Delay(1000);
						current_index = oled_showlist(list_len, current_index, list, 1);
  */
uint8_t Set_Level(MENU_LIST *list, uint8_t current_index, uint8_t temp_level, uint8_t direction)
{
	uint8_t next_level;
	uint8_t current_level = temp_level;
	uint8_t max_level = list[current_index].max_level;
	if(direction == 0 && current_level>0)
	{
		next_level = current_level-1;
		OLED_ClearPart(112,0,8,16,1);
		OLED_ShowChar(112,0,next_level+'0',CHAR_HEIGHT,1);
		OLED_DrawRect(0,0,127,16,1);
		OLED_Refresh();
	}else if(direction == 1 && current_level<max_level)
	{
		next_level = current_level+1;
		OLED_ClearPart(112,0,8,16,1);
		OLED_ShowChar(112,0,next_level+'0',CHAR_HEIGHT,1);
		OLED_DrawRect(0,0,127,16,1);
		OLED_Refresh();
	}else{
		next_level = current_level;
	}
//	list[current_index].current_level = next_level;
	return next_level;
}

void Set_Level_Silent(MENU_LIST *list, uint8_t current_index, uint8_t direction)
{
	uint8_t next_level;
	uint8_t current_level = list[current_index].current_level;
	uint8_t max_level = list[current_index].max_level;
	if(direction == 0 && current_level>0)
	{
		next_level = current_level-1;
	}else if(direction == 1 && current_level<max_level)
	{
		next_level = current_level+1;
	}else{
		next_level = current_level;
	}
	list[current_index].current_level = next_level;
}
