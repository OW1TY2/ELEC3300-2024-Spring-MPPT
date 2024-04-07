/**
 ****************************************************************************************************
 * @file        gt911.h
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
#ifndef __GT911_H
#define __GT911_H	
#include "sys.h"							  

//IO��������	 
#define GT_RST    		PCout(14)	  //GT911��λ����
#define GT_INT    		PCin(15)		//GT911�ж�����	
   	
 
//I2C��д����	
#define GT_CMD_WR 		0X28    //д����
#define GT_CMD_RD 		0X29		//������
  
//GT9147 ���ּĴ������� 
#define GT_CTRL_REG 	0X8040   	//GT911���ƼĴ���
#define GT_CFGS_REG 	0X8047   	//GT911������ʼ��ַ�Ĵ���
#define GT_CHECK_REG 	0X80FF   	//GT911У��ͼĴ���
#define GT_PID_REG 		0X8140   	//GT911��ƷID�Ĵ���

#define GT_GSTID_REG 	0X814E   	//GT911��ǰ��⵽�Ĵ������
#define GT_TP1_REG 		0X8150  	//��һ�����������ݵ�ַ
#define GT_TP2_REG 		0X8158		//�ڶ������������ݵ�ַ
#define GT_TP3_REG 		0X8160		//���������������ݵ�ַ
#define GT_TP4_REG 		0X8168		//���ĸ����������ݵ�ַ
#define GT_TP5_REG 		0X8170		//��������������ݵ�ַ  
 
 
u8 GT911_Send_Cfg(u8 mode);
u8 GT911_WR_Reg(u16 reg,u8 *buf,u8 len);
void GT911_RD_Reg(u16 reg,u8 *buf,u8 len); 
u8 GT911_Init(void);
u8 GT911_Scan(u8 mode); 
u8 Null_Scan(u8 i);
#endif













