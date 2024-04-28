#include "solar_tracker.h"

// Include any necessary libraries or headers

// Define any constants or macros
// LDR
int diff_threshold = 500; // threshold for difference between LDR values
// Motor
int MOTOR_MIN = 0; // minimum motor speed
volatile int MOTOR_MAX = 45; // maximum motor speed

// Initialize any global variables or data structures
// int LDR_val[2][2] = {{0, 0}, {0, 0}}; // two pairs

// Define functions
long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int SOLAR_TRACKER_init(void);
int SOLAR_TRACKER_calibrate(void);
int SOLAR_TRACKER_track(int16_t LDR_VAL_A, int16_t LDR_VAL_B, uint32_t *MOTOR_OUTPUT_A, uint32_t *MOTOR_OUTPUT_B) {
    if (LDR_VAL_A - LDR_VAL_B > diff_threshold) {
        *MOTOR_OUTPUT_A = MOTOR_MAX;
        *MOTOR_OUTPUT_B = 0;
    } else if (LDR_VAL_B - LDR_VAL_A > diff_threshold) {
        *MOTOR_OUTPUT_A = 0;
        *MOTOR_OUTPUT_B = MOTOR_MAX;
    } else {
        *MOTOR_OUTPUT_A = 0;
        *MOTOR_OUTPUT_B = 0;
    }
}