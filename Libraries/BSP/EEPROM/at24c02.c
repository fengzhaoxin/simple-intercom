#include "at24c02.h"
#include "I2C.h"

//存储形式
//0x00 音量 0-7
//0x01 亚音 0-4
//0x02 射频开关 0-1
//0x03 扰频 0-7
//0x04 免提灵敏度 0-8
//0x05 静噪级别 0-9
//0x06 麦克灵敏度 0-7

//	uint8_t eeprom_data = 0;
//	AT24CXX_WriteOneByte(0x00, 1);
//	HAL_Delay(1000);
//	eeprom_data = AT24CXX_ReadOneByte(0x00);
//	if (HAL_UART_Transmit_IT(&UartHandle, &eeprom_data, 1) != HAL_OK) {
//		Error_Handler();
//	}
	
//在AT24CXX指定地址读出一个数据
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
uint8_t AT24CXX_ReadOneByte(uint8_t ReadAddr)
{				  
	uint8_t temp=0;		  	    																 
  I2C_Start();
	I2C_SendByte(0XA0);   //发送器件地址0XA0,写数据 	   
	I2C_WaitAck(); 
  I2C_SendByte(ReadAddr);   //发送低地址
	I2C_WaitAck();
	I2C_Start();  	 	   
	I2C_SendByte(0XA1);           //进入接收模式			   
	I2C_WaitAck();	 
  temp=I2C_ReadByte(0);		   
  I2C_Stop();//产生一个停止条件	    
	return temp;
}

//在AT24CXX指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
void AT24CXX_WriteOneByte(uint8_t WriteAddr,uint8_t DataToWrite)
{				   	  	    																 
  I2C_Start();  
	I2C_SendByte(0XA0);   //发送器件地址0XA0,写数据 	 
	I2C_WaitAck();	   
  I2C_SendByte(WriteAddr);   //发送低地址
	I2C_WaitAck(); 	 										  		   
	I2C_SendByte(DataToWrite);     //发送字节							   
	I2C_WaitAck();  		    	   
  I2C_Stop();//产生一个停止条件 
}