#ifndef _SSD1306_H_
#define _SSD1306_H_

#include "include.h"


#define DC  NRF_GPIO_PIN_MAP(0,4)
#define RST NRF_GPIO_PIN_MAP(0,13) 


extern unsigned char OLED_GRAM[128][8];

void Single_Command(unsigned char cmd);

void Multi_Command(unsigned char * buff);

void Single_Data(unsigned char dt);

void Multi_Data(unsigned char * buff);

void OLED_Display_On(void);

void OLED_Display_Off(void);

void OLED_Init(void);

void OLED_Refresh_Gram(void);
void OLED_Clear(void);

void OLED_DrawPoint(u8 x,u8 y,u8 t);

void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);

void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);

void OLED_Show_3216_Char(u8 x,u8 y,u8 chr,u8 mode);

void OLED_Show_1616_Char(u8 x,u8 y,u8 chr,u8 mode);

void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);

void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);

void OLED_Draw_Bitmap(u8 x, u8 y, const u8 *pchBmp, u8 width, u8 height);

void OLED_Draw_Line(u8 x0, u8 y0,u8 x1,u8 y1,u8 t);

#endif
