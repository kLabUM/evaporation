/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

int main()
{
    LCD_Start();
	ADC_Start();
	AMux_Start();
	
	int16 value;
	int32 offset;
	
	LCD_Position(0,0);
	LCD_PrintString("Voltage: ");
	AMux_Select(1);
	ADC_StartConvert();
        if(ADC_IsEndConversion(ADC_WAIT_FOR_RESULT))
		{
			offset = ADC_GetResult16();
		}
	ADC_StopConvert();
	
    for(;;)
    {
		CyDelay(100);
		AMux_Select(0);
		ADC_SetOffset(offset);
		ADC_StartConvert();
        if(ADC_IsEndConversion(ADC_WAIT_FOR_RESULT))
		{
			value = ADC_GetResult16();
			LCD_ClearDisplay();
			LCD_Position(0,0);
			LCD_PrintString("Voltage: ");
			LCD_Position(0,8);
			LCD_PrintNumber((float32)100 * (ADC_CountsTo_Volts(value) / (float32)0.31973)); //for 10k and 4.7k resistor
		}
		ADC_StopConvert();
    }
}

/* [] END OF FILE */
