
#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "SPI_Init.h"

/**************调整屏幕显示方向*****************
//      0-------->0度显示方向（默认显示方向）
//      1-------->90度显示方向
//      2-------->180度显示方向
//      3-------->270度显示方向
***********************************************/
#define USE_HORIZONTAL 0 


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 320
#define LCD_H 480

#else
#define LCD_W 480
#define LCD_H 320
#endif


void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//设置坐标函数
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);//指定区域填充颜色
void LCD_Init(void);//LCD初始化


//画笔颜色
#define WHITE       0xFFFF
#define BLACK       0x0000
#define BLUE        0x001F
#define BRED        0XF81F
#define GRED        0XFFE0
#define GBLUE       0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN       0XBC40//棕色
#define BRRED       0XFC07//棕红色
#define GRAY        0X8430//灰色
#define DARKBLUE    0X01CF//深蓝色
#define LIGHTBLUE   0X7D7C//浅蓝色
#define GRAYBLUE    0X5458//灰蓝色
#define LIGHTGREEN  0X841F//浅绿色
#define LGRAY       0XC618//浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE   0XA651//浅灰蓝色(中间层颜色)
#define LBBLUE      0X2B12//浅棕蓝色(选择条目的反色)



#endif




