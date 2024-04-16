#ifndef __UI_H
#define __UI_H
#include "air001xx_hal.h"

typedef struct
{
	uint8_t str_num;
	uint8_t str_len;
	uint8_t current_level;
	uint8_t max_level;
}MENU_LIST;

#define CHAR_HEIGHT 16

extern const char freq_list[20][9];

void Show_HomePage(uint8_t vol_level, uint8_t sw_level);
void OLED_Set_Freq(uint8_t index);
uint8_t oled_showlist(uint8_t list_len, uint8_t current_index, MENU_LIST *list, uint8_t direction);
uint8_t Set_Level(MENU_LIST *list, uint8_t current_index, uint8_t temp_level, uint8_t direction);
void Set_Level_Silent(MENU_LIST *list, uint8_t current_index, uint8_t direction);

#endif