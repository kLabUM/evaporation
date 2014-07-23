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
#include <math.h>

int main()
{
	clock_Start();
    master_Start();
	LCD_Start();
	
	int16 temperature = 0;
	uint8 size = 0;
	int temp[14];
	int i;

    CyGlobalIntEnable; 
    for(;;)
    {
		uint16 compare= 8192;
		float accuratetemp = 0;
		LCD_Position(0,0);
		LCD_PrintString("Temp: ");
		master_WriteTxData(5);
		while(!master_GetRxBufferSize())
		{
		}
        temperature = master_ReadRxData();	
		
		for(i = 0; i < 14; i++)
		{
			if ((uint16)(compare & temperature) == compare)
			{
				temp[i] = 1;
			}
			else
			{
				temp[i] = 0;
			}	
			compare = compare / 2;
		}
		
		for(i = 1; i < 14; i++)
		{
			accuratetemp = accuratetemp + temp[i] * pow(2,(11-i));
		}
		if(temp[0] == 1)
		{
			accuratetemp = accuratetemp * -1;
		}
		
		//temperature = temperature >> 2;
		temperature = (uint16)(accuratetemp * 100);
		LCD_Position(0,5);
		LCD_PrintNumber(temperature);
		
		
    }
}

/* [] END OF FILE */
