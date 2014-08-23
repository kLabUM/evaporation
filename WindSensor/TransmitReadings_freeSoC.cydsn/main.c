#include <project.h>
#include <magnetometer.h>
#include <thermocouple.h>
#include <stdio.h>
#include <stdlib.h>
#include <batteryvoltage.h>
#include <RH.h>

struct evappacket
{
	float32 gpstime; 
	float32 gpsnorth;
	float32 gpswest; 
	uint32 gpsdate;
	uint16 VaisalawindDirection; 
	uint8 VaisalawindSpeed;
	int16 Vaisalaairtemp;
	int16 externaltemp;
	uint16 Vaisalarelhumidity;
	uint16 RHsensor;
	uint16 Vaisalaairpressure;
	uint16 Magnetometerheading;
	int16 Thermocouplewatertemperature;
	uint8 battery;
	uint16 dummychecksum;
};

CY_ISR_PROTO(IntWind);
CY_ISR_PROTO(SBD_int);
CY_ISR_PROTO(windtimer);
void windprocessPacket();
void clearPacketSBD();
void clearPacketwind();
uint8 windbroke;
uint8 gpsbroke;
uint8 SBDData[256];
uint16 SBDPointer = 0;
uint8 windData[256];
uint16 windDataPointer = 0;
uint8 windpacketReceived;
uint8 SBDpacketReceived;
uint8 windtimeout = 0;
uint8 gpstimeout = 0;
uint16 windtime;
int16 readingx, readingy, readingz, heading;
uint8 voltage;

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
	ADC_Start();
	
	CyGlobalIntEnable;
	//Writes to magnetometer to be read from (not calibration mode)
	writeregister((uint8) 0x00, (uint8) 0x70);
	writeregister((uint8) 0x01, (uint8) 0xA0);
	writeregister((uint8) 0x02, (uint8) 0x00);
	CyDelay(15000u);
	
	clearPacketwind();
	//Query Sensor for wind, pressure, temperature and humidity data
	UART_Wind_PutString("0R\r\n");
	
	timeout_isr_StartEx(windtimer);
	timer_clock_Start();
	Timer_Start();
	windtime = 0;

    for(;;)
    {
		//When the packet is received takes other sensor data, sends packet and turns off power
        if(windpacketReceived){
			Timer_Stop();
			timer_clock_Stop();
			timeout_isr_Stop();
			windprocessPacket();
		}
		//Here to clear any unexpected outputs from SBD Warrior
		if(SBDpacketReceived)
		{
			clearPacketSBD();
		}
		//changes
		if(windtimeout == 1)
		{
			windbroke = 1;
			windprocessPacket();
		}
		//end changes
    }
}

void windprocessPacket(){
	struct evappacket sendpacket;
	SensirionData tempandrh;
	float32 float32size;
	int16 int16size;
	uint8 uint8size;
	uint16 uint16size;
	uint32 uint32size;
	int i = 0;
	//int j = 0;
	int gpsvalid = 0;
	int16 watertemperature;
	int16 externalairtemp;
	//int count = 0;
	//char weatherdata[256];
	char gpsdata[64];
	char8 text[256];
	float time;
	char validornot;
	float northgps;
	float westgps;
	uint32 date;
	int matches;
	uint16 externalrh;
	uint8 Vtempbroke = 0;
	uint8 Vpressurebroke = 0;
	uint8 Vhumiditybroke = 0;
	
	tempandrh.temp = 0;
	tempandrh.rh = 0;
	tempandrh.valid = 1;
	
	// get magnetometer reading
	readingx = getmeasurement((uint8) 3,(uint8) 4);
	readingy = getmeasurement((uint8) 7,(uint8) 8);
	readingz = getmeasurement((uint8) 5,(uint8) 6);	
	heading = getheading(readingz, readingx); // z then x when mounted with board parallel to drifter pole
	
	// get reading from thermocouple output as an integer with last two spots as hundreths and thousandths
	watertemperature = gettemperature();
	voltage = getvoltage();
	tempandrh = TakeTempRHReading();
	
	
	clearPacketSBD();
	//query for last gps fix and wait for response from SBD Warrior 
	UART_SBD_PutString("0000000000000000000000000\r\n");
	UART_SBD_PutString("AT-WSGPLF\r\n");
	UART_SBD_PutString("AT-WSGPLF\r\n");
	timeout_isr_StartEx(windtimer);
	timer_clock_Start();
	Timer_Start();
	windtime = 0;
	gpstimeout = 0;
	while(SBDpacketReceived == 0)
	{
		if(gpstimeout == 1 && gpsbroke != 1)
		{
			gpsbroke = 1;
		}
	}
	clearPacketSBD();
	while(SBDpacketReceived == 0 && gpsbroke != 1)
	{
		if(gpstimeout == 1)
		{
			gpsbroke = 1;
		}
	}
	
	SBD_reply_Stop();
	
	Timer_Stop();
	timer_clock_Stop();
	timeout_isr_Stop();
	
	//extracts needed data from GPRMC Sentance
	matches = sscanf(SBDData, "$GPRMC,%f,%c,%f,%*c,%f,%*c,%*f,%*f,%d", &time, &validornot, &northgps, &westgps, &date);
			if(validornot == 'A' && matches == 5)
			{
				gpsvalid = 1;
			}
			
			else
			{
				gpsvalid = 0;
			}

	SBD_reply_Start();
	
	i = 0;

	// fetchs each parameter needed from the weather sensor and put each parameter in a c string

	char windDirection[4];
	for(i=0;i<3; i++)
	{
		windDirection[i] = windData[15+i];
	}
	windDirection[3] = '\0';
	uint16 winddirection = atoi(windDirection);
	
	char windSpeed[4];
	for(i=0;i<3;i++)
	{
		windSpeed[i] = windData[39+i];
	}
	
	windSpeed[3] = '\0';
	uint8 windspeed = atof(windSpeed) * 10;
	
	char airtemp[5];
	for(i=0;i<4;i++)
	{
		airtemp[i] = windData[60+i];
	}
	if(strchr(airtemp, '#'))
	{
		Vtempbroke = 1;
	}
	airtemp[4] = '\0';
	int16 airtemperature = atof(airtemp) * 10;
	
	char relhumidity[5];
	for(i=0;i<4;i++)
	{
		relhumidity[i] = windData[69+i];
	}
	
	if(strchr(relhumidity, '#'))
	{
		Vhumiditybroke = 1;
	}
	
	relhumidity[4] = '\0';
	uint16 humidity = atof(relhumidity) * 10;
	
	char airpressure[6];
	for(i=0;i<6;i++)
	{
		airpressure[i] = windData[78+i];
	}
	
	if(strchr(airpressure, '#'))
	{
		Vpressurebroke = 1;
	}
	airpressure[5] = '\0';
	uint16 pressure = atof(airpressure) * 10;
	
		sendpacket.gpstime = time;
		sendpacket.gpsnorth = northgps;
		sendpacket.gpswest = westgps;
		sendpacket.gpsdate = date;
		sendpacket.VaisalawindDirection = winddirection;
		sendpacket.VaisalawindSpeed = windspeed;
		sendpacket.Vaisalaairtemp = airtemperature;
		sendpacket.externaltemp = (int16)(tempandrh.temp * 100);
		sendpacket.Vaisalarelhumidity = humidity;
		sendpacket.RHsensor = tempandrh.rh * 100;
		sendpacket.Vaisalaairpressure = pressure;
		sendpacket.Thermocouplewatertemperature = watertemperature;
		sendpacket.Magnetometerheading = (uint16)heading;
		sendpacket.battery = voltage;
		
		if (windbroke == 1)
		{
			sendpacket.VaisalawindDirection = 65535;
			sendpacket.VaisalawindSpeed = 255;
			sendpacket.Vaisalaairtemp = -32768;
			sendpacket.Vaisalarelhumidity = 65535;
			sendpacket.Vaisalaairpressure = 32768;
		}
		
		if(Vpressurebroke == 1)
		{
			sendpacket.Vaisalaairpressure = 32768;
		}
		
		if(Vtempbroke == 1)
		{
			sendpacket.Vaisalaairtemp = -32768;
		}
		
		if(Vhumiditybroke == 1)
		{
			sendpacket.Vaisalarelhumidity = 65535;
		}
		
		if (gpsbroke == 1)
		{
			sendpacket.gpstime = -1;
			sendpacket.gpsnorth = 0;
			sendpacket.gpswest = 0;
			sendpacket.gpsdate = 4294967295;
		}
		
		if(tempandrh.valid == 0)
		{
			sendpacket.externaltemp = -32768;
			sendpacket.RHsensor = 65535;
		}
		
	
	//sprintf(text, "AT-WSMOST=%s,%s,%s,%s,%s,%s,%d,%d\r\n", gpsdata, windDirection, windSpeed, airtemp, relhumidity, airpressure, (int)heading, (uint16)watertemperature);
	//start changes
	if(gpsvalid == 1)
	{
		UART_SBD_PutString("0000000000000000000000000\r\n");
		
		UART_SBD_PutString("0000000000000000000000000\r\n");
		UART_SBD_PutString("AT-WSMOBW=34\r\n");
		UART_SBD_PutArray(&sendpacket.gpstime, sizeof(float32size));
		UART_SBD_PutArray(&sendpacket.gpsnorth, sizeof(float32size));
		UART_SBD_PutArray(&sendpacket.gpswest, sizeof(float32size));
		UART_SBD_PutArray(&sendpacket.gpsdate, sizeof(uint32size));
		UART_SBD_PutArray(&sendpacket.VaisalawindDirection, sizeof(uint16size));
		UART_SBD_PutArray(&sendpacket.VaisalawindSpeed, sizeof(uint8size));
		UART_SBD_PutArray(&sendpacket.Vaisalaairtemp, sizeof(int16size));
		UART_SBD_PutArray(&sendpacket.externaltemp, sizeof(int16size));
		UART_SBD_PutArray(&sendpacket.Vaisalarelhumidity, sizeof(uint16size));
		UART_SBD_PutArray(&sendpacket.RHsensor, sizeof(uint16size));
		UART_SBD_PutArray(&sendpacket.Vaisalaairpressure, sizeof(uint16size));
		UART_SBD_PutArray(&sendpacket.Magnetometerheading, sizeof(uint16size));
		UART_SBD_PutArray(&sendpacket.Thermocouplewatertemperature, sizeof(int16size));
		UART_SBD_PutArray(&sendpacket.battery, sizeof(uint8size));
		UART_SBD_PutArray(&sendpacket.dummychecksum, sizeof(uint16size));
	}
	
	else
	{
		UART_SBD_PutString("0000000000000000000000000\r\n");
		
		UART_SBD_PutString("0000000000000000000000000\r\n");
		UART_SBD_PutString("AT-WSMOBW=1\r\n");
		UART_SBD_PutString("I");
	}
	
	
	//end changes
	
	UART_SBD_PutString("0000000000000000000000000\r\n");
	//UART_SBD_PutString("AT-WSSBDIS\r\n");
	//UART_SBD_PutString(text);
	clearPacketSBD();
	clearPacketwind();
	UART_SBD_PutString("0000000000000000000000000\r\n");
	UART_SBD_PutString("AT-WSEPOFF\r\n");
	UART_SBD_PutString("AT-WSEPOFF\r\n");
	clearPacketSBD();
	
	CyDelay(30000);
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

CY_ISR(windtimer)
{
		/* Read Status register in order to clear the sticky Terminal Count (TC) bit 
	 * in the status register. Note that the function is not called, but rather 
	 * the status is read directly.
	 */
   	Timer_STATUS;
    
	/* Increment the Counter to indicate the keep track of the number of 
     * interrupts received */
    windtime++;
	
	if(windtime >= 300)
	{
		windtimeout = 1;
		gpstimeout = 1;
	}
}

/* [] END OF FILE */
