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

CY_ISR_PROTO(SBD_int);
void processPacket();
void clearPacket();

uint8 Data[256];
uint16 Pointer = 0;
uint8 packetReceived;


int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
	UART_Start();
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
	SBD_reply_StartEx(SBD_int);
	clearPacket();
	UART_PutString("AT-WSGPF\r\n");
	
    for(;;)
    {
		if(packetReceived)
		{
			processPacket();
		}
		
		UART_PutString("AT-WSGPF\r\n");
	}
}	

	void processPacket(){
	clearPacket();
	}

	void clearPacket(){
	Pointer = 0;
	}

	CY_ISR(SBD_int)
	{
 	    uint8 byte = UART_GetChar();
		if(byte !=0){
			Data[Pointer] = byte;
			Pointer++;	
			if(byte == '\n'){
				packetReceived = 1;
			}
			
		}
	}


/* [] END OF FILE */
