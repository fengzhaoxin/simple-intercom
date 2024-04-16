#ifndef __CW2015_H
#define __CW2015_H
#include "air001xx_hal.h"

#define SIZE_BATINFO                  64
#define REG_BATINFO             0x10

uint8_t CW2015_ReadOneByte(uint8_t ReadAddr);
void CW2015_WriteOneByte(uint8_t WriteAddr,uint8_t DataToWrite);
void Update_Bat_Info(void);
#endif