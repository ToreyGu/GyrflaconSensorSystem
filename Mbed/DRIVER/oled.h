/*
 * @C++ FILES: 
 * @Descripttion: 
 * @version: 
 * @Author: TheiiKu
 * @Date: 2023-11-18 16:44:32
 * @LastEditors: TheiiKu
 * @LastEditTime: 2023-11-20 09:30:09
 * @afterAnnotation: CRATED IN JLU SENSOR LAB
 */
#ifndef __OLED_H
#define	__OLED_H

#include "nrf.h"
#include "string.h"
#include "nrf_delay.h"


#define OLED_ADDRESS	0x3C //ͨ������0R����,������0x78��0x7A������ַ -- Ĭ��0x78 >>1


#define MAX_WRITE_LENGTH  64

//显示浮点数的最大位数
#define MAX_FLOAT_LENTH		10

//显示浮点数的保留位数
#define MAX_NUMBER_RESVERD  "%.1f"


#define  u8 uint8_t
#define  u16 uint16_t
#define  u32 uint32_t


void I2C_WriteByte(uint8_t addr,uint8_t data);
void WriteCmd(unsigned char I2C_Command);
void WriteDat(unsigned char I2C_Data);
void OLED_Init(void);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowString(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowFloat(unsigned char x, unsigned char y, float value, unsigned char TextSize);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
u32 mypow(u8 m,u8 n);
void OLED_ShowNum(unsigned char x, unsigned char y, unsigned int num, unsigned char len, unsigned char TextSize);
void OLED_Draw_Bitmap(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
 

void I2C_INIT(void);

#endif

