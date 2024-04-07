/**
 ****************************************************************************************************
 * @file        fontupd.c
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
#include "fontupd.h"
//#include "ff.h"	  
#include "w25qxx.h"
#include "lcd.h"  
//#include "malloc.h"
					   
u32 FONTINFOADDR=(1024*6+500)*1024;//Ĭ����6M�ĵ�ַ
//�ֿ���Ϣ�ṹ��. 
//���������ֿ������Ϣ����ַ����С��
_font_info ftinfo;

//��sd���е�·��
const u8 *GBK16_SDPATH="0:/SYSTEM/FONT/GBK16.FON";		//GBK16�Ĵ��λ��
const u8 *GBK12_SDPATH="0:/SYSTEM/FONT/GBK12.FON";		//GBK12�Ĵ��λ��
const u8 *UNIGBK_SDPATH="0:/SYSTEM/FONT/UNIGBK.BIN";	//UNIGBK.BIN�Ĵ��λ��
//��25Qxx�е�·��
const u8 *GBK16_25QPATH="1:/SYSTEM/FONT/GBK16.FON";		//GBK16�Ĵ��λ��
const u8 *GBK12_25QPATH="1:/SYSTEM/FONT/GBK12.FON";		//GBK12�Ĵ��λ��
const u8 *UNIGBK_25QPATH="1:/SYSTEM/FONT/UNIGBK.BIN";	//UNIGBK.BIN�Ĵ��λ��

//��ʾ��ǰ������½���
//x,y:����
//size:�����С
//fsize:�����ļ���С
//pos:��ǰ�ļ�ָ��λ��
u32 fupd_prog(u16 x,u16 y,u8 size,u32 fsize,u32 pos)
{
	float prog;
	u8 t=0XFF;
	prog=(float)pos/fsize;
	prog*=10000;
	if(t!=prog)
	{
		t=prog/100;
		if(t>100)	t=100;
		LCD_ShowNum(x,y,t,2,size);//��ʾ��ֵ
		t=0;		//��Ք���
		t=(u16)prog%100;
		if(t != 0)
		{
			if(t<10)
			{
				LCD_ShowNum(x+3*size/2,y,0,1,size);//��ʾ��ֵ
				LCD_ShowNum(x+4*size/2,y,t,1,size);//��ʾ��ֵ
			}else
			{
			LCD_ShowNum(x+3*size/2,y,t,2,size);//��ʾ��ֵ
			}
			LCD_ShowString(x+2*size/2,y,240,320,size,".");		
			LCD_ShowString(x+5*size/2,y,240,320,size,"%");		
		}
	}
	return 0;					    
} 

//���������ļ�,UNIGBK,GBK12,GBK16һ�����
//x,y:��ʾ��Ϣ����ʾ��ַ
//size:�����С
//��ʾ��Ϣ�����С
//src:0,��SD������.
//	  1,��25QXX����											  
//����ֵ:0,���³ɹ�;
//		 ����,�������.	  
//��ʼ������
//����ֵ:0,�ֿ����.
//		 ����,�ֿⶪʧ
u8 font_init(void)
{			  												 
	W25QXX_Init();
	FONTINFOADDR=0X00;			//W25Q64,6M�Ժ�	 
	ftinfo.f16addr=FONTINFOADDR;		//UNICODEGBK �����׵�ַ�̶���ַ
	W25QXX_Read((u8*)&ftinfo,FONTINFOADDR,sizeof(ftinfo));//����ftinfo�ṹ������
	//if(ftinfo.fontok!=0XAA)return 1;		//�ֿ����. 
	return 0;		    
}





























