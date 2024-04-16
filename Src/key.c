#include "main.h"
#include "key.h"

/**
	* @brief KEY INIT
	* @param NONE
	* @retval NONE
	*/
void Key_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Enable the BUTTON Clock */
//  __HAL_RCC_GPIOF_CLK_ENABLE();

//  gpioinitstruct.Pin = GPIO_PIN_4;
//  gpioinitstruct.Pull = GPIO_PULLUP;
//	gpioinitstruct.Mode = GPIO_MODE_IT_FALLING;
//	gpioinitstruct.Speed = GPIO_SPEED_FREQ_HIGH;  /* ????? */
//	HAL_GPIO_Init(GPIOF, &gpioinitstruct);
//	HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0x0F, 0);
//	HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
  KEY_GPIOA_CLK_ENABLE();//Enable KEY_GPIO_CLK
	KEY_GPIOB_CLK_ENABLE();
	
  GPIO_InitStruct.Pin = KEY_SEL_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;//GPIO_MODE INPUT
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	
  HAL_GPIO_Init(KEY_GPIOA, &GPIO_InitStruct);//KEY_SEL_INIT
	
	GPIO_InitStruct.Pin = KEY_RET_PIN;
	HAL_GPIO_Init(KEY_GPIOA, &GPIO_InitStruct);//KEY_RET_INIT
	
	GPIO_InitStruct.Pin = KEY_RIGHT_PIN;
	HAL_GPIO_Init(KEY_GPIOA, &GPIO_InitStruct);//KEY_UP_INIT
	
	GPIO_InitStruct.Pin = KEY_DOWN_PIN;
	HAL_GPIO_Init(KEY_GPIOA, &GPIO_InitStruct);//KEY_DOWN_INIT
	
	GPIO_InitStruct.Pin = KEY_LEFT_PIN;
	HAL_GPIO_Init(KEY_GPIOA, &GPIO_InitStruct);//KEY_LEFT_INIT
	
	GPIO_InitStruct.Pin = KEY_UP_PIN;
	HAL_GPIO_Init(KEY_GPIOB, &GPIO_InitStruct);//KEY_RIGHT_INIT
	
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
	GPIO_InitStruct.Pin = PD_PIN;
	HAL_GPIO_Init(KEY_GPIOB, &GPIO_InitStruct);//PB
}

/**
	* @brief KEY SCAN
	* @param NONE
	* @retval KEY_INDEX 0:NONE 1:KEY0 2:KEY1
	*/
uint8_t Key_Scan(void)
{
	if(HAL_GPIO_ReadPin(KEY_GPIOA,KEY_SEL_PIN)==0)
	{
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(KEY_GPIOA,KEY_SEL_PIN)==0)
		{
			while(HAL_GPIO_ReadPin(KEY_GPIOA,KEY_SEL_PIN)==0);
			return 1;
		}
	}else if(HAL_GPIO_ReadPin(KEY_GPIOA,KEY_RET_PIN)==0)
	{
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(KEY_GPIOA,KEY_RET_PIN)==0)
		{
			while(HAL_GPIO_ReadPin(KEY_GPIOA,KEY_RET_PIN)==0);
			return 2;
		}
	}else if(HAL_GPIO_ReadPin(KEY_GPIOB,KEY_UP_PIN)==0)
	{
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(KEY_GPIOB,KEY_UP_PIN)==0)
		{
			while(HAL_GPIO_ReadPin(KEY_GPIOB,KEY_UP_PIN)==0);
			return 3;
		}
	}else if(HAL_GPIO_ReadPin(KEY_GPIOA,KEY_DOWN_PIN)==0)
	{
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(KEY_GPIOA,KEY_DOWN_PIN)==0)
		{
			while(HAL_GPIO_ReadPin(KEY_GPIOA,KEY_DOWN_PIN)==0);
			return 4;
		}
	}else if(HAL_GPIO_ReadPin(KEY_GPIOA,KEY_LEFT_PIN)==0)
	{
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(KEY_GPIOA,KEY_LEFT_PIN)==0)
		{
			while(HAL_GPIO_ReadPin(KEY_GPIOA,KEY_LEFT_PIN)==0);
			return 5;
		}
	}else if(HAL_GPIO_ReadPin(KEY_GPIOA,KEY_RIGHT_PIN)==0)
	{
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(KEY_GPIOA,KEY_RIGHT_PIN)==0)
		{
			while(HAL_GPIO_ReadPin(KEY_GPIOA,KEY_RIGHT_PIN)==0);
			return 6;
		}
	}
	return 0;
}