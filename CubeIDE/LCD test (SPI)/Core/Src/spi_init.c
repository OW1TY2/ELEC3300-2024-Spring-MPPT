#include "spi_init.h"

SPI_HandleTypeDef SPI_InitStructure;

void SPI1_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  __HAL_RCC_SPI1_CLK_ENABLE(); //����SPI1����ʱ��
  __HAL_RCC_GPIOA_CLK_ENABLE();//����GPIO��ʱ��
    
  GPIO_InitStructure.Pin=LCD_SCK_GPIO_PIN;
  GPIO_InitStructure.Mode=GPIO_MODE_AF_PP;
  GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LCD_SCK_GPIO_PORT,&GPIO_InitStructure);
  HAL_GPIO_WritePin(LCD_SCK_GPIO_PORT,LCD_SCK_GPIO_PIN,GPIO_PIN_SET);
    
  GPIO_InitStructure.Pin=LCD_MOSI_GPIO_PIN;
  GPIO_InitStructure.Mode=GPIO_MODE_AF_PP;
  GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LCD_MOSI_GPIO_PORT,&GPIO_InitStructure);
  HAL_GPIO_WritePin(LCD_MOSI_GPIO_PORT,LCD_MOSI_GPIO_PIN,GPIO_PIN_SET);
  
  SPI_InitStructure.Instance=SPI1;
  SPI_InitStructure.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_2;//SPI1������APB2�������� Ƶ��72Mhz 2��ƵΪ36Mhz
  SPI_InitStructure.Init.CLKPhase=SPI_PHASE_2EDGE;//SPI�ڵڶ���ʱ���ؽ��в���
  SPI_InitStructure.Init.CLKPolarity=SPI_POLARITY_HIGH;//SPI����Ϊ��
  SPI_InitStructure.Init.CRCCalculation=SPI_CRCCALCULATION_DISABLE;//�ر�CRCУ��
  SPI_InitStructure.Init.DataSize=SPI_DATASIZE_8BIT;//SPI֡����Ϊ8bit
  SPI_InitStructure.Init.Direction=SPI_DIRECTION_1LINE;//SPI����ģʽ
  SPI_InitStructure.Init.FirstBit=SPI_FIRSTBIT_MSB;//��λ��ǰ
  SPI_InitStructure.Init.Mode=SPI_MODE_MASTER;//����������ģʽ
  SPI_InitStructure.Init.NSS=SPI_NSS_SOFT;//Ƭѡ�źŽ����������
  SPI_InitStructure.Init.TIMode=SPI_TIMODE_DISABLE;//�ر�TIģʽ
  HAL_SPI_Init(&SPI_InitStructure);
  __HAL_SPI_ENABLE(&SPI_InitStructure);
}
void LCD_GPIOInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  SPI1_Init();
  GPIO_InitStructure.Pin=LCD_RES_GPIO_PIN;
  GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LCD_RES_GPIO_PORT,&GPIO_InitStructure);
  HAL_GPIO_WritePin(LCD_RES_GPIO_PORT,LCD_RES_GPIO_PIN,GPIO_PIN_SET);
    
  GPIO_InitStructure.Pin=LCD_DC_GPIO_PIN;
  GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LCD_DC_GPIO_PORT,&GPIO_InitStructure);
  HAL_GPIO_WritePin(LCD_DC_GPIO_PORT,LCD_DC_GPIO_PIN,GPIO_PIN_SET);
  
  GPIO_InitStructure.Pin=LCD_CS_GPIO_PIN;
  GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LCD_CS_GPIO_PORT,&GPIO_InitStructure);
  HAL_GPIO_WritePin(LCD_CS_GPIO_PORT,LCD_CS_GPIO_PIN,GPIO_PIN_SET);
  
  GPIO_InitStructure.Pin=LCD_BLK_GPIO_PIN;
  GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LCD_BLK_GPIO_PORT,&GPIO_InitStructure);
  HAL_GPIO_WritePin(LCD_BLK_GPIO_PORT,LCD_BLK_GPIO_PIN,GPIO_PIN_SET);
}

/********************************************
����˵����ģ��SPI����һ���ֽ�����
��ڲ�����dat->��Ҫ���͵�����
���ز�������
********************************************/
void LCD_WR_Bus(u8 dat)
{
  LCD_CS_Clr();
  HAL_SPI_Transmit_DMA(&SPI_InitStructure,&dat,1);
  LCD_CS_Set();
}


/********************************************
����˵����дLCDָ��
��ڲ�����reg->��Ҫ���͵�ָ��
���ز�������
********************************************/
void LCD_WR_REG(u8 reg)
{
  LCD_DC_Clr();
  LCD_WR_Bus(reg);
  LCD_DC_Set();
}

/********************************************
����˵����дLCDһ���ֽڳ�������
��ڲ�����dat->��Ҫ���͵�����
���ز�������
********************************************/
void LCD_WR_DATA8(u8 dat)
{
  LCD_WR_Bus(dat);
}

/********************************************
����˵����дLCDһ�����ֳ�������
��ڲ�����dat->��Ҫ���͵�����
���ز�������
********************************************/
void LCD_WR_DATA(u16 dat)
{
  LCD_WR_Bus(dat>>8);
  LCD_WR_Bus(dat&0xFF);
}



