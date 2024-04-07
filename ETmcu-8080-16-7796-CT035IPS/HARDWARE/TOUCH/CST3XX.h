/**
 ****************************************************************************************************
 * @file        cst3xx.h
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
#ifndef __CST3XX_H
#define __CST3XX_H	
#include "sys.h"							  

//IO��������	 
#define CST_RST    		PCout(14)	  // ��λ����
#define CST_INT    		PCin(15)		// �ж�����	
   	
//cst328��3240��������IIC��ַ��ID�ţ������Ĵ�����ַ��ȫһ��
//I2C��д����	
#define CST3xxIIC_AD  0x1A                        //�豸��ַ
#define CST328_CMD_WR 		(CST3xxIIC_AD<<1)     	//д����
#define CST328_CMD_RD 		(CST3xxIIC_AD<<1)+1		  //������

//I2C��д����	
#define CST3240IIC_AD     0x5A                    //�豸��ַ
#define CST3240_CMD_WR 		(CST3240IIC_AD<<1)     	//д����
#define CST3240_CMD_RD 		(CST3240IIC_AD<<1)+1		//������
  
//CST3XX ���ּĴ������� 
#define CST_PID_REG     0xD204
#define CST_GSTID_REG   0xD005

#define CST_TP1_REG 		0XD001  	//��һ�����������ݵ�ַ
#define CST_TP2_REG 		0XD008		//�ڶ������������ݵ�ַ
#define CST_TP3_REG 		0XD00D		//���������������ݵ�ַ
#define CST_TP4_REG 		0XD012		//���ĸ����������ݵ�ַ
#define CST_TP5_REG 		0XD017		//��������������ݵ�ַ  
 
extern u8 CST_IIC_WR,CST_IIC_RD;

u8 CST3XX_WR_Reg(u16 reg,u8 *buf,u8 len);
void CST3XX_RD_Reg(u16 reg,u8 *buf,u8 len); 
u8 CST3XX_Init(void);
u8 CST3XX_Scan(u8 mode); 
u8 Null_Scan(u8 i);
#endif













