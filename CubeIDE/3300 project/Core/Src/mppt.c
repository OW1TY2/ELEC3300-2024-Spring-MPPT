#include "mppt.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"

int prev_VOL_IN = 0;
int prev_CUR_IN = 0;
int prev_PWR_IN = 0;
int prev_VOL_OUT = 0;
int prev_CUR_OUT = 0;
int prev_PWR_OUT = 0;
uint32_t prev_PWM_OUTPUT[2] = {0, 0};
int max_output_voltage = 1850; // corresponds to 12.6V
uint32_t max_PWM_OUTPUT = 30;

void MPPT_calculate(int VOL_IN, int CUR_IN, int VOL_OUT, int CUR_OUT, uint32_t *PWM_OUTPUT) {
    // MPPT algorithm
    VOL_IN += CUR_IN * 0.01; // compensate for voltage drop
    
    long PWR_IN = VOL_IN * CUR_IN;
    // long PWR_OUT = VOL_OUT * CUR_OUT;
    int PWR_IN_isIncreased = PWR_IN >= prev_PWR_IN;
    // int PWR_OUT_isIncreased = PWR_OUT >= prev_PWR_OUT;
    int PWM_wasIncreased = prev_PWM_OUTPUT[0] >= prev_PWM_OUTPUT[1];
    int _PWM_OUTPUT = *PWM_OUTPUT;
    if (PWR_IN_isIncreased && PWM_wasIncreased) {
        _PWM_OUTPUT += 1;
    } else if (!PWR_IN_isIncreased && !PWM_wasIncreased) {
        _PWM_OUTPUT += 1;
    } else if (PWR_IN_isIncreased && !PWM_wasIncreased) {
        _PWM_OUTPUT -= 1;
    } else if (!PWR_IN_isIncreased && PWM_wasIncreased) {
        _PWM_OUTPUT -= 1;
    }
    if (VOL_OUT > max_output_voltage) {
        _PWM_OUTPUT -= 2;
        char message[30] = "Max V_Out";
        ssd1306_SetCursor(2, 18);
        ssd1306_WriteString(message, Font_6x8, Black);
        ssd1306_UpdateScreen();
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
    } else {
        char message[30] = "Boosting";
        ssd1306_SetCursor(2, 18);
        ssd1306_WriteString(message, Font_6x8, Black);
        ssd1306_UpdateScreen();
    }
    if (_PWM_OUTPUT > (int)max_PWM_OUTPUT) {
        _PWM_OUTPUT = max_PWM_OUTPUT;
    }
    if (_PWM_OUTPUT < 0) {
        _PWM_OUTPUT = 0;
    }
    prev_VOL_IN = VOL_IN;
    prev_CUR_IN = CUR_IN;
    prev_VOL_OUT = VOL_OUT;
    prev_CUR_OUT = CUR_OUT;
    prev_PWR_IN = PWR_IN;
    // prev_PWR_OUT = PWR_OUT;
    prev_PWM_OUTPUT[1] = prev_PWM_OUTPUT[0];
    prev_PWM_OUTPUT[0] = _PWM_OUTPUT;
    
    *PWM_OUTPUT = _PWM_OUTPUT;
}
