
#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "SPI_Init.h"

/**************������Ļ��ʾ����*****************
//      0-------->0����ʾ����Ĭ����ʾ����
//      1-------->90����ʾ����
//      2-------->180����ʾ����
//      3-------->270����ʾ����
***********************************************/
#define USE_HORIZONTAL 0 


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 320
#define LCD_H 480

#else
#define LCD_W 480
#define LCD_H 320
#endif


void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//�������꺯��
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);//ָ�����������ɫ
void LCD_Init(void);//LCD��ʼ��


//������ɫ
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
#define BROWN       0XBC40//��ɫ
#define BRRED       0XFC07//�غ�ɫ
#define GRAY        0X8430//��ɫ
#define DARKBLUE    0X01CF//����ɫ
#define LIGHTBLUE   0X7D7C//ǳ��ɫ
#define GRAYBLUE    0X5458//����ɫ
#define LIGHTGREEN  0X841F//ǳ��ɫ
#define LGRAY       0XC618//ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE   0XA651//ǳ����ɫ(�м����ɫ)
#define LBBLUE      0X2B12//ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)



#endif




