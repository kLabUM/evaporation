#include <magnetometer.h>

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
