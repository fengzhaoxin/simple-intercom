#ifndef __AT24C02_H
#define __AT24C02_H
#include "air001xx_hal.h"

#define ADDR_VOL 0x00 //音量 0-7
#define ADDR_SUB 0x01 //亚音 0-4
#define ADDR_SW 0x02 //射频开关 0-1
#define ADDR_SCR 0x03 //扰频 0-7
#define ADDR_VOX 0x04 //免提灵敏度 0-8
#define ADDR_SQU 0x05 //静噪级别 0-9
#define ADDR_MIC 0x06 //麦克灵敏度 0-7
#define ADDR_FREQ 0x07 //频道 0-19

uint8_t AT24CXX_ReadOneByte(uint8_t ReadAddr);
void AT24CXX_WriteOneByte(uint8_t WriteAddr,uint8_t DataToWrite);

#endif