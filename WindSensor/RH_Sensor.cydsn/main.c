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

struct RHdata
{
	uint8 MSB;
	uint8 LSB;
};

void writeregister(uint8 theregister, uint8 write)
{
	uint8 writestatus = psoc_MasterSendStart(64, psoc_WRITE_XFER_MODE);
	if(psoc_MSTR_NO_ERROR == writestatus)
	{
		writestatus = psoc_MasterWriteByte(theregister);
		writestatus = psoc_MasterWriteByte(write);
	}
	psoc_MasterSendStop();
	
}
struct RHdata readregister(uint8 theregister)
{
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
	
	while(psoc_MSTR_NO_ERROR != status)
	{
    status = psoc_MasterSendStart(64, psoc_READ_XFER_MODE);
	}
	if(psoc_MSTR_NO_ERROR == status) //ensures these is no error before reading
	{
		returnvalue.MSB = psoc_MasterReadByte(psoc_ACK_DATA);
		returnvalue.LSB = psoc_MasterReadByte(psoc_NAK_DATA);
	}
	psoc_MasterSendStop();
	
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
int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
	psoc_Start();
	LCD_Start();
	struct RHdata rh;
	uint8 readbyte = 229;
	uint16 RH;
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
		
		rh = readregister(readbyte);
		RH = processRH(rh.MSB, rh.LSB);
		LCD_ClearDisplay();
		LCD_Position(0,0);
		LCD_PrintString("RH: ");
		LCD_Position(0,3);
		LCD_PrintU32Number(RH);
		
    }
}

/* [] END OF FILE */
