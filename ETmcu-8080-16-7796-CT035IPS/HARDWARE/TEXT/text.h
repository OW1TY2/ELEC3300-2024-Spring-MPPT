/**
 ****************************************************************************************************
 * @file        text.h
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
#ifndef __TEXT_H__
#define __TEXT_H__	 
#include "sys.h"
#include "fontupd.h"
					     
void Show_Str(u16 x,u16 y,u16 width,u16 height,char*str,u8 size,uint8_t mode, uint16_t color);//��ָ��λ����ʾһ���ַ��� 
void Show_Str_Mid(u16 x,u16 y,char*str,u8 size,u8 len,u16 color);
#endif
