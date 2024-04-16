#ifndef __I2C_H
#define __I2C_H

#include "air001xx_hal.h"

#define I2C_GPIO GPIOF
#define I2C_SDA GPIO_PIN_0
#define I2C_SCL GPIO_PIN_1
#define I2C_GPIO_ENABLE() __HAL_RCC_GPIOF_CLK_ENABLE()

#define I2C_CMD  0	//写命令
#define I2C_DATA 1	//写数据

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WaitAck(void);
void I2C_SendByte(uint8_t dat);
uint8_t I2C_ReadByte(uint8_t ack);

void OLED_WR_Byte(uint8_t dat,uint8_t mode);
#endif