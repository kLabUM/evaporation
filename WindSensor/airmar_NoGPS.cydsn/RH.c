#include <RH.h>

#define sensirion_addr	0b1000000
#define sensirion_RH_command	0b11100101
#define sensirion_temp_command	0b11100011


uint8 InterruptCnt2 = 0;
uint8 rhtimeout = 0;

CY_ISR(InterruptHandler2)
{
	/* Read Status register in order to clear the sticky Terminal Count (TC) bit 
	 * in the status register. Note that the function is not called, but rather 
	 * the status is read directly.
	 */
   	Timer_STATUS;
    
	/* Increment the Counter to indicate the keep track of the number of 
     * interrupts received */
    InterruptCnt2++;
	
	if(InterruptCnt2 == 4)
	{
		rhtimeout = 1;
	}
}

uint16 GetSensirionValue(uint8 sensorCommand){
    psoc_MasterClearStatus();
    psoc_MasterWriteBuf(sensirion_addr,&sensorCommand,1,psoc_MODE_COMPLETE_XFER);

    while (((0u == (psoc_MasterStatus() & psoc_MSTAT_WR_CMPLT))))
	{
	}
    uint8 i2cBufferRead[2];
    psoc_MasterClearStatus();
    psoc_MasterReadBuf(sensirion_addr,i2cBufferRead,2,psoc_MODE_COMPLETE_XFER);

    while ((0u == (psoc_MasterStatus() & psoc_MSTAT_RD_CMPLT)))
	{
	}
    uint16 returnValue = (i2cBufferRead[0] <<8) + i2cBufferRead[1];
    return returnValue;
}

SensirionData TakeTempRHReading(){
    
    SensirionData returnValue;
	returnValue.valid = 1;
    uint16 RH = GetSensirionValue(sensirion_RH_command);
	if(RH == 65535)
	{
		returnValue.valid = 0;
	}
    returnValue.rh=-6 + 125*((float)RH/65532);
    uint16 temp = GetSensirionValue(sensirion_temp_command);
	if(temp == 65535)
	{
		returnValue.valid = 0;
	}
    returnValue.temp=-46.85 + 175.72*((float)temp/65532);
    return returnValue;
}

struct RHdata
{
	uint8 MSB;
	uint8 LSB;
};

void writeregister2(uint8 theregister, uint8 write)
{
	uint8 writestatus = psoc_MasterSendStart(64, psoc_WRITE_XFER_MODE);
	if(psoc_MSTR_NO_ERROR == writestatus)
	{
		writestatus = psoc_MasterWriteByte(theregister);
		writestatus = psoc_MasterWriteByte(write);
	}
	psoc_MasterSendStop();
	
}
struct RHdata readregister2(uint8 theregister)
{
	int i;
	struct RHdata returnvalue;
	returnvalue.LSB = 0;
	returnvalue.MSB = 0;
	uint8 writestatus = psoc_MasterSendStart(64, psoc_WRITE_XFER_MODE);
	if(psoc_MSTR_NO_ERROR == writestatus) //ensures there is no error before writing
	{
		writestatus = psoc_MasterWriteByte(theregister);
	}
	psoc_MasterSendStop();
	uint8 status = psoc_MasterSendStart(64, psoc_READ_XFER_MODE);
	
	CyGlobalIntEnable;
	timeout_isr_StartEx(InterruptHandler2);
	timer_clock_Start();
	Timer_Start();
	InterruptCnt2 = 0;
	
	while(psoc_MSTR_NO_ERROR != status && rhtimeout != 1)
	{
    status = psoc_MasterSendStart(64, psoc_READ_XFER_MODE);
	}

	if(psoc_MSTR_NO_ERROR == status) //ensures these is no error before reading
	{
		returnvalue.MSB = psoc_MasterReadByte(psoc_ACK_DATA);
		returnvalue.LSB = psoc_MasterReadByte(psoc_NAK_DATA);
	}
	
	else if (psoc_MSTR_NO_ERROR != status)
	{
		returnvalue.MSB = 0;
		returnvalue.LSB = 0;
	}
	
	return returnvalue;
}

float processRH(uint8 MSB, uint8 LSB)
{
	uint16 resultant = 0;
	float anserw;
	resultant = MSB << 8;
	resultant = resultant + LSB;
	uint16 check = resultant & (uint16)3;
	if(check <= 3)
	{
	resultant = resultant & (uint16)65532;
	}
	anserw = ((float)125 * ((float)resultant / (float)65536)) - (float)6;
	return anserw*100;
}

float processtemp(uint8 MSB, uint8 LSB)
{
	uint16 resultant = 0;
	float anserw;
	resultant = MSB << 8;
	resultant = resultant + LSB;
	
	anserw = (float)-46.85 + ((float)175.72 * (float)resultant / (float)65536);
	return anserw * 100;
}
	

uint16 getRH()
{
	struct RHdata rh;
	uint8 readbyte = 229;
	uint16 RH;
	
	rh = readregister2(readbyte);
	RH = processRH(rh.MSB, rh.LSB);
	
	return RH;
}

int16 getTemp()
{
	struct RHdata temp;
	uint8 readbyte = 227;
	int16 Temp;
	
	temp = readregister2(readbyte);
	Temp = processtemp(temp.MSB, temp.LSB);
	return Temp;
}
	
	