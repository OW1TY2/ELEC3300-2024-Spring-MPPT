/**
 ****************************************************************************************************
 * @file        sys.c
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
#include "updater.h"
 
void NVIC_Configuration(void)
{

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	  NVIC_PriorityGroupConfigSet();
}
