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
#include <magnetometer.h>
#include <thermocouple.h>
#include <stdio.h>


CY_ISR_PROTO(IntWind);
CY_ISR_PROTO(SBD_int);
void windprocessPacket();
void clearPacketSBD();
void clearPacketwind();

uint8 SBDData[256];
uint16 SBDPointer = 0;
uint8 windData[256];
uint16 windDataPointer = 0;
uint8 windpacketReceived;
uint8 SBDpacketReceived;
int16 readingx, readingy, readingz, heading;

int main()
{
	clearPacketSBD();
	clearPacketwind();
	UART_Wind_Start();
	UART_SBD_Start();
	psoc_Start();
	isr_Wind_StartEx(IntWind);
	SBD_reply_StartEx(SBD_int);
	clock_Start();
	master_Start();
	
	CyGlobalIntEnable;
	//Writes to magnetometer to be read from (not calibration mode)
	writeregister((uint8) 0x00, (uint8) 0x70);
	writeregister((uint8) 0x01, (uint8) 0xA0);
	writeregister((uint8) 0x02, (uint8) 0x00);
	CyDelay(2000u);
	
	clearPacketwind();
	UART_Wind_PutString("0R\r\n");

    for(;;)
    {
        if(windpacketReceived){
			windprocessPacket();
		}
		
		if(SBDpacketReceived)
		{
			clearPacketSBD();
		}
		
    }
}

void windprocessPacket(){
	int i = 0;
	int j = 0;
	int gpsvalid = 1;
	int16 watertemperature;
	int count = 0;
	//char windDirection[3];
	//char windSpeed[3];
	char weatherdata[256];
	char gpsdata[64];
	char8 text[256];
	
	readingx = getmeasurement((uint8) 3,(uint8) 4);
	readingy = getmeasurement((uint8) 7,(uint8) 8);
	readingz = getmeasurement((uint8) 5,(uint8) 6);	
	heading = getheading(readingx, readingy);
	
	watertemperature = gettemperature();
	
	UART_SBD_PutString("AT-WSGPLF\r\n");
	UART_SBD_PutString("AT-WSGPLF\r\n");
	CyDelay(500u);
	
	while(SBDData[13 + i] != '\r')
	{
		gpsdata[i] = SBDData[13 + i];
		i++;
	}
	
	for(i=0;i<40;i++)
	{
		if(gpsdata[i] == 'v')
		{
			gpsvalid = 0;
			break;
		}
		
		if(gpsdata[i] == 'a')
		{
			gpsvalid = 1;
			break;
		}
	}
	
	i = 0;
	j =0;
	while(!(windData[j] == '0' && windData[j+1] == 'R' && windData[j+2] == '3'))
	{
		weatherdata[i] = windData[j];
		if(windData[j+1] == '\r' && windData[j+2] == '\n')
		{
			windData[j+2] = ',';
			j = j + 2;
			i++;
			count++;
		}
		
		else
		{
			i++;
			j++;
		}
	}
	
	/*for(i=0;i<3; i++)
	{
		windDirection[i] = windData[15+i];
	}
	
	for(i=0;i<3;i++)
	{
		windSpeed[i] = windData[39+i];
	}*/
	
	sprintf(text, "AT-WSMOST=%s,%s, %d, %d\r\n", gpsdata, weatherdata, (int)heading, watertemperature);
	UART_SBD_PutString(text);
	UART_SBD_PutString(text);
	clearPacketSBD();
	clearPacketwind();
	UART_SBD_PutString("AT-WSEPOFF\r\n");
	clearPacketSBD();
}

void clearPacketSBD(){	
	SBDPointer = 0;
	SBDpacketReceived = 0;
    
}

void clearPacketwind()
{
	windDataPointer = 0;
	windpacketReceived = 0;
}

CY_ISR(IntWind)
{
 	    uint8 byte = UART_Wind_GetChar();
		if(byte !=0){
			windData[windDataPointer] = byte;
			windDataPointer++;	
			if(byte == '\n'){
				windpacketReceived = 1;
			}
			
		}
}

CY_ISR(SBD_int)
{
	uint8 byte = UART_SBD_GetChar();
	if(byte !=0){
		if(byte == '\n')
		{
				SBDData[SBDPointer] = '_';
				SBDpacketReceived = 1;
		}
		
		else
		
		{
			SBDData[SBDPointer] = byte;
		}
		
		SBDPointer++;	
			}
			
		}

/* [] END OF FILE */
