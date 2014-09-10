#ifndef RH_h
#define RH_h
	
#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include <psoc.h>

typedef struct
{
	float temp;
	float rh;
	uint8 valid;
}SensirionData;

SensirionData TakeTempRHReading();
uint16 GetSensirionValue(uint8 sensorCommand);

#endif
