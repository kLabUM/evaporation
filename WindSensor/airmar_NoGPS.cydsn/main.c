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
#include <RH.h>
#include <batteryvoltage.h>

struct evappacket
{
	float32 gpstime;
	float32 gpsnorth;
	float32 gpswest; 
	uint32 gpsdate;
	uint16 airmarwindDirection; 
	uint8 airmarwindSpeed;
	int16 airmarairtemp;
	int16 externalairtemp;
	uint16 externalrelhumidity;
	uint16 airmarairpressure;
	int16 Thermocouplewatertemperature;
	uint8 battery;
	uint16 dummychecksum;
};

CY_ISR_PROTO(SBD_int);
CY_ISR_PROTO(airmar_int);
CY_ISR_PROTO(windtimer);
void clearPacketSBD();
void clearPacketwind();
uint8 SBDData[256];
uint16 SBDPointer = 0;
char windData[128];
char gpsData[128];
char text[256];
struct windvector vectorforavg[64];
int samplesize = 0;
int windDataPointer = 0;
int windpacketReceived = 0;
uint8 SBDpacketReceived;
int headingandwindReceived = 0;
int gpsvalid = 0;
int i = 0;
int gpsretry = 0;
int8 errorcode = -1;
int count;
char * pch;
char * startofheadingdata;
char * startofwinddata;
char leftorright;
float relativewindheading;
float32 pressure;
float32 airtemp;
float heading;
float windDirection;
float windSpeed;
float32 time;
char validornot = 0;
int validgpsfound = 0;
float32 northgps;
float32 westgps;
uint32 date;
struct speedheading resultantavg;
float windsum = 0;
float scalerspeed = 0;
int16 watertemp;
uint16 relh;
int16 battery;
float32 float32size;
uint32 uint32size;
uint16 uint16size;
int16 int16size;
uint8 uint8size;
int matches;
uint16 windtime = 0;
uint8 windtimeout = 0;
uint8 windbroke = 0;
uint8 gpstimeout = 0;
uint8 gpsbroke = 0;
uint8 tempandpressurebroke = 1;
uint8 temppressuretimeout = 0;
SensirionData tempandrh;

int main()
{
	gpsretry = 0;
	struct speedheading current;
	struct evappacket sendpacket;
	
	Comp_Start();
	psoc_Start();
    Airmar_Start();
	master_Start();
	UART_SBD_Start();
	SBD_reply_StartEx(SBD_int);
	isr_airmar_StartEx(airmar_int);
	ADC_Start();
	clock_Start();

    CyGlobalIntEnable;
	isr_airmar_Stop();
	
    for(;;)
    {
		CyDelay(10000);
		gpsretry = 0;
		Airmar_PutString("$PAMTX,0\r\n");
       	Airmar_PutString("$PAMTC,EN,ALL,0\r\n");
		Airmar_PutString("$PAMTC,EN,VWR,1,5\r\n");
		Airmar_PutString("$PAMTC,EN,HDG,1,5\r\n");
		Airmar_PutString("$PAMTX,1\r\n");
		clearPacketwind();
		//isr_airmar_StartEx(airmar_int);
		
		/*	timeout_isr_StartEx(windtimer);
			timer_clock_Start();
			Timer_Start();
			windtime = 0; */
		
		// CyDelay(5000u);
		
		while(samplesize < 25 /*&& windtimeout != 1*/)
		{
			isr_airmar_StartEx(airmar_int);
			CyDelay(100u);
			isr_airmar_Stop();
			
			if(headingandwindReceived)
			{
				isr_airmar_Stop();
				
				startofwinddata = strstr(windData, "$HCHDG");
				int location = startofwinddata - windData;
				int matches1 = sscanf(windData + (startofwinddata - windData), "$HCHDG,%f,", &heading);
				
				startofheadingdata = strstr(windData, "$WIVWR");
				location = startofheadingdata - windData;
				int matches2 = sscanf(windData + (startofheadingdata - windData),"$WIVWR,%f,%c,%*f,%*c,%f,", &relativewindheading, &leftorright, &windSpeed);
				
				current.speed = windSpeed;
				windsum = windsum + current.speed;
				if(leftorright == 'L')
				{
					current.heading = subtractheadings(heading, relativewindheading);
				}
				else if(leftorright == 'R')
				{
					current.heading = addheadings(heading, relativewindheading);
				}
				vectorforavg[samplesize] = definevectors(current);
				if(matches1 == 1 && matches2 == 3)
				{
					//samplesize++;
				}
				clearPacketwind();
				isr_airmar_StartEx(airmar_int);
				windtime = 0;
				
			}
			
			samplesize++;
		}	
		
			Timer_Stop();
			timer_clock_Stop();
			timeout_isr_Stop();
			
		scalerspeed = windsum / samplesize;
		resultantavg = converttospeedandheading(avgwind(vectorforavg, samplesize));
		
		if(windtimeout == 1)
		{
			windbroke = 1;
		}
		
		for(i = 0; i<50;i++)
		{
		isr_airmar_Stop();
		Airmar_PutString("$PAMTX,0\r\n");
		Airmar_PutString("$PAMTC,EN,ALL,0\r\n");
		Airmar_PutString("$PAMTC,EN,MDA,1,5\r\n");
		Airmar_PutString("$PAMTX,1\r\n");
		clearPacketwind();
		isr_airmar_StartEx(airmar_int);
		
		timeout_isr_StartEx(windtimer);
		timer_clock_Start();
		Timer_Start();
		windtime = 0;
		
		while(windpacketReceived == 0)
		{
			if(temppressuretimeout == 1)
			{
				tempandpressurebroke = 1;
				i = 50;
				break;
			}
		}
		
		Timer_Stop();
		timer_clock_Stop();
		timeout_isr_Stop();
		
		isr_airmar_Stop();
		startofwinddata = strstr(windData, "$WIMDA");
		matches = sscanf(windData + (startofwinddata - windData), "$WIMDA,%*f,%*c,%f,%*c,%f,", &pressure, &airtemp);
		clearPacketwind();
		
		if(matches == 2)
		{
			i = 50;
			tempandpressurebroke = 0;
		}
		}
		
		watertemp = gettemperature();
		tempandrh =  TakeTempRHReading();
		battery = getvoltage();
		
		isr_airmar_Stop();
		clearPacketSBD();
		UART_SBD_PutString("0000000000000000000000000\r\n");
		UART_SBD_PutString("AT-WSGPLF\r\n");
		UART_SBD_PutString("AT-WSGPLF\r\n");

		timeout_isr_StartEx(windtimer);
	timer_clock_Start();
	Timer_Start();
	windtime = 0;
	gpstimeout = 0;
	while(SBDpacketReceived == 0 && gpsbroke != 1)
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

		sscanf(SBDData, "$GPRMC,%f,%c,%f,%*c,%f,%*c,%*f,%*f,%d", &time, &validornot, &northgps, &westgps, &date);
			
			if(validornot == 'A')
			{
				gpsvalid = 1;
			}
			
			else
			{
				gpsvalid = 0;
			}
		
		watertemp = gettemperature();
		tempandrh =  TakeTempRHReading();
		battery = getvoltage();
		
		sendpacket.gpstime = time;
		sendpacket.gpsnorth = northgps;
		sendpacket.gpswest = westgps;
		sendpacket.gpsdate = date;
		sendpacket.airmarwindDirection = (uint16)(resultantavg.heading);
		sendpacket.airmarwindSpeed = (uint8)(scalerspeed * 10);
		sendpacket.airmarairtemp = (int16)(airtemp * 10);
		sendpacket.externalairtemp = (int16)(tempandrh.temp * 10);
		sendpacket.externalrelhumidity = (uint16)(tempandrh.rh * 10);
		sendpacket.airmarairpressure = (uint16)(pressure * 1000);
		sendpacket.Thermocouplewatertemperature = watertemp;
		sendpacket.battery = battery;
		
		if(windbroke == 1)
		{
			sendpacket.airmarwindDirection = 65535;
			sendpacket.airmarwindSpeed = 255;
		}
		
		if(tempandpressurebroke == 1)
		{
			sendpacket.airmarairtemp = -32768;
			sendpacket.airmarairpressure = 32768;
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
			sendpacket.externalairtemp = -32768;
			sendpacket.externalrelhumidity = 65535;
		}
		
		UART_SBD_PutString("0000000000000000000000000\r\n");
		
		UART_SBD_PutString("0000000000000000000000000\r\n");
		UART_SBD_PutString("AT-WSMOBW=30\r\n");
		UART_SBD_PutArray(&sendpacket.gpstime, sizeof(float32size));
		UART_SBD_PutArray(&sendpacket.gpsnorth, sizeof(float32size));
		UART_SBD_PutArray(&sendpacket.gpswest, sizeof(float32size));
		UART_SBD_PutArray(&sendpacket.gpsdate, sizeof(uint32size));
		UART_SBD_PutArray(&sendpacket.airmarwindDirection, sizeof(uint16size));
		UART_SBD_PutArray(&sendpacket.airmarwindSpeed, sizeof(uint8size));
		UART_SBD_PutArray(&sendpacket.airmarairtemp, sizeof(int16size));
		UART_SBD_PutArray(&sendpacket.externalairtemp, sizeof(int16size));
		UART_SBD_PutArray(&sendpacket.externalrelhumidity, sizeof(uint16size));
		UART_SBD_PutArray(&sendpacket.airmarairpressure, sizeof(uint16size));
		UART_SBD_PutArray(&sendpacket.Thermocouplewatertemperature, sizeof(int16size));
		UART_SBD_PutArray(&sendpacket.battery, sizeof(uint8size));
		UART_SBD_PutArray(&sendpacket.dummychecksum, sizeof(uint16size));
		
		
		//UART_SBD_PutString("0000000000000000000000000\r\n");
		//UART_SBD_PutString("AT-WSSBDIS\r\n");
		//UART_SBD_PutString("AT-WSSBDIS\r\n");
		
		UART_SBD_PutString("0000000000000000000000000\r\n");
		UART_SBD_PutString("AT-WSEPOFF\r\n");
		UART_SBD_PutString("AT-WSEPOFF\r\n");
		
		CyDelay(5000); 
	}		
		
}

CY_ISR(airmar_int)
{
		
 	    uint8 byte = Airmar_GetChar();
		if(byte !=0){
			windData[windDataPointer] = byte;

			if(byte == '\n')
			{
				if(windpacketReceived == 1)
					headingandwindReceived = 1;
				
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
	headingandwindReceived = 0;
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

void clearPacketSBD(){	
	SBDPointer = 0;
	SBDpacketReceived = 0;
    
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
	
	if(windtime >= 10)
	{
		windtimeout = 1;
		gpstimeout = 1;
		temppressuretimeout = 1;
	}
}

/* [] END OF FILE */
