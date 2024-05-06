#ifndef _SPI_INIT_H_
#define _SPI_INIT_H_

#include "stm32f1xx.h"


#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long

#define LCD_SCK_GPIO_PORT    GPIOA
#define LCD_SCK_GPIO_PIN     GPIO_PIN_5

#define LCD_MOSI_GPIO_PORT    GPIOA
#define LCD_MOSI_GPIO_PIN     GPIO_PIN_7

#define LCD_RES_GPIO_PORT    GPIOE
#define LCD_RES_GPIO_PIN     GPIO_PIN_6

#define LCD_DC_GPIO_PORT     GPIOE
#define LCD_DC_GPIO_PIN      GPIO_PIN_5

#define LCD_CS_GPIO_PORT     GPIOA
#define LCD_CS_GPIO_PIN      GPIO_PIN_4

#define LCD_BLK_GPIO_PORT    GPIOC
#define LCD_BLK_GPIO_PIN     GPIO_PIN_4

#define LCD_RES_Clr() HAL_GPIO_WritePin(LCD_RES_GPIO_PORT,LCD_RES_GPIO_PIN,GPIO_PIN_RESET)
#define LCD_RES_Set() HAL_GPIO_WritePin(LCD_RES_GPIO_PORT,LCD_RES_GPIO_PIN,GPIO_PIN_SET)

#define LCD_DC_Clr() HAL_GPIO_WritePin(LCD_DC_GPIO_PORT,LCD_DC_GPIO_PIN,GPIO_PIN_RESET)
#define LCD_DC_Set() HAL_GPIO_WritePin(LCD_DC_GPIO_PORT,LCD_DC_GPIO_PIN,GPIO_PIN_SET)

#define LCD_CS_Clr() HAL_GPIO_WritePin(LCD_CS_GPIO_PORT,LCD_CS_GPIO_PIN,GPIO_PIN_RESET)
#define LCD_CS_Set() HAL_GPIO_WritePin(LCD_CS_GPIO_PORT,LCD_CS_GPIO_PIN,GPIO_PIN_SET)

#define LCD_BLK_Clr() HAL_GPIO_WritePin(LCD_BLK_GPIO_PORT,LCD_BLK_GPIO_PIN,GPIO_PIN_RESET)
#define LCD_BLK_Set() HAL_GPIO_WritePin(LCD_BLK_GPIO_PORT,LCD_BLK_GPIO_PIN,GPIO_PIN_SET)

void SPI1_Init(void);
void LCD_GPIOInit(void);
void LCD_WR_Bus(u8 dat);
void LCD_WR_REG(u8 reg);//д��ָ��
void LCD_WR_DATA8(u8 dat);//д������
void LCD_WR_DATA(u16 dat);//д������

#endif

