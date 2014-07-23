#ifndef magnetometer_h
#define magnetometer_h

#include <project.h>
#include <math.h>
	
void writeregister(uint8 theregister, uint8 write);
uint8 readregister(uint8 theregister);
int16 getmeasurement(uint8 registerA, uint8 registerB);
int16 getheading(int16 x, int16 y);

#endif
