
#include "ssd1306.h"
#include "oledfont.h"

#include <stdio.h>

#include "nrf_gpio.h"

#include "nrf_drv_spi.h"
#include "spi.h"

#include "nrf_delay.h"



u8 OLED_GRAM[128][8];

//----------------------------------------

void Single_Command(unsigned char cmd)
{
    nrf_gpio_pin_clear(DC);
    //if SPI is busy Frequently,delay here
    //nrf_delay_us(30);
    spi_write(&cmd, sizeof(cmd));
}


void Multi_Command(unsigned char * buff)
{
    nrf_gpio_pin_clear(DC);
    //if SPI is busy Frequently,delay here
    //nrf_delay_us(30);
    spi_write(buff, 1024);
}

//----------------------------------------

void Single_Data(unsigned char dt)
{
    nrf_gpio_pin_set(DC);
    //if SPI is busy Frequently,delay here
    //nrf_delay_us(30);
    spi_write(&dt, sizeof(dt));
}

void Multi_Data(unsigned char * buff)
{
    nrf_gpio_pin_set(DC);
    //if SPI is busy Frequently,delay here
    //nrf_delay_us(30);
    spi_write(buff, 1024);
}

//----------------------------------------



   
void OLED_Display_On(void)
{
	Single_Command(0X8D);
	Single_Command(0X14);
	Single_Command(0XAF);
}
  
void OLED_Display_Off(void)
{
	Single_Command(0X8D);
	Single_Command(0X10);
	Single_Command(0XAE);
}



void OLED_Init(void)
{
    //High
    nrf_gpio_pin_set(RST);
    nrf_delay_ms(10);
    
    //Low
    nrf_gpio_pin_clear(RST);
    nrf_delay_ms(10);
    
    //High
    nrf_gpio_pin_set(RST);
    nrf_delay_ms(10);
    
    
	Single_Command(0xAE);//--turn off oled panel
	Single_Command(0x00);//---set low column address
	Single_Command(0x10);//---set high column address
	Single_Command(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	Single_Command(0x81);//--set contrast control register
	Single_Command(0xCF);// Set SEG Output Current Brightness
	Single_Command(0xA1);//--Set SEG/Column Mapping     
	Single_Command(0xC0);//Set COM/Row Scan Direction   
	Single_Command(0xA6);//--set normal display
	Single_Command(0xA8);//--set multiplex ratio(1 to 64)
	Single_Command(0x3f);//--1/64 duty
	Single_Command(0xD3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	Single_Command(0x00);//-not offset
	Single_Command(0xd5);//--set display clock divide ratio/oscillator frequency
	Single_Command(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	Single_Command(0xD9);//--set pre-charge period
	Single_Command(0xF1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	Single_Command(0xDA);//--set com pins hardware configuration
	Single_Command(0x12);
	Single_Command(0xDB);//--set vcomh
	Single_Command(0x40);//Set VCOM Deselect Level
	Single_Command(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	Single_Command(0x02);//
	Single_Command(0x8D);//--set Charge Pump enable/disable
	Single_Command(0x14);//--set(0x10) disable
	Single_Command(0xA4);// Disable Entire Display On (0xa4/0xa5)
	Single_Command(0xA6);// Disable Inverse Display On (0xa6/a7) 
	Single_Command(0xAF);//--turn on oled panel
    
    OLED_Clear(); 
}



void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		Single_Command (0xb0+i);
		Single_Command (0x00);
		Single_Command (0x10); 
		for(n=0;n<128;n++)
        {
            Single_Data(OLED_GRAM[n][i]);
        }
	}   
}



void OLED_Clear(void)  
{  
	u8 i,n;  
	for(i=0;i<8;i++)
    {
        for(n=0;n<128;n++)
        {
            OLED_GRAM[n][i]=0XFF;
        }
    }        
	OLED_Refresh_Gram();
    for(i=0;i<8;i++)
    {
        for(n=0;n<128;n++)
        {
            OLED_GRAM[n][i]=0X00;
        }
    }
    OLED_Refresh_Gram();
}



	
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;
}


void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)
{
    int x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)
        {
            OLED_DrawPoint(x,y,dot);
        }
	}
    OLED_Refresh_Gram();
}




void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode)
{      			    
	u8 temp,t,t1;
	u8 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);
	chr=chr-' ';		 
    for(t=0;t<csize;t++)
    {   
		if(size==12)temp=asc2_1206[chr][t];
		else if(size==16)temp=asc2_1608[chr][t];
		else if(size==24)temp=asc2_2412[chr][t];
		else return;
        for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)OLED_DrawPoint(x,y,mode);
			else OLED_DrawPoint(x,y,!mode);
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}




void OLED_Show_3216_Char(u8 x,u8 y,u8 chr,u8 mode)
{      			    
	u8 temp=0,y0=y;	 
    for(int i=0;i<64;i++)
    {   
		temp=c_chFont3216[chr-0x30][i];
        for(int j=0; j<8; j++)
		{
			if(temp&0x80)OLED_DrawPoint(x,y,mode);
			else OLED_DrawPoint(x,y,!mode);
			temp<<=1;
			y++;
			if((y-y0)==32)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}




void OLED_Show_1616_Char(u8 x,u8 y,u8 chr,u8 mode)
{

    u8 temp=0,y0=y;	 
    for(int i=0;i<32;i++)
    {   
		temp=c_chFont1612[chr-0x30][i];
        for(int j=0; j<8; j++)
		{
			if(temp&0x80)OLED_DrawPoint(x,y,mode);
			else OLED_DrawPoint(x,y,!mode);
			temp<<=1;
			y++;
			if((y-y0)==16)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    } 
    
}





u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  



void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ',size,1);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0',size,1); 
	}
} 




void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size)
{	
    while((*p<='~')&&(*p>=' '))
    {       
        if(x>(128-(size/2))){x=0;y+=size;}
        if(y>(64-size)){y=x=0;OLED_Clear();}
        OLED_ShowChar(x,y,*p,size,1);	 
        x+=size/2;
        p++;
    }  
}



void OLED_Draw_Bitmap(u8 x, u8 y, const u8 *pchBmp, u8 width, u8 height)
{
	u16 i, j, byteWidth = (width + 7) / 8;
	
    for(j = 0; j < height; j ++){
        for(i = 0; i < width; i ++ ) {
            if(*(pchBmp + j * byteWidth + i / 8) & (128 >> (i & 7))) {
                OLED_DrawPoint(x + i, y + j, 1);
            }
        }
    }
}


void OLED_Draw_Line(u8 x0, u8 y0,u8 x1,u8 y1,u8 t)
{
    int dx,             // difference in x's
    dy,             // difference in y's
    dx2,            // dx,dy * 2
    dy2, 
    x_inc,          // amount in pixel space to move during drawing
    y_inc,          // amount in pixel space to move during drawing
    error,          // the discriminant i.e. error i.e. decision variable
    index;          // used for looping	

	dx = x1-x0;//计算x距离
	dy = y1-y0;//计算y距离

	if (dx>=0)
	{
		x_inc = 1;
	}
	else
	{
		x_inc = -1;
		dx    = -dx;  
	} 
	
	if (dy>=0)
	{
		y_inc = 1;
	} 
	else
	{
		y_inc = -1;
		dy    = -dy; 
	} 

	dx2 = dx << 1;
	dy2 = dy << 1;

	if (dx > dy)//x距离大于y距离，那么每个x轴上只有一个点，每个y轴上有若干个点
	{//且线的点数等于x距离，以x轴递增画点
		// initialize error term
		error = dy2 - dx; 

		// draw the line
		for (index=0; index <= dx; index++)//要画的点数不会超过x距离
		{
			//画点
			OLED_DrawPoint(x0,y0,t);
			
			// test if error has overflowed
			if (error >= 0) //是否需要增加y坐标值
			{
				error-=dx2;

				// move to next line
				y0+=y_inc;//增加y坐标值
			} // end if error overflowed

			// adjust the error term
			error+=dy2;

			// move to the next pixel
			x0+=x_inc;//x坐标值每次画点后都递增1
		} // end for
	} // end if |slope| <= 1
	else//y轴大于x轴，则每个y轴上只有一个点，x轴若干个点
	{//以y轴为递增画点
		// initialize error term
		error = dx2 - dy; 

		// draw the line
		for (index=0; index <= dy; index++)
		{
			// set the pixel
			OLED_DrawPoint(x0,y0,t);

			// test if error overflowed
			if (error >= 0)
			{
				error-=dy2;

				// move to next line
				x0+=x_inc;
			} // end if error overflowed

			// adjust the error term
			error+=dx2;

			// move to the next pixel
			y0+=y_inc;
		} // end for
	} // end else |slope| > 1
}


