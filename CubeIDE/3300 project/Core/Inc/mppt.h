#ifndef MPPT_H
#define MPPT_H

#include "stm32f1xx_hal.h"

void MPPT_calculate(int VOL_IN, int CUR_IN, int VOL_OUT, int CUR_OUT, uint32_t *PWM_OUTPUT);

#endif // MPPT_H