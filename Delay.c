

#include  "Delay.h"

void delay(uint32_t delay)
{
	int int_c2 = 16;
	int min = 0;
	volatile int counter, counter_2;

		for(counter_2 = int_c2; counter_2 > min; counter_2--)
		{
			for(counter = delay; counter > min; counter--);

		}
}
