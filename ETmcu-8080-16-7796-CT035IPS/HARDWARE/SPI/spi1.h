#ifndef __spi1_H
#define __spi1_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�����տƼ�ETmcu������
//SPI��غ���	   
//����:www.eya-display.com
//�޸�����:2016/3/26
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �㶫ʡ�����տƼ����޹�˾ 2016-2026
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define SPI1_DMA 1 //0  �ر�  1����   (usart3 dma ��ͻ)

void SPI1_Init(void);			 //��ʼ��SPI��
void SPI1_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u8   SPI1_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�
	
#if SPI1_DMA==1
u8 DMA1_Spi1_Init(void);
u8 DMA1_Spi1_RX(u8 *buffer,u32 len);
u8 DMA1_Spi1_TX(u8 *buffer,u32 len);
#endif

#endif

