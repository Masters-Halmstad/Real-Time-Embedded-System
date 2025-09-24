/*
	Part of the Real-Time Embedded Systems course at Halmstad University
	Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
	All rights reserved.
*/
/*
 * Modified by Wagner Morais on Aug 2023.
 */
#include <stdio.h>
#include "expstruct.h"
#include "led.h"
#include <stdlib.h>
#include "piface.h"

// #define LINE 32
#define waitTime 500000

int main()
{

	// char str[LINE];
	led_init();
	piface_init();
	piface_clear();
	piface_puts("DT8025 - A2P3\n");
	RPI_WaitMicroSeconds(waitTime);

	char str[50];
	ExpStruct *value;

	int i = 1;
	// cyclic execution
	while (1)
	{
		value = iexp(i++);
		piface_clear();
		sprintf(str, "%d: %d.%d\n", i, value->expInt, value->expFraction);
		piface_puts(str);
		if (i >= 20)
			i = 1;
		free(value);
		// for test
	}
	return 0;
}
