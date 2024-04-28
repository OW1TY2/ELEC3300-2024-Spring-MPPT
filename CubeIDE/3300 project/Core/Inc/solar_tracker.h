#ifndef SOLAR_TRACKER_H
#define SOLAR_TRACKER_H

// Include any necessary libraries or headers
#include "stm32f1xx_hal.h"
// Define any constants or macros
// Declare any global variables or data structures

// Declare function prototypes

int SOLAR_TRACKER_init(void);
int SOLAR_TRACKER_calibrate(void);
int SOLAR_TRACKER_track(int16_t LDR_VAL_A, int16_t LDR_VAL_B, uint32_t *MOTOR_OUTPUT_A, uint32_t *MOTOR_OUTPUT_B);


#endif // SOLAR_TRACKER_H