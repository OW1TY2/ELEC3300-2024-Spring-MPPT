/**
 ****************************************************************************************************
 * @file        w25qxx.c
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
#include "w25qxx.h" 
#include "spi1.h"
#include "delay.h"
#include "usart.h"
#include "stm32f10x_spi.h"
#include "lcd.h"
#include "SPI2.h"

u16 W25QXX_TYPE=W25Q128;	//Ĭ����W25Q128
extern u8 Olddir;
//4KbytesΪһ��Sector
//16������Ϊ1��Block
//W25Q128
//����Ϊ16M�ֽ�,����128��Block,4096��Sector 
													 
//��ʼ��SPI FLASH��IO��
//FLASH����SPI1�� 
void W25QXX_Init(void)
{	
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );//PORTAʱ��ʹ�� 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;  // PA4 ���� 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOA,GPIO_Pin_4);
 
	SPI1_Init();		   	//��ʼ��SPI
	SPI1_SetSpeed(SPI_BaudRatePrescaler_2);//����Ϊ18Mʱ��,����ģʽ
	W25QXX_TYPE=W25QXX_ReadID();//��ȡFLASH ID. 
	//DMA1_Spi2_Init();
  if(W25QXX_TYPE == 0x5e17) printf("оƬ�ͺ�ZB25VQ128ASIG\r\n\r\n");

}  

//��ȡW25QXX��״̬�Ĵ���
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
//TB,BP2,BP1,BP0:FLASH����д��������
//WEL:дʹ������
//BUSY:æ���λ(1,æ;0,����)
//Ĭ��:0x00
u8 W25QXX_ReadSR(void)   
{  
	u8 byte=0;   
	W25QXX_CS=0;                            //ʹ������   
	SPI1_ReadWriteByte(W25X_ReadStatusReg); //���Ͷ�ȡ״̬�Ĵ�������    
	byte=SPI1_ReadWriteByte(0Xff);          //��ȡһ���ֽ�  
	W25QXX_CS=1;                            //ȡ��Ƭѡ     
	return byte;     
} 
//дW25QXX״̬�Ĵ���
//ֻ��SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
void W25QXX_Write_SR(u8 sr)   
{   
	W25QXX_CS=0;                            //ʹ������   
	SPI1_ReadWriteByte(W25X_WriteStatusReg);//����дȡ״̬�Ĵ�������    
	SPI1_ReadWriteByte(sr);               	//д��һ���ֽ�  
	W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
}   
//W25QXXдʹ��	
//��WEL��λ   
void W25QXX_Write_Enable(void)   
{
	W25QXX_CS=0;                          	//ʹ������   
    SPI1_ReadWriteByte(W25X_WriteEnable); 	//����дʹ��  
	W25QXX_CS=1;                           	//ȡ��Ƭѡ     	      
} 
//W25QXXд��ֹ	
//��WEL����  
void W25QXX_Write_Disable(void)   
{  
	W25QXX_CS=0;                            //ʹ������   
    SPI1_ReadWriteByte(W25X_WriteDisable);  //����д��ָֹ��    
	W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
} 		
//��ȡоƬID
//����ֵ����:				   
//0XEF13,��ʾоƬ�ͺ�ΪW25Q80  
//0XEF14,��ʾоƬ�ͺ�ΪW25Q16    
//0XEF15,��ʾоƬ�ͺ�ΪW25Q32  
//0XEF16,��ʾоƬ�ͺ�ΪW25Q64 
//0XEF17,��ʾоƬ�ͺ�ΪW25Q128 	  
u16 W25QXX_ReadID(void)
{
	u16 Temp = 0;	  
	W25QXX_CS=0;				    
	SPI1_ReadWriteByte(0x90);//���Ͷ�ȡID����	    
	SPI1_ReadWriteByte(0x00); 	    
	SPI1_ReadWriteByte(0x00); 	    
	SPI1_ReadWriteByte(0x00); 	 			   
	Temp|=SPI1_ReadWriteByte(0xFF)<<8;  
	Temp|=SPI1_ReadWriteByte(0xFF);	 
	W25QXX_CS=1;				    
	return Temp;
}   		    
//��ȡSPI FLASH  
//��ָ����ַ��ʼ��ȡָ�����ȵ�����
//pBuffer:���ݴ洢��
//ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
//NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   
{   	
	W25QXX_CS=0;                            	  //ʹ������   
	SPI1_ReadWriteByte(W25X_ReadData);         	//���Ͷ�ȡ����   
	SPI1_ReadWriteByte((u8)((ReadAddr)>>16));  	//����24bit��ַ    
	SPI1_ReadWriteByte((u8)((ReadAddr)>>8));   
	SPI1_ReadWriteByte((u8)ReadAddr);  
// ��DMA����	
//	for(i=0;i<NumByteToRead;i++)
//	{ 
//				pBuffer[i]=SPI2_ReadWriteByte(0XFF);   	//ѭ������  
//	}
	//*********DMA����*************************************/
   DMA1_Spi1_RX(pBuffer,NumByteToRead);
//*****************************************************/
	W25QXX_CS=1;  				    	      
}  

//SPI��һҳ(0~65535)��д������256���ֽڵ�����
//��ָ����ַ��ʼд�����256�ֽڵ�����
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!	 
void W25QXX_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
 	  u16 i;  
    W25QXX_Write_Enable();                  	  //SET WEL 
	  W25QXX_CS=0;                            	  //ʹ������   
    SPI1_ReadWriteByte(W25X_PageProgram);      	//����дҳ����   
    SPI1_ReadWriteByte((u8)((WriteAddr)>>16)); 	//����24bit��ַ    
    SPI1_ReadWriteByte((u8)((WriteAddr)>>8));   
    SPI1_ReadWriteByte((u8)WriteAddr);   
    for(i=0;i<NumByteToWrite;i++)SPI1_ReadWriteByte(pBuffer[i]);//ѭ��д��  
	  W25QXX_CS=1;                            	//ȡ��Ƭѡ 
	  W25QXX_Wait_Busy();					   		        //�ȴ�д�����
} 
//�޼���дSPI FLASH 
//����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
//�����Զ���ҳ���� 
//��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)
//CHECK OK
void W25QXX_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 			 		 
	u16 pageremain;	   
	pageremain=256-WriteAddr%256; //��ҳʣ����ֽ���		 	    
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//������256���ֽ�
	while(1)
	{	   
		W25QXX_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//д�������
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite-=pageremain;			  //��ȥ�Ѿ�д���˵��ֽ���
			if(NumByteToWrite>256)pageremain=256; //һ�ο���д��256���ֽ�
			else pageremain=NumByteToWrite; 	  //����256���ֽ���
		}
	};	    
} 
//дSPI FLASH  
//��ָ����ַ��ʼд��ָ�����ȵ�����
//�ú�������������!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)						
//NumByteToWrite:Ҫд����ֽ���(���65535)   
u8 W25QXX_BUFFER[4096];		 
void W25QXX_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 
	u32 secpos;
	u16 secoff;
	u16 secremain;	   
 	u16 i;    
	u8 * W25QXX_BUF;	  
  W25QXX_BUF=W25QXX_BUFFER;	     
 	secpos=WriteAddr/4096;//������ַ  
	secoff=WriteAddr%4096;//�������ڵ�ƫ��
	secremain=4096-secoff;//����ʣ��ռ��С   
 	//printf("ad:%X,nb:%X\r\n",WriteAddr,NumByteToWrite);//������
 	if(NumByteToWrite<=secremain)secremain=NumByteToWrite;//������4096���ֽ�
	while(1) 
	{	
		W25QXX_Read(W25QXX_BUF,secpos*4096,4096);//������������������
		for(i=0;i<secremain;i++)//У������
		{
			if(W25QXX_BUF[secoff+i]!=0XFF)break;//��Ҫ����  	  
		}
		if(i<secremain)//��Ҫ����
		{
			W25QXX_Erase_Sector(secpos);		//�����������
			for(i=0;i<secremain;i++)	   		//����
			{
				W25QXX_BUF[i+secoff]=pBuffer[i];	  
			}
			W25QXX_Write_NoCheck(W25QXX_BUF,secpos*4096,4096);//д����������  

		}else W25QXX_Write_NoCheck(pBuffer,WriteAddr,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
		if(NumByteToWrite==secremain)break;//д�������
		else//д��δ����
		{
			secpos++;//������ַ��1
			secoff=0;//ƫ��λ��Ϊ0 	 

		   	pBuffer+=secremain;  				//ָ��ƫ��
			  WriteAddr+=secremain;				//д��ַƫ��	   
		   	NumByteToWrite-=secremain;			//�ֽ����ݼ�
			if(NumByteToWrite>4096)secremain=4096;//��һ����������д����
			else secremain=NumByteToWrite;		//��һ����������д����
		}	 
	};	 
}
//��������оƬ		  
//�ȴ�ʱ�䳬��...
void W25QXX_Erase_Chip(void)   
{                                 
    W25QXX_Write_Enable();                 	 	   //SET WEL 
    W25QXX_Wait_Busy();   
  	W25QXX_CS=0;                            	  //ʹ������   
    SPI1_ReadWriteByte(W25X_ChipErase);        	//����Ƭ��������  
	  W25QXX_CS=1;                                //ȡ��Ƭѡ     	      
	  W25QXX_Wait_Busy();   				   		        //�ȴ�оƬ��������
}   
//����һ������
//Dst_Addr:������ַ ����ʵ����������
//����һ������������ʱ��:150ms
void W25QXX_Erase_Sector(u32 Dst_Addr)   
{  
	//����falsh�������,������   
 	//printf("fe:%x\r\n",Dst_Addr);	  
 	  Dst_Addr*=4096;
    W25QXX_Write_Enable();                  	//SET WEL 	 
    W25QXX_Wait_Busy();   
  	W25QXX_CS=0;                            	//ʹ������   
    SPI1_ReadWriteByte(W25X_SectorErase);      	//������������ָ�� 
    SPI1_ReadWriteByte((u8)((Dst_Addr)>>16));  	//����24bit��ַ    
    SPI1_ReadWriteByte((u8)((Dst_Addr)>>8));   
    SPI1_ReadWriteByte((u8)Dst_Addr);  
	  W25QXX_CS=1;                            	//ȡ��Ƭѡ     	      
    W25QXX_Wait_Busy();   				   		//�ȴ��������
}  
//�ȴ�����
void W25QXX_Wait_Busy(void)   
{   
	while((W25QXX_ReadSR()&0x01)==0x01);  		// �ȴ�BUSYλ���
}  
//�������ģʽ
void W25QXX_PowerDown(void)   
{ 
  	W25QXX_CS=0;                           	 	//ʹ������   
    SPI1_ReadWriteByte(W25X_PowerDown);        //���͵�������  
	  W25QXX_CS=1;                            	//ȡ��Ƭѡ     	      
    delay_us(3);                               //�ȴ�TPD  
}   
//����
void W25QXX_WAKEUP(void)   
{  
  	W25QXX_CS=0;                            	//ʹ������   
    SPI1_ReadWriteByte(W25X_ReleasePowerDown);	//  send W25X_PowerDown command 0xAB    
	  W25QXX_CS=1;                            	//ȡ��Ƭѡ     	      
    delay_us(3);                            	//�ȴ�TRES1
}   


// ����.ͼ�곤��.ͼ���ַ.ѭ������.��ȡ����
void sendicon(u16 x,u16 y,u16 width,u16 height,u32 ad,u16 loop,u16 count,u8 *tempsys)
{
	u32 i,j,k;
	u16 bu,Swap;
	if(Olddir==0)
	{
		LCD_Display_Dir(1);//��ΪͼƬȡģ�Ǻ���ȡģ�ģ������ǰ������ģʽ������Ҫ��ת�ɺ���  �к�������Ҫ�л�
		Swap=width;
		width=height;
		height=Swap;
	}
	LCD_Set_Window(x,y,width,height);
	//LCD_SetCursor(x,y);              //���ù��λ��  
	LCD_WriteRAM_Prepare();   	       //��ʼд��GRAM
	LCD_RS=1;
	LCD_CS=0;
	j = ad;
	for(i=0; i<loop; i++)
	{
		W25QXX_Read(tempsys,j,count); 
		j  += count;		
		for(k=0;k<count;k+=2)
		{ 
		 	 bu  = tempsys[k+1] << 8;
			 bu |= tempsys[k];

#if(FAST==0)			
			 LCD_WriteRAM(bu);
#else	
			//ʹ�����´����������
#if(Interface==I80_16BIT)	
	  DATAOUT(bu);
		LCD_WR=0;
		LCD_WR=1;
#elif(Interface==D4WSPI)	
		SPI2_ReadWriteByte(bu>>8);
		SPI2_ReadWriteByte(bu);
#else
	  DATAOUT(bu>>8);
		LCD_WR=0;
		LCD_WR=1;
		DATAOUT(bu);
		LCD_WR=0;
		LCD_WR=1;
#endif
#endif
		}

	}
	LCD_Set_Window(0,0,lcddev.width,lcddev.height);//�ͷŴ���
	if((Olddir==0)&&(lcddev.dir==1))LCD_Display_Dir(0);//���֮ǰ������������Ϊ����ʾͼƬǿ��ת�ɺ����ģ�����Ҫ��ԭ������
	
}















