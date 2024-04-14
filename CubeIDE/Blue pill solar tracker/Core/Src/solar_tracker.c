#include "solar_tracker.h"

// Include any necessary libraries or headers

// Define any constants or macros
// LDR
int diff_threshold = 100; // threshold for difference between LDR values
// Motor
int MOTOR_MIN = 0; // minimum motor speed
int MOTOR_MAX = 100; // maximum motor speed

// Initialize any global variables or data structures
// int LDR_val[2][2] = {{0, 0}, {0, 0}}; // two pairs

// Define functions
int SOLAR_TRACKER_init(void);
int SOLAR_TRACKER_calibrate(void);
int SOLAR_TRACKER_track(uint32_t LDR_VAL_A, uint32_t LDR_VAL_B, uint32_t *MOTOR_OUTPUT_A, uint32_t *MOTOR_OUTPUT_B) {
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