#ifndef __KEY_H
#define __KEY_H
#include "air001xx_hal.h"

#define KEY_GPIOA GPIOA
#define KEY_GPIOB GPIOB
#define KEY_SEL_PIN GPIO_PIN_6//select
#define KEY_RET_PIN GPIO_PIN_7//return
#define KEY_UP_PIN GPIO_PIN_1//up
#define KEY_DOWN_PIN GPIO_PIN_2//down
#define KEY_LEFT_PIN GPIO_PIN_5//left
#define KEY_RIGHT_PIN GPIO_PIN_4//right

#define PD_PIN GPIO_PIN_0//PD

#define KEY_GPIOA_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define KEY_GPIOB_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()

void Key_Init(void);
uint8_t Key_Scan(void);

#endif