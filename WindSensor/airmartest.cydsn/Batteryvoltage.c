#include<batteryvoltage.h>

uint8 getvoltage()
{
	int16 value;
	int32 offset;
	uint8 result;
	
	AMux_Select(1);
	ADC_StartConvert();
    if(ADC_IsEndConversion(ADC_WAIT_FOR_RESULT))
	{
		offset = ADC_GetResult16();
	}
	ADC_StopConvert();
	
	AMux_Select(0);
	ADC_SetOffset(offset);
	ADC_StartConvert();
    if(ADC_IsEndConversion(ADC_WAIT_FOR_RESULT))
	{
		value = ADC_GetResult16();
	}
	ADC_StopConvert();
	
	result = 10 * (ADC_CountsTo_Volts(value) / (float32)0.1525423729) + 0.2; // 10k and 1.8k resistor
	
	return result;
}
	
