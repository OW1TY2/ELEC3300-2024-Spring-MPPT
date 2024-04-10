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
int SOLAR_TRACKER_track(int LDR_val[2], int MOTOR_OUTPUT[2]) {
    if (LDR_val[0] - LDR_val[1] > diff_threshold) {
        MOTOR_OUTPUT[0] = MOTOR_MAX;
        MOTOR_OUTPUT[1] = 0;
    } else if (LDR_val[1] - LDR_val[0] > diff_threshold) {
        MOTOR_OUTPUT[0] = 0;
        MOTOR_OUTPUT[1] = MOTOR_MAX;
    } else {
        MOTOR_OUTPUT[0] = 0;
        MOTOR_OUTPUT[1] = 0;
    }
}