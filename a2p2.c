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

#define LINE 32
#define waitTime 2000000

int main()
{

	char str[LINE];
	piface_init();
	piface_clear();

	piface_puts("DT8025 - A2P2");
	RPI_WaitMicroSeconds(waitTime);
	ExpStruct *value;

	value = iexp(10);

	sprintf(str, "%d: %d.%d", 10, value->expInt, value->expFraction);
	// strcpy(str, "10: 22026.47");
	piface_clear();
	RPI_WaitMicroSeconds(waitTime);
	piface_puts(str);
	RPI_WaitMicroSeconds(waitTime);
	free(value);
	return 0;
}