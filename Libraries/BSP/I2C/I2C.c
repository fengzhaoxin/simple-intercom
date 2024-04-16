#include "main.h"
#include "i2c.h"

/*引脚配置*/
#define I2C_W_SCL(x)		HAL_GPIO_WritePin(I2C_GPIO, I2C_SCL, x)
#define I2C_W_SDA(x)		HAL_GPIO_WritePin(I2C_GPIO, I2C_SDA, x)

/*I2C引脚初始化*/
void I2C_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

  I2C_GPIO_ENABLE();                        /* 使能GPIOB时钟 */
	
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;            /* 推挽输出 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* GPIO速度 */  
  GPIO_InitStruct.Pin = I2C_SCL | I2C_SDA;
  HAL_GPIO_Init(I2C_GPIO, &GPIO_InitStruct);   /* GPIO初始化 */
	
	I2C_W_SCL(1);
	I2C_W_SDA(1);
}

/**
	* @brief  I2C延时
  * @param  无
  * @retval 无
  */
static void I2C_delay(void)
{
	uint8_t t=3;
	while(t--);
}

/**
  * @brief  I2C开始
  * @param  无
  * @retval 无
  */
void I2C_Start(void)
{
	I2C_W_SDA(1);
	I2C_W_SCL(1);
	I2C_delay();
	I2C_W_SDA(0);
	I2C_delay();
	I2C_W_SCL(0);
	I2C_delay();
}

/**
  * @brief  I2C停止
  * @param  无
  * @retval 无
  */
void I2C_Stop(void)
{
	I2C_W_SDA(0);
	I2C_W_SCL(1);
	I2C_delay();
	I2C_W_SDA(1);
}

/**
  * @brief  I2C等待信号响应
  * @param  无
  * @retval 无
  */
void I2C_WaitAck(void) //测数据信号的电平
{
	I2C_W_SDA(1);
	I2C_delay();
	I2C_W_SCL(1);
	I2C_delay();
	I2C_W_SCL(0);
	 
}

/**
  * @brief  I2C发送一个字节
  * @param  Byte 要发送的一个字节
  * @retval 无
  */
void I2C_SendByte(uint8_t dat)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		if(dat&0x80)//将dat的8位从最高位依次写入
		{
			I2C_W_SDA(1);
    }
		else
		{
			I2C_W_SDA(0);
    }
		I2C_delay();
		I2C_W_SCL(1);
		I2C_delay();
		I2C_W_SCL(0);//将时钟信号设置为低电平
		dat<<=1;
  }
}

/*
*函数名：i2c_Ack
*形参：无
*返回值：无
*/
void I2C_Ack(void)
{
	I2C_W_SDA(0);    //cpu驱动SDA=0
	I2C_delay();
	I2C_W_SCL(1);    //产生一个高电平时钟
	I2C_delay();
	I2C_W_SCL(0);
	I2C_delay();
	I2C_W_SDA(1);    //cpu释放总线
}

/*
*函数名：i2c_NAck
*形参：无
*返回值：无
*/
void I2C_NAck(void)
{
	I2C_W_SDA(1);    //cpu驱动SDA=1
	I2C_delay();
	I2C_W_SCL(1);    //产生一个高电平时钟
	I2C_delay();
	I2C_W_SCL(0);
	I2C_delay();
}   

/*
*函数名：i2c_ReadByte
*形参：ack=1时，发送ACK，ack=0，发送nACK
*返回值：读取到的数据
*/
uint8_t I2C_ReadByte(uint8_t ack)
{
    uint8_t i;
    uint8_t value = 0;
    /*读取到第一个bit为数据的bit7*/
    for(i = 0;i<8;i++)
    {
			I2C_W_SCL(0);
			I2C_delay();
			I2C_W_SCL(1);
			value <<= 1;
			I2C_delay();
			if(HAL_GPIO_ReadPin(I2C_GPIO,I2C_SDA))
			{
					value++;
			}
			I2C_delay();
    }
    if (!ack)
        I2C_NAck();//发送nACK
    else
        I2C_Ack(); //发送ACK  
    return value;
}

//发送一个字节
//向SSD1306写入一个字节。
//mode:数据/命令标志 0,表示命令;1,表示数据;
/**
  * @brief  SSD1306写入一个字节
  * @param  dat 要发送的一个字节
  * @param  mode 数据/命令标志 0,表示命令;1,表示数据;
  * @retval 无
  */
void OLED_WR_Byte(uint8_t dat,uint8_t mode)
{
	I2C_Start();
	I2C_SendByte(0x78);
	I2C_WaitAck();
	if(mode){I2C_SendByte(0x40);}
  else{I2C_SendByte(0x00);}
	I2C_WaitAck();
	I2C_SendByte(dat);
	I2C_WaitAck();
	I2C_Stop();
}