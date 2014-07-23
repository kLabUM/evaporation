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

void writeregister(uint8 theregister, uint8 write)
{
	uint8 writestatus = psoc_MasterSendStart(0x18, psoc_WRITE_XFER_MODE);
	if(psoc_MSTR_NO_ERROR == writestatus)
	{
		writestatus = psoc_MasterWriteByte(theregister);
		writestatus = psoc_MasterWriteByte(write);
	}
	psoc_MasterSendStop();
	
}

void readtempregister(uint8 theregister, uint8* upper, uint8* lower)
{
	uint8 writestatus = psoc_MasterSendStart(0x18, psoc_WRITE_XFER_MODE);
	if(psoc_MSTR_NO_ERROR == writestatus) //ensures there is no error before writing
	{
		writestatus = psoc_MasterWriteByte(theregister);
	}
	psoc_MasterSendStop();

    uint8 status = psoc_MasterSendStart(0x18, psoc_READ_XFER_MODE);
	if(psoc_MSTR_NO_ERROR == status) //ensures these is no error before reading
	{
		*upper = psoc_MasterReadByte(psoc_ACK_DATA); 
		*lower = psoc_MasterReadByte(psoc_NAK_DATA);
	}
	
	psoc_MasterSendStop();
}

int main()
{
	int32 tcColdJnuVolt, tcHotJnuVolt, tcuVolt, tcTemp, tempavg;
	float coldJnTemp;
	psoc_Start();
    ADC_DelSig_Start();
    AMux_Start();
	LCD_Start();
	

    CyGlobalIntEnable;  /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
		tempavg = 0;
		int32 i, j;
		uint8 a = 0;
		uint8 b = 0;
		uint8* upper;
		uint8* lower;
		lower = &a;
		upper = &b;
		float output;
		
		for(j=0;j<5;j++)
		{
		readtempregister(0x05, upper, lower);
		*upper = *upper & 0x1F;
		if ((*upper & 0x10) == 0x10)
		{ 
			*upper = *upper & 0x0F; 
			coldJnTemp = 256 - (*upper * 16 + *lower / 16);
		}
		else 
		{
			coldJnTemp = ((*upper * 16) + (*lower / 16));
		}
		
		tcColdJnuVolt = Thermocouple_1_GetVoltage ((int32)(coldJnTemp*100)); 
		
	    AMux_Select(0);
	    ADC_DelSig_SelectConfiguration(ADC_DelSig_CFG2,1);
	    ADC_DelSig_StartConvert();
	    CyDelay(100u);
	    for(i = 0; i < 100; i++)
	    {
	        if(ADC_DelSig_IsEndConversion(ADC_DelSig_WAIT_FOR_RESULT))
	        {
	            output = ADC_DelSig_CountsTo_uVolts(ADC_DelSig_GetResult32());
	            tcHotJnuVolt = (float)output;
	            break;
	        }
	        CyDelay(5u);
	    }
	    ADC_DelSig_StopConvert();
		
		tcuVolt = tcColdJnuVolt + tcHotJnuVolt; 
		tcTemp = Thermocouple_1_GetTemperature(tcuVolt);
		tempavg = tcTemp + tempavg;
		}
		LCD_WriteControl(LCD_CLEAR_DISPLAY);
		LCD_Position(0,0);
		LCD_PrintString("Temp: ");
		LCD_Position(0,5);
		LCD_PrintNumber(tempavg/5);
		
		
		

	}
	
	
}

/* [] END OF FILE */
