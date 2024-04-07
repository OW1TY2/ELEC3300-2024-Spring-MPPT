#ifndef __MYCT_IIC_H
#define __MYCT_IIC_H
#include "sys.h"	    
 //////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�����տƼ�ETmcu������
//IIC���ݴ�������   
//����:www.eya-display.com
//�޸�����:2016/3/26
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �㶫ʡ�����տƼ����޹�˾ 2016-2026
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
   	   		   
//IO��������
#define CT_SDA_IN()  {GPIOA->CRL&=0XFFFFF0FF;GPIOA->CRL|=8<<4*2;}
#define CT_SDA_OUT() {GPIOA->CRL&=0XFFFFF0FF;GPIOA->CRL|=3<<4*2;}

//IO��������	 
#define CT_IIC_SCL    PAout(0) 			//SCL     
#define CT_IIC_SDA    PAout(2) 			//SDA	 
#define CT_READ_SDA   PAin(2)  			//����SDA 

//IIC���в�������
void CT_IIC_Init(void);                	//��ʼ��IIC��IO��				 
void CT_IIC_Start(void);				//����IIC��ʼ�ź�
void CT_IIC_Stop(void);	  				//����IICֹͣ�ź�
void CT_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 CT_IIC_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
u8 CT_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void CT_IIC_Ack(void);					//IIC����ACK�ź�
void CT_IIC_NAck(void);					//IIC������ACK�ź�

#endif







