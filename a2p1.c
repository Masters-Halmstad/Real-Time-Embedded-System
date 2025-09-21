/*
	Modified by Wagner Morais on Sep 2023.
 */

#include <stdio.h>
#include "piface.h"

#define LCD_LONG_DELAY \
	do { for(volatile int DELAYx = 0; DELAYx < 5000000; DELAYx++); } while(0);


int main()
{
	piface_init();
	piface_clear();
	while(1){
		piface_clear();
		piface_puts("Short string");
		LCD_LONG_DELAY;

		piface_clear();
		piface_puts("This is a long string");
		LCD_LONG_DELAY;

		piface_clear();
		piface_puts("1st line\n2nd line");
		LCD_LONG_DELAY;
	}
	return 0;
}