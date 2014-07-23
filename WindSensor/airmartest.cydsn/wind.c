#include <wind.h>

struct windvector definevectors(struct speedheading inputs)
{
	struct windvector output;
	
	if(inputs.heading >= 270)
	{
		output.Ecomponent = -1 * inputs.speed * cos(inputs.heading - 270);
		output.Ncomponent = inputs.speed * sin(inputs.heading - 270);
	}
	
	else if(inputs.heading >= 180)
	{
		output.Ecomponent = -1 * inputs.speed * sin(inputs.heading - 180);
		output.Ncomponent = -1 * inputs.speed * cos(inputs.heading - 180);
	}
	
	else if(inputs.heading >= 90)
	{
		output.Ecomponent = inputs.speed * 	cos(inputs.heading - 90);
		output.Ncomponent = -1 * inputs.speed * sin(inputs.heading - 90);
	}
	
	else
	{
		output.Ecomponent = inputs.speed * sin(inputs.heading);
		output.Ncomponent = inputs.speed * cos(inputs.heading);
	}
	
	return output;
}

struct windvector avgwind(struct windvector input[], int length)
{
	struct windvector output;
	int i = 0;
	float Nsum = 0, Esum = 0;
	
	for(i =0;i<length;i++)
	{
		Nsum = input[i].Ncomponent + Nsum;
		Esum = input[i].Ecomponent + Esum;
	}
	
	output.Ncomponent = Nsum / length;
	output.Ecomponent = Esum / length;
	
	return output;
	
}

struct speedheading converttospeedandheading(struct windvector input)
{
	struct speedheading output;
	
	output.speed = sqrt((input.Ecomponent * input.Ecomponent) + (input.Ncomponent * input.Ncomponent));
	
	if(input.Ecomponent < 0 && input.Ncomponent > 0)
	{
		output.heading = atan(input.Ncomponent / (-1 * input.Ecomponent)) + 270;
	}
	
	else if(input.Ecomponent < 0 && input.Ncomponent < 0)
	{
		output.heading = atan((-1 * input.Ecomponent) / (-1 * input.Ncomponent)) + 180;
	}
	
	else if(input.Ecomponent > 0 && input.Ncomponent < 0)
	{
		output.heading = atan((-1 * input.Ncomponent) / (input.Ecomponent)) + 90;
	}
	
	else if(input.Ecomponent > 0 && input.Ncomponent > 0)
	{
		output.heading = atan(input.Ecomponent / input.Ncomponent);
	}
	
	else if(input.Ecomponent == 0 && input.Ncomponent > 0)
	{
		output.heading = 0;
	}
	
	else if(input.Ecomponent == 0 && input.Ncomponent < 0)
	{
		output.heading = 180;
	}
	
	else if(input.Ecomponent > 0 && input.Ncomponent == 0)
	{
		output.heading = 90;
	}
	
	else if(input.Ecomponent < 0 && input.Ncomponent == 0)
	{
		output.heading = 270;
	}
	
	else 
	{
		output.heading = 0;
	}
	
	return output;
}