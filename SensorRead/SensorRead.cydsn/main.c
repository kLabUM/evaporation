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


typedef struct{
    float Temp;
    float RH;
    uint8 valid;
} Vaisala;

Vaisala take_Temp_RH_reading();

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    ADC_DelSig_Start();
    AMux_Start();
    
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
        Vaisala fake;
        fake = take_Temp_RH_reading();
        uint8 x = 0;
    }
}

Vaisala take_Temp_RH_reading(){
    uint16 output;
    Vaisala reading;
    reading.valid = 0;
    ADC_DelSig_StartConvert();
    AMux_Select(0u);
    CyDelay(100u);
    
    uint8 i;
    for(i = 0; i < 100; i++)
    {
        if(ADC_DelSig_IsEndConversion(ADC_DelSig_WAIT_FOR_RESULT))
        {
            output = ADC_DelSig_CountsTo_mVolts(ADC_DelSig_GetResult16());
            reading.RH = ((float)output)/50;
            reading.valid = 1;
            break;
        }
        CyDelay(5u);
    }
    AMux_Select(1);
    CyDelay(100u);
    for(i = 0; i < 100; i++)
    {
        if(ADC_DelSig_IsEndConversion(ADC_DelSig_WAIT_FOR_RESULT))
        {
            output = ADC_DelSig_CountsTo_mVolts(ADC_DelSig_GetResult16());
            reading.Temp = ((float)output)*120/5000-40;
            reading.valid = 1 & reading.valid;
            break;
        }
        CyDelay(5u);
    }
    return reading;
}

/* [] END OF FILE */
