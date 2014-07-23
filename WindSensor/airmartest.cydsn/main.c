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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <thermocouple.h>
#include <wind.h>

CY_ISR_PROTO(airmar_int);
void clearPacketwind();
char windData[128];
char gpsData[128];
char text[256];
struct speedheading dataforavg[64];
struct windvector vectorforavg[64];
int samplesize = 0;
int windDataPointer = 0;
int windpacketReceived = 0;
int gpsandwindReceived = 0;
int gpsvalid = 0;
int i = 0;
int gpsretry = 0;
char * pch;
char * startofwinddata;
char pressure[8];
char airtemp[8];
char windDirection[8];
char windSpeed[8];
int16 watertemp;

int main()
{
	memset (pressure, 0, 8);
	memset (airtemp, 0, 8);
	memset (windDirection, 0, 8);
	memset (windSpeed, 0, 8);
	
	Comp_Start();
    Airmar_Start();
	master_Start();
	UART_SBD_Start();
	isr_airmar_StartEx(airmar_int);

    CyGlobalIntEnable;
	isr_airmar_Stop();
	
    for(;;)
    {
		Airmar_PutString("$PAMTX\r\n");
       	Airmar_PutString("$PAMTC,EN,ALL,0\r\n");
		Airmar_PutString("$PAMTC,EN,RMC,1,50\r\n");
		Airmar_PutString("$PAMTC,EN,MWD,1,50\r\n");
		Airmar_PutString("$PAMTX,1\r\n");
		isr_airmar_StartEx(airmar_int);
		
		while(gpsvalid == 0)
		{
			if(gpsandwindReceived)
			{
				isr_airmar_Stop();
				for(i=0;i<40;i++)
				{
					if(windData[i] == 'V')
					{
						gpsretry++;
						gpsvalid = 0;
						isr_airmar_StartEx(airmar_int);
						
						
						if(gpsretry >= 5)
						{
							memcpy(gpsData, windData, 128);
							gpsvalid = 1;
						}
						break;
					}
		
					if(windData[i] == 'A')
					{
						gpsvalid = 1;
						memcpy(gpsData, windData, 128);
						
						break;
					}
				}
				
				startofwinddata = strchr(windData, '\0');
			
				pch = strtok (windData + (startofwinddata - windData + 2),",");
		
				for(i=1;i<8;i++)
				{
					pch = strtok (NULL, ",");
			
					switch(i)
					{
						case 3:
							sprintf(windDirection, "%s", pch);
							break;
						case 7:
							sprintf(windSpeed, "%s", pch);
							break;
						default:
							break;
					}
			
    			}
				
				
				
				clearPacketwind();
				
				
			}
		}
		
		isr_airmar_Stop();
		Airmar_PutString("$PAMTX\r\n");
		Airmar_PutString("$PAMTC,EN,ALL,0\r\n");
		Airmar_PutString("$PAMTC,EN,MDA,1,5\r\n");
		Airmar_PutString("$PAMTX,1\r\n");
		isr_airmar_StartEx(airmar_int);
		
		while(windpacketReceived == 0)
		{
		}
		
		if(windpacketReceived)
		{
			isr_airmar_Stop();
			pch = strtok (windData,",");
  			for(i=1;i<6;i++)
  			{
    			pch = strtok (NULL, ",");
				
				switch(i)
				{
					case 3:
					sprintf(pressure, "%s", pch);
					break;
					
					case 5:
					sprintf(airtemp, "%s", pch);
					break;
					
					default:
					break;
				}
  			}
		
			clearPacketwind();
		}
		
		isr_airmar_Stop();
		Airmar_PutString("$PAMTX\r\n");
		Airmar_PutString("$PAMTC,EN,ALL,0\r\n");
		Airmar_PutString("$PAMTC,EN,MWD,1,5\r\n");
		Airmar_PutString("$PAMTX,1\r\n");
		isr_airmar_StartEx(airmar_int);
		
		while(windpacketReceived == 0)
		{
		}
		
		isr_airmar_Stop();
		pch = strtok (windData,",");
		
		for(i=1;i<8;i++)
		{
			pch = strtok (NULL, ",");
			
			switch(i)
			{
				case 3:
					sprintf(windDirection, "%s", pch);
					break;
				case 7:
					sprintf(windSpeed, "%s", pch);
					break;
				default:
					break;
			}
			
    	}
		clearPacketwind();
		
		watertemp = gettemperature();
		
		sprintf(text, "AT-WSMOST=%s,%s,%s,%s,%s,%d\r\n", gpsData, windDirection, windSpeed, airtemp,pressure, (int)watertemp);
		UART_SBD_PutString(text);
		UART_SBD_PutString("AT-WSEPOFF\r\n");
	}		
		
}

CY_ISR(airmar_int)
{
		
 	    uint8 byte = Airmar_GetChar();
		if(byte !=0){
			windData[windDataPointer] = byte;
			if(byte == '\r')
			{
				windData[windDataPointer] = '\0';	
			}
			if(byte == '\n')
			{
				if(windpacketReceived == 1)
					gpsandwindReceived = 1;
				
				if(windpacketReceived == 0)
					windpacketReceived = 1;
			}
			windDataPointer++;	
			
		}
}

void clearPacketwind()
{
	windDataPointer = 0;
	windpacketReceived = 0;
	gpsandwindReceived = 0;
}

/* [] END OF FILE */
