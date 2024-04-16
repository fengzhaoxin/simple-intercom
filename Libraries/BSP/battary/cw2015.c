#include "cw2015.h"
#include "I2C.h"

const unsigned char cw_bat_config_info[SIZE_BATINFO] = {
	0X15,0X7E,0X7C,0X5C,0X64,0X6A,0X65,0X5C,0X55,0X53,0X56,0X61,0X6F,0X66,0X50,0X48,
	0X43,0X42,0X40,0X43,0X4B,0X5F,0X75,0X7D,0X52,0X44,0X07,0XAE,0X11,0X22,0X40,0X56,
	0X6C,0X7C,0X85,0X86,0X3D,0X19,0X8D,0X1B,0X06,0X34,0X46,0X79,0X8D,0X90,0X90,0X46,
	0X67,0X80,0X97,0XAF,0X80,0X9F,0XAE,0XCB,0X2F,0X00,0X64,0XA5,0XB5,0X11,0XD0,0X11
};
	
//在AT24CXX指定地址读出一个数据
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
uint8_t CW2015_ReadOneByte(uint8_t ReadAddr)
{				  
	uint8_t temp=0;		  	    																 
  I2C_Start();  
	I2C_SendByte(0XC4);   //发送器件地址0XA0,写数据 	   
	I2C_WaitAck(); 
  I2C_SendByte(ReadAddr);   //发送低地址
	I2C_WaitAck();
	I2C_Start();  	 	   
	I2C_SendByte(0XC5);           //进入接收模式			   
	I2C_WaitAck();	 
  temp=I2C_ReadByte(0);		   
  I2C_Stop();//产生一个停止条件	    
	return temp;
}

//在AT24CXX指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
void CW2015_WriteOneByte(uint8_t WriteAddr,uint8_t DataToWrite)
{				   	  	    																 
  I2C_Start();
	I2C_SendByte(0XC4);   //发送器件地址0XA0,写数据 	 
	I2C_WaitAck();	   
  I2C_SendByte(WriteAddr);   //发送低地址
	I2C_WaitAck(); 	 										  		   
	I2C_SendByte(DataToWrite);     //发送字节							   
	I2C_WaitAck();  		    	   
  I2C_Stop();//产生一个停止条件 
}

void Update_Bat_Info(void)
{
	unsigned char reg_val;
	for(int i = 0; i < SIZE_BATINFO; i++)
	{
		reg_val = cw_bat_config_info[i];
		CW2015_WriteOneByte(REG_BATINFO +i, reg_val);
		HAL_Delay(20);
	}
}