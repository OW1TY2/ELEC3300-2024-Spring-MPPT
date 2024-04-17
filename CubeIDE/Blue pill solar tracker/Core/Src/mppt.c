#include "mppt.h"

int prev_VOL_IN = 0;
int prev_CUR_IN = 0;
int prev_PWR_IN = 0;
int prev_VOL_OUT = 0;
int prev_CUR_OUT = 0;
int prev_PWR_OUT = 0;
uint32_t prev_PWM_OUTPUT[2] = {0, 0};

void MPPT_calculate(int VOL_IN, int CUR_IN, int VOL_OUT, int CUR_OUT, uint32_t *PWM_OUTPUT) {
    // MPPT algorithm
    
    long PWR_IN = VOL_IN * CUR_IN;
    long PWR_OUT = VOL_OUT * CUR_OUT;
    int PWR_OUT_isIncreased = PWR_OUT > prev_PWR_OUT;
    int PWM_wasIncreased = prev_PWM_OUTPUT[0] > prev_PWM_OUTPUT[1];
    if (PWR_OUT_isIncreased && PWM_wasIncreased) {
        *PWM_OUTPUT += 1;
    } else if (!PWR_OUT_isIncreased && !PWM_wasIncreased) {
        *PWM_OUTPUT += 1;
    } else if (PWR_OUT_isIncreased && !PWM_wasIncreased) {
        *PWM_OUTPUT -= 1;
    } else if (!PWR_OUT_isIncreased && PWM_wasIncreased) {
        *PWM_OUTPUT -= 1;
    }

    prev_VOL_IN = VOL_IN;
    prev_CUR_IN = CUR_IN;
    prev_VOL_OUT = VOL_OUT;
    prev_CUR_OUT = CUR_OUT;
    prev_PWM_OUTPUT[1] = prev_PWM_OUTPUT[0];
    prev_PWM_OUTPUT[0] = *PWM_OUTPUT;
    // *PWM_OUTPUT = ...
}