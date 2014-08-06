#include <thermocouple.h>

int16 gettemperature()
{
	int16 temperature = 0;
	int temp[14];
	int i;
	uint16 compare= 8192;
	float accuratetemp = 0;
	master_WriteTxData(5);
	while(!master_GetRxBufferSize())
	{
	}
    temperature = master_ReadRxData();
	//CyDelay(100u);
	//master_WriteTxData(5);
    //temperature = master_ReadRxData();
	for(i = 0; i < 14; i++)
	{
		if ((uint16)(compare & temperature) == compare)
		{
			temp[i] = 1;
		}
		else
		{
			temp[i] = 0;
		}	
		compare = compare / 2;
	}
		
	for(i = 1; i < 14; i++)
	{
		accuratetemp = accuratetemp + (float)temp[i] * (float)pow(2,(11-i));
	}
	if(temp[0] == 1)
	{
		accuratetemp = accuratetemp * (float)-1;
	}
		
	temperature = (accuratetemp * (float)100);
	return temperature;
	
}