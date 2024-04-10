#ifndef SOLAR_TRACKER_H
#define SOLAR_TRACKER_H

// Include any necessary libraries or headers

// Define any constants or macros
// Declare any global variables or data structures

// Declare function prototypes

int SOLAR_TRACKER_init(void);
int SOLAR_TRACKER_calibrate(void);
int SOLAR_TRACKER_track(int LDR_val[2], int MOTOR_OUTPUT[2]);


#endif // SOLAR_TRACKER_H