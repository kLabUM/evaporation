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
#include <stdio.h>

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    int32 output;
    int32 raw_reading;
    uint8 i;
    uint8 buffer[50];
    LCD_Char_Start();
    ADC_DelSig_Start();
    
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    CyDelay(100u);
    for(;;)
    {
        ADC_DelSig_StartConvert();
    //ADC_DelSig_SelectConfiguration(ADC_DelSig_CFG2,1);
        CyDelay(100u);
        for(i = 0; i < 100; i++)
        {
            if(ADC_DelSig_IsEndConversion(ADC_DelSig_WAIT_FOR_RESULT))
            {
                raw_reading=ADC_DelSig_GetResult32();
                output = ADC_DelSig_CountsTo_uVolts(raw_reading);
                break;
            }
            CyDelay(5u);
        }
        ADC_DelSig_StopConvert();
        
        LCD_Char_ClearDisplay();
        LCD_Char_Position(0u, 0u);
        sprintf(buffer,"%d", output);
        LCD_Char_PrintString(buffer);
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
