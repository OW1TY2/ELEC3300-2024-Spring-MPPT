#include "lcd_init.h"


/******************************************************************************
����˵����������ʼ�ͽ�����ַ
������ݣ�x1,x2 �����е���ʼ�ͽ�����ַ
          y1,y2 �����е���ʼ�ͽ�����ַ
����ֵ��  ��
******************************************************************************/
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{
  LCD_WR_REG(0x2a);//�е�ַ����
  LCD_WR_DATA(x1);
  LCD_WR_DATA(x2);
  LCD_WR_REG(0x2b);//�е�ַ����
  LCD_WR_DATA(y1);
  LCD_WR_DATA(y2);
  LCD_WR_REG(0x2c);//������д
}

/******************************************************************************
����˵������ָ�����������ɫ
������ݣ�xsta,ysta   ��ʼ����
          xend,yend   ��ֹ����
          color       Ҫ������ɫ
����ֵ��  ��
******************************************************************************/
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{
  u16 i,j; 
  LCD_Address_Set(xsta,ysta,xend-1,yend-1);//������ʾ��Χ
  for(i=ysta;i<yend;i++)
  {
    for(j=xsta;j<xend;j++)
    {
      LCD_WR_DATA(color);
    }
  }
}


void LCD_Init(void)
{
  LCD_GPIOInit();//��ʼ��GPIO
  LCD_RES_Clr();
  HAL_Delay(10);
  LCD_RES_Clr();//��λ
  HAL_Delay(10);
  LCD_RES_Set();
  HAL_Delay(120);
  LCD_BLK_Set();//�򿪱��⣨Ĭ�Ͽ������⣩

  //************* Start Initial Sequence **********//
  LCD_WR_REG(0x11); //Sleep out 
  HAL_Delay(120);              //Delay 120ms 
  //************* Start Initial Sequence **********// 
  LCD_WR_REG(0xF0);
  	LCD_WR_DATA8(0xC3);

  	LCD_WR_REG(0xF0);
  	LCD_WR_DATA8(0x96);

  	LCD_WR_REG(0x36);    // Memory Access Control
  	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x48);
  	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0x88);
  	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x28);
  	else LCD_WR_DATA8(0xE8);

  	LCD_WR_REG(0x3A);
  	LCD_WR_DATA8(0x55);

  	LCD_WR_REG(0xB4);     //1-dot Inversion
  	LCD_WR_DATA8(0x01);

  	LCD_WR_REG(0xB1);
  	LCD_WR_DATA8(0x80);   //FRS[D7-D4], DIVA[D1-D0] 81 for 15Hz
  	LCD_WR_DATA8(0x10);   //RTNA[4:0]

  	LCD_WR_REG(0xB5);
  	LCD_WR_DATA8(0x1F);   //VFP FF for 15Hz
  	LCD_WR_DATA8(0x50);   //VBP FF for 15Hz
  	LCD_WR_DATA8(0x00);
  	LCD_WR_DATA8(0x20);   //HBP

  	LCD_WR_REG(0xB6);
  	LCD_WR_DATA8(0x8A);
  	LCD_WR_DATA8(0x07);
  	LCD_WR_DATA8(0x3B);   //480 Gates

  	LCD_WR_REG(0xC0);
  	LCD_WR_DATA8(0x80);
  	LCD_WR_DATA8(0x64); //VGH=15V VGL=-10V

  	LCD_WR_REG(0xC1);
  	LCD_WR_DATA8(0x13);  //VOP=4.5V

  	LCD_WR_REG(0xC2);
  	LCD_WR_DATA8(0xA7);

  	LCD_WR_REG(0xC5);
  	LCD_WR_DATA8(0x09);

  	LCD_WR_REG(0xE8);
  	LCD_WR_DATA8(0x40);
  	LCD_WR_DATA8(0x8a);
  	LCD_WR_DATA8(0x00);
  	LCD_WR_DATA8(0x00);
  	LCD_WR_DATA8(0x29);
  	LCD_WR_DATA8(0x19);
  	LCD_WR_DATA8(0xA5);
  	LCD_WR_DATA8(0x33);

  	LCD_WR_REG(0xE0);
  	LCD_WR_DATA8(0xF0);
  	LCD_WR_DATA8(0x06);
  	LCD_WR_DATA8(0x0B);
  	LCD_WR_DATA8(0x07);
  	LCD_WR_DATA8(0x06);
  	LCD_WR_DATA8(0x05);
  	LCD_WR_DATA8(0x2E);
  	LCD_WR_DATA8(0x33);
  	LCD_WR_DATA8(0x47);
  	LCD_WR_DATA8(0x3A);
  	LCD_WR_DATA8(0x17);
  	LCD_WR_DATA8(0x16);
  	LCD_WR_DATA8(0x2E);
  	LCD_WR_DATA8(0x31);

  	LCD_WR_REG(0xE1);
  	LCD_WR_DATA8(0xF0);
  	LCD_WR_DATA8(0x09);
  	LCD_WR_DATA8(0x0D);
  	LCD_WR_DATA8(0x09);
  	LCD_WR_DATA8(0x08);
  	LCD_WR_DATA8(0x23);
  	LCD_WR_DATA8(0x2E);
  	LCD_WR_DATA8(0x33);
  	LCD_WR_DATA8(0x46);
  	LCD_WR_DATA8(0x38);
  	LCD_WR_DATA8(0x13);
  	LCD_WR_DATA8(0x13);
  	LCD_WR_DATA8(0x2C);
  	LCD_WR_DATA8(0x32);

  	LCD_WR_REG(0xF0);
  	LCD_WR_DATA8(0x3C);

  	LCD_WR_REG(0xF0);
  	LCD_WR_DATA8(0x69);


  	LCD_WR_REG(0x2A);    //320
  	LCD_WR_DATA8(0x00);
  	LCD_WR_DATA8(0x00);
  	LCD_WR_DATA8(0x01);
  	LCD_WR_DATA8(0x3F);

  	LCD_WR_REG(0x2B);    //480
  	LCD_WR_DATA8(0x00);
  	LCD_WR_DATA8(0x00);
  	LCD_WR_DATA8(0x01);
  	LCD_WR_DATA8(0xDF);

  	LCD_WR_REG(0x35);
  	LCD_WR_DATA8(0x00);

  	LCD_WR_REG(0x11);

  	HAL_Delay(120);                //ms

  	LCD_WR_REG(0x29);
  	HAL_Delay(50);

  	LCD_WR_REG(0x21);
}









