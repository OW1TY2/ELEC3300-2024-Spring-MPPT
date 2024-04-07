/**
 ****************************************************************************************************
 * @file        lcd.h
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
 #ifndef __UPDATER_H
#define  __UPDATER_H		
#include "sys.h"	 
#include "stdlib.h"

//��ʶ��
#define UART_IDentifier      0x40  //��ʶ��
void TIM3_Int_Init(u16 arr,u16 psc);
void NVIC_PriorityGroupConfigSet(void);
void Update(void);

extern u8  Contflag;//������־�����ڲ���ˢͼʱ��
extern u16 Counter; //���ڼ���������ˢͼʱ��

extern u32 ADD_BASE;

#endif  
	 
	 



