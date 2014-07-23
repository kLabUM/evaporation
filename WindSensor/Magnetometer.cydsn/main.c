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
	uint8 writestatus = psoc_MasterSendStart(30, psoc_WRITE_XFER_MODE);
	if(psoc_MSTR_NO_ERROR == writestatus)
	{
		writestatus = psoc_MasterWriteByte(theregister);
		writestatus = psoc_MasterWriteByte(write);
	}
	psoc_MasterSendStop();
	
}
uint8 readregister(uint8 theregister)
{
	uint8 value;
	uint8 writestatus = psoc_MasterSendStart(30, psoc_WRITE_XFER_MODE);
	if(psoc_MSTR_NO_ERROR == writestatus) //ensures there is no error before writing
	{
		writestatus = psoc_MasterWriteByte(theregister);
	}
	psoc_MasterSendStop();

    uint8 status = psoc_MasterSendStart(30, psoc_READ_XFER_MODE);
	if(psoc_MSTR_NO_ERROR == status) //ensures these is no error before reading
	{
		value = psoc_MasterReadByte(psoc_NAK_DATA); //reads data then sends NAK to signal to slave
	}
	psoc_MasterSendStop();
	
	return value;
}

int16 getmeasurement(uint8 registerA, uint8 registerB)
{
	uint8 MSB;
	uint8 LSB;
	
	MSB = readregister(registerA);
	LSB = readregister(registerB);
	
	int16 reading = ((uint16)MSB << 8) | LSB;
	return reading;
}

int16 getheading(int16 x, int16 y)
{
	int16 heading;
	
	if(y > 0)
	{
		heading = 90 - atan(x / y) * 180/3.14156;
	}
	else if(y < 0)
	{
		heading = 270 - atan(x / y) * 180/3.14156;
	}
	else if(y == 0 && x < 0)
	{
		heading = 180;
	}
	else
	{
		heading = 0;
	}
	
	return heading;
}

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
	psoc_Start();
	int16 readingx, readingy, readingz, heading;
	uint8 readingconfig;
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
	writeregister((uint8) 0x00, (uint8) 0x70);
	writeregister((uint8) 0x01, (uint8) 0xA0);
	writeregister((uint8) 0x02, (uint8) 0x00);
	CyDelay(1000u);
	
    for(;;)
	{
		
		readingx = getmeasurement((uint8) 3,(uint8) 4);
		readingy = getmeasurement((uint8) 7,(uint8) 8);
		readingz = getmeasurement((uint8) 5,(uint8) 6);	
		heading = getheading(readingx, readingy);
		readingconfig = readregister((uint8) 0x00);
		
		
	}
   
}

/* [] END OF FILE */
