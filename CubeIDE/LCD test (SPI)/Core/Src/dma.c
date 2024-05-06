#include "dma.h"

DMA_HandleTypeDef DMA_InitStructure;
extern SPI_HandleTypeDef SPI_InitStructure;

void MYDMA_Config(DMA_Channel_TypeDef*DMA_CHx)
{
  __HAL_RCC_DMA1_CLK_ENABLE();//ʹ��DMAʱ��
  __HAL_LINKDMA(&SPI_InitStructure,hdmatx,DMA_InitStructure);//��SPI������DMA��������
  
  DMA_InitStructure.Instance=DMA_CHx;//����DMAͨ��
  DMA_InitStructure.Init.Direction=DMA_MEMORY_TO_PERIPH;//���ݴ��䷽����ڴ淢�͵�����
  DMA_InitStructure.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;//�洢�����ݳ���Ϊ8bit
  DMA_InitStructure.Init.MemInc=DMA_MINC_ENABLE;//�洢����ַ����
  DMA_InitStructure.Init.Mode=DMA_NORMAL;//��ͨģʽ
  DMA_InitStructure.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;//�������ݳ���Ϊ8bit
  DMA_InitStructure.Init.PeriphInc=DMA_PINC_DISABLE;//�����ַ����
  DMA_InitStructure.Init.Priority=DMA_PRIORITY_MEDIUM;//DMAͨ��ӵ�������ȼ�
  HAL_DMA_DeInit(&DMA_InitStructure);//ȡ������DMA����һ��
  HAL_DMA_Init(&DMA_InitStructure);//��ʼ��DMA����
}
void MYDMA_Config1(DMA_Channel_TypeDef* DMA_CHx)
{
  __HAL_RCC_DMA1_CLK_ENABLE();//ʹ��DMAʱ��
 __HAL_LINKDMA(&SPI_InitStructure,hdmatx,DMA_InitStructure);//��SPI������DMA������
  
  DMA_InitStructure.Instance=DMA_CHx;//����DMAͨ��
  DMA_InitStructure.Init.Direction=DMA_MEMORY_TO_PERIPH;//���ݴ��䷽����ڴ淢�͵�����
  DMA_InitStructure.Init.MemDataAlignment=DMA_MDATAALIGN_HALFWORD;//�洢�����ݳ���Ϊ16bit
  DMA_InitStructure.Init.MemInc=DMA_MINC_DISABLE;//�洢����ַ����
  DMA_InitStructure.Init.Mode=DMA_NORMAL;//��ͨģʽ
  DMA_InitStructure.Init.PeriphDataAlignment=DMA_PDATAALIGN_HALFWORD;//�������ݳ���Ϊ16bit
  DMA_InitStructure.Init.PeriphInc=DMA_PINC_DISABLE;//�����ַ����
  DMA_InitStructure.Init.Priority=DMA_PRIORITY_MEDIUM;//DMAͨ��ӵ�������ȼ�
  HAL_DMA_DeInit(&DMA_InitStructure);//ȡ������DMA����һ��
  HAL_DMA_Init(&DMA_InitStructure);//��ʼ��DMA���� 
}
/******************************************************************************
����˵����ʹ��һ��DMA����
������ݣ�SrcAddress  The source memory Buffer address      ����Դ��ַ
          DstAddress  The destination memory Buffer address Ŀ���ַ
          DataLength  �������ݳ������65535
����ֵ��  ��
******************************************************************************/
void MYDMA_Enable(u32 SrcAddress, u32 DstAddress, u32 DataLength)
{
  __HAL_DMA_DISABLE(&DMA_InitStructure);
  DMA_InitStructure.Instance->CPAR = DstAddress;
  DMA_InitStructure.Instance->CMAR = SrcAddress;//����
  DMA_InitStructure.Instance->CNDTR=DataLength;//�������ݴ�����
  SET_BIT(SPI_InitStructure.Instance->CR2,SPI_CR2_TXDMAEN); //����SPI TX DMA����
  __HAL_DMA_ENABLE(&DMA_InitStructure);
}

