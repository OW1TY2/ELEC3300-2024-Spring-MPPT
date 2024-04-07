/**
 ****************************************************************************************************
 * @file        cst3xx.c
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
#include "cst3xx.h"
#include "touch.h"
#include "ctiic.h"
#include "usart.h"
#include "delay.h" 
#include "string.h" 
#include "lcd.h" 

u8 CST_IIC_WR=CST328_CMD_WR,CST_IIC_RD=CST328_CMD_RD;//Ĭ��IIC��ַ��CST328

//��CST3XXд��һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:д���ݳ���
//����ֵ:0,�ɹ�;1,ʧ��.
u8 CST3XX_WR_Reg(u16 reg,u8 *buf,u8 len)
{
	u8 i;
	u8 ret=0;
	CT_IIC_Start();	
 	CT_IIC_Send_Byte(CST_IIC_WR);   	//����д���� 	 
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(reg>>8);   	//���͸�8λ��ַ
	CT_IIC_Wait_Ack(); 	 										  		   
	CT_IIC_Send_Byte(reg&0XFF);   	//���͵�8λ��ַ
	CT_IIC_Wait_Ack();  
	for(i=0;i<len;i++)
	{	   
    	CT_IIC_Send_Byte(buf[i]);  	//������
		ret=CT_IIC_Wait_Ack();
		if(ret)break;  
	}
    CT_IIC_Stop();					//����һ��ֹͣ����	    
	return ret; 
}
//��CST3XX����һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:�����ݳ���			  
void CST3XX_RD_Reg(u16 reg,u8 *buf,u8 len)
{
	u8 i; 
 	CT_IIC_Start();	
 	CT_IIC_Send_Byte(CST_IIC_WR);   //����д���� 	 
	CT_IIC_Wait_Ack();
 	CT_IIC_Send_Byte(reg>>8);   	//���͸�8λ��ַ
	CT_IIC_Wait_Ack(); 	 										  		   
 	CT_IIC_Send_Byte(reg&0XFF);   	//���͵�8λ��ַ
	CT_IIC_Wait_Ack();  
 	CT_IIC_Start();  	 	   
	CT_IIC_Send_Byte(CST_IIC_RD);   //���Ͷ�����		   
	CT_IIC_Wait_Ack();	   
	for(i=0;i<len;i++)
	{	   
    	buf[i]=CT_IIC_Read_Byte(i==(len-1)?0:1); //������	  
	} 
    CT_IIC_Stop();//����һ��ֹͣ����    
} 
//��ʼ��CST3XX������
//����ֵ:0,��ʼ���ɹ�;1,��ʼ��ʧ�� 
u8 CST3XX_Init(void)
{
	u8 temp[5]; 
	GPIO_InitTypeDef  GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PC�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_14|GPIO_Pin_15;// PC14��PC15�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_14|GPIO_Pin_15);//���1

 	CT_IIC_Init();  //��ʼ����������I2C����  
	CST_RST=0;				//��λ
	delay_ms(10);
 	CST_RST=1;				//�ͷŸ�λ 
 	delay_ms(10);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;			//PC15�˿�����
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;		//��������
	GPIO_Init(GPIOC, &GPIO_InitStructure);			  //PC15��������
	GPIO_ResetBits(GPIOC,GPIO_Pin_15);				    //����	

 	delay_ms(100);
	CST3XX_WR_Reg(0xD101,temp,4);
	CST3XX_RD_Reg(CST_PID_REG,temp,4);//��ȡ��ƷID
	if((temp[3]==0x01)&&(temp[2]==0x48)) return 0;
	
	CST_IIC_WR=CST3240_CMD_WR;
	CST_IIC_RD=CST3240_CMD_RD;
	CST3XX_WR_Reg(0xD101,temp,4);
	CST3XX_RD_Reg(CST_PID_REG,temp,4);//��ȡ��ƷID  ��ȡ��3240
	if((temp[3]==0x32)&&(temp[2]==0x40)) return 0;
	//printf("CTP ID:0x%x\r\n",temp[0]);	//��ӡID 
	//printf("CTP ID:0x%x\r\n",temp[1]);
	//printf("CTP ID:0x%x\r\n",temp[2]);
	//printf("CTP ID:0x%x\r\n",temp[3]);
	return 1;
}
const u16 CST3XX_TPX_TBL[5]={CST_TP1_REG,CST_TP2_REG,CST_TP3_REG,CST_TP4_REG,CST_TP5_REG};
//ɨ�败����(���ò�ѯ��ʽ)
//mode:0,����ɨ��.
//����ֵ:��ǰ����״̬.
//0,�����޴���;1,�����д���
u8 CST3XX_Scan(u8 mode)
{
	u8 buf[4];
	u8 i=0;
	u8 res=0;
	u8 temp;
	static u8 t=0;//���Ʋ�ѯ���,�Ӷ�����CPUռ����   
	t++;
	if((t%10)==0||t<10)//����ʱ,ÿ����10��CTP_Scan�����ż��1��,�Ӷ���ʡCPUʹ����
	{
		CST3XX_RD_Reg(CST_GSTID_REG,&mode,1);//��ȡ�������״̬ 
		//printf("mode:0x%x\r\n",mode);
		if((mode&0XF)&&((mode&0XF)<6))
		{
			temp=0XFF<<(mode&0XF);//����ĸ���ת��Ϊ1��λ��,ƥ��tp_dev.sta���� 
			tp_dev.sta=(~temp)|TP_PRES_DOWN|TP_CATH_PRES; 
			for(i=0;i<5;i++)
			{
				if(tp_dev.sta&(1<<i))	//������Ч?
				{
					CST3XX_RD_Reg(CST3XX_TPX_TBL[i],buf,4);	//��ȡXY����ֵ
					if(lcddev.dir==0)	//����
					{
						tp_dev.x[i]=((u16)buf[0]<<4)+(((u16)buf[2]>>4)&0x0F);
						tp_dev.y[i]=(((u16)buf[1]<<4)+((u16)buf[2]&0x0f));
					}else //����
					{
						tp_dev.y[i]=((u16)buf[0]<<4)+(((u16)buf[2]>>4)&0x0F);
						tp_dev.x[i]=lcddev.width-(((u16)buf[3]<<8)+buf[2]);
					}  
					printf("x[%d]:%d,y[%d]:%d\r\n",i,tp_dev.x[i],i,tp_dev.y[i]);//���ڴ�ӡ���꣬���ڵ���
				}			
			} 
			res=1;
			if(tp_dev.x[0]==0 && tp_dev.y[0]==0)mode=0;	//���������ݶ���0,����Դ˴�����
			t=0;		//����һ��,��������������10��,�Ӷ����������
		}
 		if((mode&0XF)<6)
		{
			temp=0;
			CST3XX_WR_Reg(CST_GSTID_REG,&temp,1);//���־ 		
		}
	}
	if((mode&0X0F)==0X00)//�޴����㰴��
	{ 
		if(tp_dev.sta&TP_PRES_DOWN)	//֮ǰ�Ǳ����µ�
		{
			tp_dev.sta&=~(1<<7);	//��ǰ����ɿ�
		}else						//֮ǰ��û�б�����
		{ 
			tp_dev.x[0]=0xffff;
			tp_dev.y[0]=0xffff;
			tp_dev.sta&=0XE0;	//�������Ч���	
		}	 
	} 	
	if(t>240)t=10;//���´�10��ʼ����
	return res;
}
 

























