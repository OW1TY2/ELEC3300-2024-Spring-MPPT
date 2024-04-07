/**
 ****************************************************************************************************
 * @file        main.c
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
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "touch.h" 
#include "text.h" 
#include "w25qxx.h"
#include "updater.h"
/*  �����Ҫ�����ɱ��CPU��ֻ��Ҫ�����IO�ڣ�������������հ�ʹ��
*/

u8 AUTO=0;//���������������Ҫһֱˢ�����������������Ϊ1
u8 Olddir;//���ڼ�¼��Ļԭʼ�ķ���
u8  Contflag=0;//������־�����ڲ���ˢͼʱ��
u16 Counter=0; //���ڼ���������ˢͼʱ��

//�ⲿflash��ַ����
// 16*16����GBK ��0x00000000 -0x000BB080
// 24*24����GBK ��0x000BB080 -0x001A4D20
// 32*32����GBK ��0x0025FDA00-0x002EC200
// 128x128ͼƬ  �� 0x0054BFA0           ��ʼ���  ÿ��ͼƬ��С 128*128*2�ֽ�  ��5��ͼƬ
// 160x128ͼƬ  �� 0x0054BFA0+0x00028000��ʼ���  ÿ��ͼƬ��С 160*128*2�ֽ�  ��5��ͼƬ   ��ƫ�Ƶ�ַ0x00028000
// 320x240ͼƬ  �� 0x0054BFA0+0x0005A000��ʼ���  ÿ��ͼƬ��С 320*240*2�ֽ�  ��5��ͼƬ   ��ƫ�Ƶ�ַ0x0005A000
// 480x272ͼƬ  �� 0x0054BFA0+0x00115800��ʼ���  ÿ��ͼƬ��С 480*272*2�ֽ�  ��5��ͼƬ   ��ƫ�Ƶ�ַ0x00115800
// 480x320ͼƬ  �� 0x0054BFA0+0x00253C80��ʼ���  ÿ��ͼƬ��С 480*320*2�ֽ�  ��5��ͼƬ   ��ƫ�Ƶ�ַ0x00253C80

//ͼƬ��ŵ�ַ 
#define pic_ad  ADD_BASE+0x0054BFA0 //�����ַ����Ҫ�Ķ�
//����lcd.h�����õķֱ���ѡ���Ӧ��ͼƬ��ʼ��ַ
#if((LCD_WIDTH==128)&&(LCD_HEIGHT==128))
#define off_ad  0x0
#elif((LCD_WIDTH==128)&&(LCD_HEIGHT==160))
#define off_ad  0x00028000
#elif((LCD_WIDTH==240)&&(LCD_HEIGHT==320))
#define off_ad  0x0005A000
#elif((LCD_WIDTH==480)&&(LCD_HEIGHT==272))
#define off_ad  0x00115800
#elif((LCD_WIDTH==320)&&(LCD_HEIGHT==480))
#define off_ad  0x00254400
#endif
//ͼƬȡģ��ʽΪ����ȡģ�����Ҫ������ʾͼƬ����Ҫ�л��ɺ�����ʾ!!!

//���尴��
#define KEYup   1
#define KEYdown 2

#define DelayTime 1000000
//����Ϊ���������
 int main(void)
 {
	u32 loop=0;               //����������������Ļ���Զ�ˢ���ܻ���
	u8 ix=0;                  //ѭ��ʹ�õı���
	u8 Keypad;                //����λ�û���
  u8 buffpic[LCD_WIDTH*2];  //ͼƬ����
	delay_init();	    	      //��ʱ������ʼ��	  
	NVIC_Configuration(); 	  //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(Baudrate);	 	  //���ڳ�ʼ��Ϊ115200  ����ͨ�����ڴ�ӡһЩ������Ϊ���Բο�
	W25QXX_Init();            //��ʼ���ⲿNorFLASH
	LCD_Init();               //Һ������ʼ��  ����ʾlogo  LOGO�ļ�ͨ��ȡģ���� IMAGE1.C�У���LCD��ʼ�����֮����ʾLOGO��LOGO��ʾ���֮�󿪱���
	TIM3_Int_Init(49,7199);   //10Khz�ļ���Ƶ�ʣ�������50Ϊ5ms  
	TIM2_PWM_Init(899,16);    //��ʼ���������PWM  //8��Ƶ��PWMƵ��=72000/(899+1)/16=2Khz 
	//Update();               //�����Ҫ����FALSH����ſ����������Ŀǰֻ֧��ȫ������
	//�����ɰ������仯
	for(ix=0;ix<10;ix++)
	{
		 SendPWMval(ix);         //��������0-10
		 delay_ms(250);         //��ʱ�ۿ����ȱ仯�����Բο�����������ñ�������
	}
	delay_ms(2000); 
	tp_dev.init();		        //��������ʼ��
	//TP_Adjust();            //����������败��У׼���棬��ſ������������������У׼���ɡ�  ���败�����к������л�֮��ҲҪ�ſ��������������У׼����
//////////////////////////////////////////���¿�ʼLCD���ܲ��� ��ʼ///////////////////////////////////////	
	ix=0;
	LCD_Clear(WHITE);//����
	Show_Str((lcddev.width-32*7)/2,10,260,32,"�����տƼ�����",32,1,RED); //X���������ʾ32*32���� 
	Show_Str(30,60,600,24,"������",24,1,BLACK);                          //��ʾ24*24����
	Show_Str(30,60+24*1,600,24,"Һ����ʾ��",24,1,BLACK);
	Show_Str(30,60+24*2,600,24,"Һ����ʾģ��",24,1,BLACK);
	Show_Str(30,60+24*3,600,24,"������ʾ�ն�",24,1,BLACK);
	Show_Str(30,60+24*4,600,24,"��ʾ�������",24,1,BLACK);
	Show_Str(lcddev.width-40,lcddev.height-20,50,16,"����",16,1,BLUE);  //��ʾ16*16����
	while(1)
	{
		if(AUTO==1)loop++; //���û�д����������������ʵ��ѭ������ͼƬ
		if(((Keypad=py_get_keynum())>0)||(loop>DelayTime))//����λ��ɨ�裬��������
		{
			if(loop>DelayTime) { Keypad=KEYdown;loop=0;}
	
			     if(Keypad==KEYup)   {if(ix>0)  ix--;} //�������ϵİ���
			else if(Keypad==KEYdown) {if(ix<12) ix++;}//�������µİ���
			
			if(ix>12)ix=0;
			
			Contflag=1; //��ʼ��ʱ
			switch(ix)//����ת��
			{
				case 1:LCD_Clear(RED);   POINT_COLOR=WHITE;	Show_Str(10,10,200,16,"����ɫ��ʾ����ɫ��",16,1,GREEN);                  break;
				case 2:LCD_Clear(GREEN); POINT_COLOR=BLACK;	Show_Str(10,10,200,16,"����ɫ��ʾ����ɫ��",16,1,RED);                    break;
				case 3:LCD_Clear(BLUE);  POINT_COLOR=RED;   Show_Str(10,10,200,16,"����ɫ��ʾ����ɫ��",16,1,RED);                    break;
				case 4:LCD_Clear(BLACK); POINT_COLOR=WHITE; Show_Str(10,10,200,16,"��ɫ",16,1,RED);                								   break;
				case 5:LCD_Clear(WHITE); POINT_COLOR=BLACK; Show_Str(10,10,200,16,"��ɫ",16,1,RED);      Olddir=lcddev.dir;          break;
				case 6:sendicon(0,0,lcddev.width,lcddev.height,(pic_ad+off_ad)+(lcddev.width*lcddev.height)*2*0, lcddev.width,lcddev.height*2, buffpic);
				       break;
				case 7:sendicon(0,0,lcddev.width,lcddev.height,(pic_ad+off_ad)+(lcddev.width*lcddev.height)*2*1, lcddev.width,lcddev.height*2, buffpic);
				       break;
				case 8:sendicon(0,0,lcddev.width,lcddev.height,(pic_ad+off_ad)+(lcddev.width*lcddev.height)*2*2, lcddev.width,lcddev.height*2, buffpic);
				       break;
				case 9:sendicon(0,0,lcddev.width,lcddev.height,(pic_ad+off_ad)+(lcddev.width*lcddev.height)*2*3, lcddev.width,lcddev.height*2, buffpic);
				       break;
				case 10:sendicon(0,0,lcddev.width,lcddev.height,(pic_ad+off_ad)+(lcddev.width*lcddev.height)*2*4, lcddev.width,lcddev.height*2, buffpic);
		           free(buffpic);
			         break;
			  			  			  			  		
			  case 11:LCD_Clear(WHITE); 
				        Show_Str(0,0,lcddev.width,lcddev.height,"    �㶫ʡ���ǻտƼ�������һ�Ҽ��з�������������Ϊһ��ĿƼ�����ҵ��" 
				                                                 "��˾רҵ����0.68Ӣ��-15.6Ӣ��Һ����ʾ������������������ʾ�����ṩ��ʾ���������"
				                                                 "��Ʒ�㷺Ӧ���ڹ�ҵ�����ء�ҽ�ơ��ҵ硢�����������ܼҾӵȸ��и�ҵ��"
				                                                 "�������5000��M2,ӵ��5��ȫ�Զ������ߣ�ÿ�±��Ͳ���2KK."
				                                                 " ��˾ӵ����ҵ������з��Ŷ�10���ˣ�������Ա��ҵ����15�����ϣ��ܿ����ṩ������ʾ����,������̿ͻ��Ŀ������ڡ�"
				                                                 "��˾���첿���豸����ʦ�Ŷӣ���ҵ����15�����ϡ�"
				                                                 "��˾ӵ��15�˵�Ʒ���Ŷӣ��ڸ��������ϸ�ѹأ�Ϊ����Ʒ�ʱ��ݻ�����"
				                                                 "��˾��ӵ��30���˵������Ŷӣ��ֹ����г����͹����г����������š�"
				                                                 "��˾ͨ����ISO9001����������ϵ��֤��ӵ�����ƵĹ����ƶȡ�"
				                                                 "�������ۺ�ļ���ʵ����ǿ����������������ʵķ���������"
				                                                 "Ϊ�ͻ��ṩ���Լ۱ȵĲ�Ʒ�ͷ����ǹ�˾���ľ�������"
				                                                 "��л�Ͽͻ�һֱ������֧�֣�Ҳ��ӭԽ��Խ���¿ͻ��ļ��롣"			
				                                                 "���ǻ��ڴ���־ͬ���ϵĿͻ�һ��ɳ������ٹ�Ӯ��"
				                                                 "��˾��ַ:wwww.eya-display.com",16,1,BLACK);
			
				        if(AUTO==1) ix=0; //���û�д������Ͳ���Ҫ���Դ����Ļ�����
				        break;
				case 12:Load_Drow_Dialog();Show_Str(10,10,100,16,"��������",16,1,RED);
							  if (tp_dev.touchtype & 0X80)
							  {
								  ctp_test(); ix=0; /* ���������� */
							  }
							  else
							  {
								  rtp_test(); ix=0; /* ���������� */
							  }
								break;
		   }
			Contflag=0;//ֹͣ��ʱ
			LCD_ShowNum(lcddev.width-35,5,Counter*5,3,12,BLACK);
			LCD_ShowString(lcddev.width-17,5,24,12,12,"MS",BLACK); //��ʾˢͼʱ��
			printf("ˢͼʱ���ǣ�%d ms\r\n",Counter*5);
			printf("ix===%d\r\n",ix);
			Counter=0;//�����ʱ��
			ShowUI(ix);
		 }
	//////////////////////////////////////////���¿�ʼLCD���ܲ��� ����///////////////////////////////////////
  }
}
