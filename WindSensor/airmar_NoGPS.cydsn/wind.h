#ifndef wind_h
#define wind_h
	
#include<math.h>
#include<string.h>
struct windvector
	{
		float Ncomponent;
		float Ecomponent;
	};
	
struct speedheading
	{
		float speed;
		float heading;
	};
	
	struct windvector definevectors(struct speedheading);
	struct windvector avgwind(struct windvector[], int length);
	struct speedheading converttospeedandheading(struct windvector);
	float subtractheadings(float heading, float subtractheading);
	float addheadings(float heading, float subtractheading);

#endif