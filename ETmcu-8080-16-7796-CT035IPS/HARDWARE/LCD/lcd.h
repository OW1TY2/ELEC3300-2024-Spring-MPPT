/**
 ****************************************************************************************************
 * @file        lcd.h
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
 #ifndef __LCD_H
#define __LCD_H		
#include "sys.h"	 
#include "stdlib.h"


/*****************************************��Ҫ�޸ĵĵط� 1 ***************************/
#define LCD_WIDTH  320
#define LCD_HEIGHT 480   //������Ļ��Ӧ�޸ķֱ��� 

/*****************************************��Ҫ�޸ĵĵط� 2 ***************************/

#define Interface  I80_16BIT    //I80_16BIT//I80_H8BIT//I80_L8BIT//D4WSPI  //��Ӧ��ʾ���Ľӿ�
//#define Interface  I80_H8BIT
//#define Interface  I80_L8BIT
//#define Interface  D4WSPI

/*****************************************��Ҫ�޸ĵĵط� 3 ***************************/
//�������޸���LCD.C�� LCD_INIT_CODE()  30�п�ʼ

/*****************************************��Ҫ�޸ĵĵط� 4 ***************************/
//�������л�
#define Landscape  1 //1:����ʾ  0������ʾ  PS:��������FPC�ĳ��߷�������  

/*****************************************��Ҫ�޸ĵĵط� 5 ***************************/
#define RGB 0x00
#define BGR 0x08
#define COLORORDER BGR  //RGB BGR�л��������ʾ��ɫ����ɫ���ˣ�����ͨ���л��������������




#define FAST     1  //����ˢͼ  1:����ˢͼ  0����ˢ   ��ˢ����ˢ��24%


//LCD��Ҫ������
typedef struct  
{										    
	u16 width;			//LCD ���
	u16 height;			//LCD �߶�
	u16 id;				  //LCD ID
	u8  dir;			  //���������������ƣ�0��������1��������	
	u8	wramcmd;		//��ʼдgramָ��
	u8  setxcmd;		//����x����ָ��
	u8  setycmd;		//����y����ָ��	 
}_lcd_dev; 	  

//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����
//LCD�Ļ�����ɫ�ͱ���ɫ	   
extern u16  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern u16  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ
//////////////////////////////////////////////////////////////////////////////////	 
//-----------------LCD�˿ڶ���---------------- 
#define	LCD_LED PAout(3)   //LCD    		 BL_EN 

#define	LCD_RST PCout(13)   //LCD    		 RESET
#if(Interface==D4WSPI)
	#define	LCD_CS  PBout(12)  //LCD spi�ӿڵ�CS�������
#else
	#define	LCD_CS  PAout(8)   //LCD   		 CS
#endif

#define	LCD_RS  PAout(11)   //LCD   		 RS
#define	LCD_WR  PAout(12)   //LCD     	 WR
#define	LCD_RD  PAout(15)   //LCD    		 RD
	 
//ɨ�跽����
#define L2R_U2D  0 //������,���ϵ���
#define L2R_D2U  1 //������,���µ���
#define R2L_U2D  2 //���ҵ���,���ϵ���
#define R2L_D2U  3 //���ҵ���,���µ���

#define U2D_L2R  4 //���ϵ���,������
#define U2D_R2L  5 //���ϵ���,���ҵ���
#define D2U_L2R  6 //���µ���,������
#define D2U_R2L  7 //���µ���,���ҵ���	 

extern u8 DFT_SCAN_DIR;


//PB0~15,��Ϊ���ݿ�
#if((Interface==I80_16BIT)||(Interface==I80_L8BIT))
	#define DATAOUT(x) GPIOB->ODR=x; //�������
#elif(Interface==I80_H8BIT)
  #define DATAOUT(x) GPIOB->ODR=(GPIOB->ODR&0X00FF)|((u16)(x<<8)&0xFF00)    //�������
#endif

	#define DATAIN     GPIOB->IDR;   //��������
//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	   0x001F  
#define BRED             0XF81F
#define GRED 			 	     0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 //��ɫ
#define BRRED 			     0XFC07 //�غ�ɫ
#define GRAY  			     0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
//#define LIGHTGRAY      0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			     0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)
	    															  
void LCD_Init(void);													   	//��ʼ��
void LCD_DisplayOn(void);													//����ʾ
void LCD_DisplayOff(void);													//����ʾ
void LCD_Clear(u16 Color);	 												//����
void LCD_SetCursor(u16 Xpos, u16 Ypos);										//���ù��
void LCD_DrawPoint(u16 x,u16 y, uint32_t color);											//����
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color);								//���ٻ���
u16  LCD_ReadPoint(u16 x,u16 y); 											//���� 
void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color);										//��Բ
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);							//����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);		   				//������
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);		   				//��䵥ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);				//���ָ����ɫ
void LCD_ShowChar(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode, uint16_t color);						//��ʾһ���ַ�
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size,u16 color);  						//��ʾһ������
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode,u16 color);				//��ʾ ����
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p,u16 color);		//��ʾһ���ַ���,12/16����
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height);
void IO_init(void);


void LCD_WR_REG(u8);
void LCD_WR_DATA(u16);
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
u16 LCD_ReadReg(u8 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);		  
void LCD_Scan_Dir(u8 dir);							//������ɨ�跽��
void LCD_Display_Dir(u8 dir);						//������Ļ��ʾ����
void TIM2_PWM_Init(u16 arr,u16 psc);
void SendPWMval(u16 value);
 					   																			 			  		 
#endif  
	 
	 



