#include <stdio.h>
#include <stdint.h>

uint32_t prbs()
{   
    static uint32_t shift_register=0xa551199; // "random" seed value
	int b1 = 0;
	int b2 = 0;
	if (shift_register & (1 << 30))
	{
		b1 = 1;
	}
	if (shift_register & (1 << 27))
	{
		b2 = 1;
	}
	
	shift_register=shift_register << 1;
	shift_register=shift_register | (b1 ^ b2);
	shift_register = shift_register & 0x7fffffff;
    return shift_register ; // return 31 LSB's 
}
int main()
{
	uint64_t counter = 0;
	uint32_t randnum;
	uint32_t first;
	
	first = prbs();
	while(counter <= ((uint64_t)1 << 33) )
	{
		randnum = prbs();
		if (randnum == first)
		{
			printf("Duplicate found after %d iterations\n",counter);
			return 0;
		}
		counter++;
		if ((counter % 1000000) == 0)
		{
			printf("%x, %x\n",counter,randnum);
		}
	}
}
