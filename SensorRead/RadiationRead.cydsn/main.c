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



typedef struct{
    float SW_In;
    float SW_Out;
    float LW_In;
    float LW_Out;
    float temp;
    uint8 SW_In_valid;
    uint8 SW_Out_valid;
    uint8 LW_In_valid;
    uint8 LW_Out_valid;
} Radiation;
typedef struct{
    float sensor;
    float ref;
    uint8 sensor_valid;
    uint8 ref_valid;
} Thermo;
typedef struct{
    float Temp;
    float RH;
    uint8 valid;
} Vaisala;
float r;

Radiation take_radiation_reading();
Vaisala take_Temp_RH_reading();
float GetPt100Temperature(float r);
int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    ADC_DelSig_Start();
    AMux_Start();
    UART_Start();
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
   // LCD_Char_Start();
    //status = LCD_SegStat_Start();
    CyDelay(10000u); //10 second delay to allow for sensors to "warm up"
    //uint8 buffer[50];
    //uint8 buffer2[50];
    uint8 value[128];
    for(;;)
    {
        /* Place your application code here. */
        Radiation rad;
        rad = take_radiation_reading();
        Vaisala vais;
        vais = take_Temp_RH_reading();
        //LCD_Char_ClearDisplay();
        //LCD_Char_Position(0u, 0u);
        //sprintf(buffer,"%d %d %d %d", (int)fake.SW_In, (int)fake.SW_Out, (int)fake.LW_In, (int)fake.LW_Out);
        //LCD_Char_PrintString(buffer);
        //LCD_Char_Position(1u, 0u);
        //sprintf(buffer2,"%d %d",(int)fake2.Temp, (int)fake2.RH);
        //LCD_Char_PrintString(buffer2);
        sprintf(value,"%d,%d,%d,%d,%d,%d,%d\r\n",(int)rad.SW_In, (int)rad.SW_Out, (int)rad.LW_In, (int)rad.LW_Out,(int)((rad.temp-273.15)*100),  (int)(vais.Temp*100), (int)(vais.RH*100));
        UART_PutString(value);
        uint8 x = 0;
    }
}
Radiation take_radiation_reading(){
    int32 output;
    uint8 i;
    Radiation reading;
    Thermo RTD;
    AMux_Select(4);
    ADC_DelSig_SelectConfiguration(ADC_DelSig_CFG2,1);
    ADC_DelSig_StartConvert();
    //ADC_DelSig_SelectConfiguration(ADC_DelSig_CFG2,1);
    CyDelay(100u);
    for(i = 0; i < 100; i++)
    {
        if(ADC_DelSig_IsEndConversion(ADC_DelSig_WAIT_FOR_RESULT))
        {
            output = ADC_DelSig_CountsTo_mVolts(ADC_DelSig_GetResult32());
            RTD.sensor = (float)output;
            RTD.sensor_valid = 1;
            break;
        }
        CyDelay(5u);
    }
    ADC_DelSig_StopConvert();
    AMux_Select(5);
    ADC_DelSig_SelectConfiguration(ADC_DelSig_CFG2,1);
    ADC_DelSig_StartConvert();
    //ADC_DelSig_SelectConfiguration(ADC_DelSig_CFG2,1);
    CyDelay(100u);
    for(i = 0; i < 100; i++)
    {
        if(ADC_DelSig_IsEndConversion(ADC_DelSig_WAIT_FOR_RESULT))
        {
            output = ADC_DelSig_CountsTo_mVolts(ADC_DelSig_GetResult32());
            RTD.ref = (float)output;
            RTD.ref_valid = 1;
            break;
        }
        CyDelay(5u);
    }
        
    r = 98*RTD.sensor/RTD.ref;
    reading.temp = GetPt100Temperature(r) + 273.15;//2.5584*r - 255.7 + 273.15; //linear equation from wikipedia table plus 273 to convert to kelvin
    
    ADC_DelSig_Stop();
    AMux_Select(0);
    ADC_DelSig_Start();
    ADC_DelSig_SelectConfiguration(ADC_DelSig_CFG1,1);
    ADC_DelSig_StartConvert();
    CyDelay(100u);
    for(i = 0; i < 100; i++)
    {
        if(ADC_DelSig_IsEndConversion(ADC_DelSig_WAIT_FOR_RESULT))
        {
            output = ADC_DelSig_CountsTo_uVolts(ADC_DelSig_GetResult32());
            reading.SW_In = (float)output/17.53;
            reading.SW_In_valid = 1;
            break;
        }
        CyDelay(5u);
    }
    ADC_DelSig_StopConvert();
    AMux_Select(1);
    ADC_DelSig_StartConvert();
    CyDelay(100u);
    for(i = 0; i < 100; i++)
    {
        if(ADC_DelSig_IsEndConversion(ADC_DelSig_WAIT_FOR_RESULT))
        {
            output = ADC_DelSig_CountsTo_uVolts(ADC_DelSig_GetResult32());
            reading.SW_Out = (float)output/20.69;
            reading.SW_Out_valid = 1;
            break;
        }
        CyDelay(5u);
    }
    ADC_DelSig_StopConvert();
    AMux_Select(2);
    ADC_DelSig_StartConvert();
    CyDelay(100u);
    for(i = 0; i < 100; i++)
    {
        if(ADC_DelSig_IsEndConversion(ADC_DelSig_WAIT_FOR_RESULT))
        {
            output = ADC_DelSig_CountsTo_uVolts(ADC_DelSig_GetResult32());
            reading.LW_In = (float)output/12.95 + .0000000567*reading.temp*reading.temp*reading.temp*reading.temp;
            reading.LW_In_valid = 1;
            break;
        }
        CyDelay(5u);
    }
    ADC_DelSig_StopConvert();
    AMux_Select(3);
    ADC_DelSig_StartConvert();
    CyDelay(100u);
    for(i = 0; i < 100; i++)
    {
        if(ADC_DelSig_IsEndConversion(ADC_DelSig_WAIT_FOR_RESULT))
        {
            output = ADC_DelSig_CountsTo_uVolts(ADC_DelSig_GetResult32());
            reading.LW_Out = (float)output/11.21 + .0000000567*reading.temp*reading.temp*reading.temp*reading.temp;
            reading.LW_Out_valid = 1;
            break;
        }
        CyDelay(5u);
    }
    ADC_DelSig_StopConvert();
    return reading;
}

float GetPt100Temperature(float r)
{
      float const Pt100[] = {80.31, 82.29, 84.27, 86.25, 88.22, 90.19, 92.16, 94.12, 96.09, 98.04,
                            100.0, 101.95, 103.9, 105.85, 107.79, 109.73, 111.67, 113.61, 115.54, 117.47,
                            119.4, 121.32, 123.24, 125.16, 127.07, 128.98, 130.89, 132.8, 134.7, 136.6,
                            138.5, 140.39, 142.29, 157.31, 175.84, 195.84};
 
      int t = -50, i = 0, dt = 0;
 
      if (r > Pt100[0])
         while (250 > t)
         {
               dt = (t < 110) ? 5 : (t > 110) ? 50 : 40;
 
               if (r < Pt100 [++i])
                  return t + ( r - Pt100[i-1])*dt/(Pt100[i]-Pt100[i-1]);
               t += dt;
         };
 
      return t;
 
}

Vaisala take_Temp_RH_reading(){
    uint32 output;
    Vaisala reading2;
    reading2.valid = 0;
    AMux_Select(7);
    ADC_DelSig_SelectConfiguration(ADC_DelSig_CFG2,1);
    ADC_DelSig_StartConvert();
    CyDelay(100u);
    
    uint8 i;
    for(i = 0; i < 100; i++)
    {
        if(ADC_DelSig_IsEndConversion(ADC_DelSig_WAIT_FOR_RESULT))
        {
            output = ADC_DelSig_CountsTo_mVolts(ADC_DelSig_GetResult32());
            reading2.RH = ((float)output)/50;
            reading2.valid = 1;
            break;
        }
        CyDelay(5u);
    }
    ADC_DelSig_StopConvert();
    AMux_Select(6);
    ADC_DelSig_StartConvert();
    CyDelay(100u);
    for(i = 0; i < 100; i++)
    {
        if(ADC_DelSig_IsEndConversion(ADC_DelSig_WAIT_FOR_RESULT))
        {
            output = ADC_DelSig_CountsTo_mVolts(ADC_DelSig_GetResult32());
            reading2.Temp = ((float)output)*120/5000-40;
            reading2.valid = 1 & reading2.valid;
            break;
        }
        CyDelay(5u);
    }
    return reading2;
}
/* [] END OF FILE */
