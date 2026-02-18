/*
	Part of the Real-Time Embedded Systems course at Halmstad University
	Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
	All rights reserved.
	Wagner de Morais (Wagner.deMorais@hh.se)
*/

#include <stdio.h>
#include <stdlib.h>
#include "expstruct.h"
#include "piface.h"
#include <string.h>
#include <rpi-systimer.h>

#define LINE 32
#define waitTime 500000

int main()
{

	char str[LINE];
	piface_init();
	piface_clear();
	int expNumber = 1;

	piface_puts("DT8025 - A2P2");
	RPI_WaitMicroSeconds(waitTime);
	ExpStruct *value;
	while (1)
	{
		while (expNumber < 21)
		{
			value = iexp(expNumber);
			piface_clear();
			sprintf(str, "%d: %d.%d", expNumber, value->expInt, value->expFraction);
			piface_puts(str);
			RPI_WaitMicroSeconds(waitTime);
			free(value);
			expNumber++;
		}
		expNumber = 1;
	}

	return 0;
}