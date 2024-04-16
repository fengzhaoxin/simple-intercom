#ifndef __UART_H
#define __UART_H

#include "air001xx_hal.h"

#define RX_LEN 11

extern UART_HandleTypeDef UartHandle;

extern uint8_t AT_CMD1[41];
extern uint8_t AT_CMD2[13];
extern uint8_t AT_CMD3[13];
extern uint8_t AT_CMD4[21];
extern const char subtone[5][2];
void UART2_INIT(void);
uint8_t Uart_SetFreq(uint8_t index, uint8_t direction);
void Uart_TxData(uint8_t index, uint8_t level);

#endif