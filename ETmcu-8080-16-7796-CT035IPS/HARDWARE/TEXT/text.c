/**
 ****************************************************************************************************
 * @file        text.c
 * @author      EYA-DISPLAY
 * @version     V2.0
 * @date        2022-04-28
 * @brief       Һ��������Demo
 * @license     Copyright (c) 2022-2032, �����տƼ�����(�㶫)
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:EYA-ETmcu������
 * ��˾��ַ:www.eya-display.com
 *
 ****************************************************************************************************
 **/
#include "sys.h" 
#include "fontupd.h"
#include "w25qxx.h"
#include "lcd.h"
#include "text.h"	
#include "string.h"			
#include "malloc.h"	
#include "updater.h"


#define F16addr ADD_BASE+0x00000000
#define F24addr ADD_BASE+0x000BB080
#define F32addr ADD_BASE+0x0025FDA0
/**
//��ȡ���ֵ�������
//code  : ��ǰ���ֱ���(GBK��)
//mat   : ��ǰ���ֵ������ݴ�ŵ�ַ
//size  : �����С
//size��С������,��������ݴ�СΪ: (size / 8 + ((size % 8) ? 1 : 0)) * (size)  �ֽ�
 */
static void text_get_hz_mat(unsigned char *code, unsigned char *mat, uint8_t size)
{
    unsigned char qh, ql;
    unsigned char i;
    unsigned long foffset;
    uint8_t csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size); /* �õ�����һ���ַ���Ӧ������ռ���ֽ��� */
    qh = *code;
    ql = *(++code);

    if (qh < 0x81 || ql < 0x40 || ql == 0xff || qh == 0xff)   /* �� ���ú��� */
    {
        for (i = 0; i < csize; i++)
        {
            *mat++ = 0x00;  /* ������� */
        }

        return;     /* �������� */
    }

    if (ql < 0x7f)
    {
        ql -= 0x40; /* ע��! */
    }
    else
    {
        ql -= 0x41;
    }

    qh -= 0x81;
    foffset = ((unsigned long)190 * qh + ql) * csize;   /* �õ��ֿ��е��ֽ�ƫ���� */

    switch (size)
    {
        case 32:
            W25QXX_Read(mat, foffset + F32addr, csize);
            break;

        case 16:
            W25QXX_Read(mat, foffset + F16addr, csize);
            break;

        case 24:
            W25QXX_Read(mat, foffset + F24addr, csize);
            break;
    }
}
//��ʾһ��ָ����С�ĺ���
//x,y   : ���ֵ�����
//font  : ����GBK��
//size  : �����С
//mode  : ��ʾģʽ
//0, ������ʾ(����Ҫ��ʾ�ĵ�,��LCD����ɫ���,��g_back_color)
//1, ������ʾ(����ʾ��Ҫ��ʾ�ĵ�, ����Ҫ��ʾ�ĵ�, ��������)
//color : ������ɫ
//�ú�������ڴ���з������������ʾ��demo CPU RAM���㣬���ܻ����bug
void text_show_font(uint16_t x, uint16_t y, uint8_t *font, uint8_t size, uint8_t mode, uint16_t color)
{
    uint8_t temp, t, t1;
    uint16_t y0 = y;
    uint8_t *dzk;
    uint8_t csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size);     /* �õ�����һ���ַ���Ӧ������ռ���ֽ��� */

    if (size != 16 && size != 24 && size != 32)//��Ҫ���������Լ����
    {
        return;     /* ��֧�ֵ�size */
    }

    dzk = malloc(size);       /* �����ڴ� */

    if (dzk == 0) return;               /* �ڴ治���� */

    text_get_hz_mat(font, dzk, size);   /* �õ���Ӧ��С�ĵ������� */

    for (t = 0; t < csize; t++)
    {
        temp = dzk[t];                  /* �õ��������� */

        for (t1 = 0; t1 < 8; t1++)
        {
            if (temp & 0x80)
            {
                LCD_DrawPoint(x, y, color);        /* ����Ҫ��ʾ�ĵ� */
            }
            else if (mode == 0)     /* ����ǵ���ģʽ, ����Ҫ��ʾ�ĵ�,�ñ���ɫ��� */
            {
                LCD_DrawPoint(x, y, BACK_COLOR);  /* ��䱳��ɫ */
            }

            temp <<= 1;
            y++;

            if ((y - y0) == size)
            {
                y = y0;
                x++;
                break;
            }
        }
    }
    free(dzk);    /* �ͷ��ڴ� */
}





//��ָ��λ�ÿ�ʼ��ʾһ���ַ���	    
//֧���Զ�����
//(x,y):��ʼ����
//width,height:����
//str  :�ַ���
//size :�����С
//mode:0,�ǵ��ӷ�ʽ;1,���ӷ�ʽ   
//color : ������ɫ
void Show_Str(u16 x,u16 y,u16 width,u16 height,char*str,u8 size,uint8_t mode, uint16_t color)
{					
    u8 x0 = x;
    u8 y0 = y;
    uint8_t bHz = 0;                /* �ַ��������� */
    uint8_t *pstr = (uint8_t *)str; /* ָ��char*���ַ����׵�ַ */
		width+=x;
	  height+=y;

    while (*pstr != 0)   /* ����δ���� */
    {
        if (!bHz)
        {
            if (*pstr > 0x80)   /* ���� */
            {
                bHz = 1;    /* ��������� */
            }
            else            /* �ַ� */
            {
							while((*pstr<='~')&&(*pstr>=' '))//�ж��ǲ��ǷǷ��ַ�!
							{       
									if(x>=width){x=x0;y+=size;}
									if(y>=height)break;//�˳�
									LCD_ShowChar(x,y,*pstr,size,0,color);
									x+=size/2;
									pstr++;
							} 
            }
        }
        else     /* ���� */
        {
            bHz = 0; /* �к��ֿ� */

            if (x > (x0 + width - size))   /* ���� */
            {
                y += size;
                x = x0;
            }

            if (y > (y0 + height - size))break; /* Խ�緵�� */

            text_show_font(x, y, pstr, size, mode, color); /* ��ʾ�������,������ʾ */
            pstr += 2;
            x += size; /* ��һ������ƫ�� */
        }
    }
} 			 		 
//��ָ����ȵ��м���ʾ�ַ���
//����ַ����ȳ�����len,����Show_Str��ʾ
//len:ָ��Ҫ��ʾ�Ŀ��			  
void Show_Str_Mid(u16 x,u16 y,char*str,u8 size,u8 len,u16 color)
{
	u16 strlenth=0;
   	strlenth=strlen((const char*)str);
	strlenth*=size/2;
	if(strlenth>len)Show_Str(x,y,lcddev.width,lcddev.height,str,size,1,color);
	else
	{
		strlenth=(len-strlenth)/2;
	    Show_Str(strlenth+x,y,lcddev.width,lcddev.height,str,size,1,color);
	}
}   





















		  






