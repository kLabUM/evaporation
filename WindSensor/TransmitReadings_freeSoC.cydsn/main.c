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
	//Initializations
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
	CyDelay(15000u);
	
	clearPacketwind();
	//Query Sensor for wind, pressure, temperature and humidity data
	UART_Wind_PutString("0R\r\n");

    for(;;)
    {
		//When the packet is received takes other sensor data, sends packet and turns off power
        if(windpacketReceived){
			windprocessPacket();
		}
		//Here to clear any unexpected outputs from SBD Warrior
		if(SBDpacketReceived)
		{
			clearPacketSBD();
		}
		
    }
}

void windprocessPacket(){
	int i = 0;
	//int j = 0;
	int gpsvalid = 0;
	int16 watertemperature;
	//int count = 0;
	//char weatherdata[256];
	char gpsdata[64];
	char8 text[256];
	char time[8];
	char validornot[8];
	char northgps[8];
	char westgps[8];
	char date[8];
	char *pch;
	
	
	// get magnetometer reading
	readingx = getmeasurement((uint8) 3,(uint8) 4);
	readingy = getmeasurement((uint8) 7,(uint8) 8);
	readingz = getmeasurement((uint8) 5,(uint8) 6);	
	heading = getheading(readingz, readingx); // z then x when mounted with board parallel to drifter pole
	
	// get reading from thermocouple output as an integer with last two spots as hundreths and thousandths
	watertemperature = gettemperature();
	
	clearPacketSBD();
	//query for last gps fix and wait for response from SBD Warrior 
	UART_SBD_PutString("AT-WSGPLF\r\n");
	UART_SBD_PutString("AT-WSGPLF\r\n");
	while(SBDpacketReceived == 0)
	{
	}
	clearPacketSBD();
	while(SBDpacketReceived == 0)
	{
	}
	
	SBD_reply_Stop();
	//copies gps data into a c string
	while(SBDData[i] != '\r')
	{
		gpsdata[i] = SBDData[i];
		i++;
	}
	//start changes
	pch = strtok (SBDData,",");
  			for(i=1;i<6;i++)
  			{
    			pch = strtok (NULL, ",");
				
				switch(i)
				{
					case 1:
					sprintf(time, "%s", pch);
					break;
					
					case 2:
					sprintf(validornot, "%s", pch);
					break;
					
					case 3:
					sprintf(northgps, "%s", pch);
					break;
					
					case 5:
					sprintf(westgps, "%s", pch);
					break;
					
					case 9:
					sprintf(date, "%s", pch);
					break;
					
					default:
					break;
				}
  			}
			
			if(validornot[0] == 'A')
			{
				gpsvalid = 1;
			}
			
			else
			{
				gpsvalid = 0;
			}
			//end changes
	SBD_reply_Start();
	
	gpsdata[i] = '\0';
	// checks if gps is valid and sets gpsvalid to appropriate conclusion
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

	
	// fetchs each parameter needed from the weather sensor and put each parameter in a c string
	char windDirection[4];
	for(i=0;i<3; i++)
	{
		windDirection[i] = windData[15+i];
	}
	windDirection[3] = '\0'; 
	
	char windSpeed[4];
	for(i=0;i<3;i++)
	{
		windSpeed[i] = windData[39+i];
	}
	
	windSpeed[3] = '\0';
	
	char airtemp[5];
	for(i=0;i<4;i++)
	{
		airtemp[i] = windData[60+i];
	}
	
	airtemp[4] = '\0';
	
	char relhumidity[5];
	for(i=0;i<4;i++)
	{
		relhumidity[i] = windData[69+i];
	}
	
	relhumidity[4] = '\0';
	
	char airpressure[6];
	for(i=0;i<5;i++)
	{
		airpressure[i] = windData[78+i];
	}
	
	airpressure[5] = '\0';
	
	sprintf(text, "AT-WSMOST=%s,%s,%s,%s,%s,%s,%d,%d\r\n", gpsdata, windDirection, windSpeed, airtemp, relhumidity, airpressure, (int)heading, (uint16)watertemperature);
	//start changes
	if(gpsvalid == 1)
	{
		sprintf(text, "AT-WSMOST=%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d\r\n", time, northgps, westgps, date, windDirection, windSpeed, airtemp, relhumidity, airpressure, (int)heading, (uint16)watertemperature);
	}
	
	else
	{
		sprintf(text, "AT-WSMOST=INVALID");
	}
	
	
	//end changes
	
	
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
				SBDData[SBDPointer] = '\0';
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
