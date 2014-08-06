#include<batteryvoltage.h>

int16 getvoltage()
{
	int16 value;
	int32 offset;
	int16 result;
	
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
	
	result = 100 * (ADC_CountsTo_Volts(value) / 0.31973); // 10k and 4.7k resistor
	
	return result;
}
	
