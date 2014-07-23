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

CY_ISR_PROTO(IntWind);
void processPacket();
void clearPacket();

uint8 windData[256];
uint16 windDataPointer = 0;
uint8 packetReceived;

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
	clearPacket();
    
	CyGlobalIntEnable;  /* Uncomment this line to enable global interrupts. */
    UART_Wind_Start();
	isr_Wind_StartEx(IntWind);
	UART_Wind_PutString("0R\r\n");

	for(;;)
    {
		if(packetReceived){
			processPacket();
		}
	   //CyDelay(100u);
	   //UART_Wind_PutString("0R1\r\n");
        /*put in a timer 
	here that says to break out of loop once we've recorded data for x time?*/
    }
}

void processPacket(){
	/* need to do something here in which it pulls out the information that we want and then does a running average*/
	clearPacket();
}

void clearPacket(){
	windDataPointer = 0;
    /*reinitiate command here?*/
}

CY_ISR(IntWind)
{
 	    uint8 byte = UART_Wind_GetChar();
		if(byte !=0){
			windData[windDataPointer] = byte;
			windDataPointer++;	
			if(byte == '\n'){
				packetReceived = 1;
			}
			
		}
}


/* [] END OF FILE */
