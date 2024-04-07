/**
 ****************************************************************************************************
 * @file        usart.h
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
#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define Baudrate            256000
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			   1		//ʹ�ܣ�1��/��ֹ��0������1����

#define DMA_SIZE 2
extern u8 DMA_Flag;
extern u8 DMA_Buf_Flag1;
extern u8 DMA_Buf_Flag2;
extern u8 DMA_Buf1[] ;
extern u8 DMA_Buf2[];

extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
#endif


