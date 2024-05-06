#ifndef _DMA_H_
#define _DMA_H_

#include "spi_init.h"

void MYDMA_Config(DMA_Channel_TypeDef*DMA_CHx);//≈‰÷√DMA1_CHx
void MYDMA_Config1(DMA_Channel_TypeDef* DMA_CHx);//≈‰÷√DMA1_CHx
void MYDMA_Enable(u32 SrcAddress, u32 DstAddress, u32 DataLength);

#endif



