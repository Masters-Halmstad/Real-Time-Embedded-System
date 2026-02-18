/*
	Part of the Real-Time Embedded Systems course at Halmstad University
	Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
	All rights reserved.
	Wagner de Morais (Wagner.deMorais@hh.se)
*/

#include <stdio.h>
#include <stdlib.h>
#include "lib/uart.h"
#include "lib/iregister.h"

#define LINE 80

void stringInput(char *str)
{
	char c;
	int index = 0;
	while (1)
	{
		c = uart_getc();
		if (c == '\n' || c == '\r')
		{
			str[index] = '\0';
			break;
		}
		if (index < LINE - 1)
		{
			str[index] = c;
			index++;
		}
	};
}

void uart_putI(int i)
{
	char buffer[LINE];
	sprintf(buffer, "%d", i);
	uart_puts(buffer);
}

int main()
{
	iRegister r;
	char name[LINE];
	char str[LINE];
	int inumber, inibble, ibit, ishift = 0, v;
	char *stringBit; // to store the bits in string form

	// initializing and clearing the channel
	uart_init();
	uart_clear();

	uart_puts("========= RTES Assignement 1 Part 1 =========================");
	// input name
	uart_puts("\n");
	uart_puts("Enter your name: ");
	stringInput(name);
	uart_puts("\n");

	// print welcome message
	uart_puts("Welcome, ");
	uart_puts(name);
	uart_puts("\n");

	// input integer number
	uart_puts("Enter a integer number (32 bit): ");
	stringInput(str);
	inumber = atoi(str);
	uart_putI(inumber);
	uart_puts("\n");

	// input bit position
	uart_puts("Enter the bit position (0<=ibit<=31): ");
	stringInput(str);
	ibit = atoi(str);
	uart_putI(ibit);
	uart_puts("\n");

	// input nibble position
	uart_puts("Enter the nibble position (0<=inibble<=7): ");
	stringInput(str);
	inibble = atoi(str);
	uart_putI(inibble);
	uart_puts("\n");

	// input number of bits to shift position
	uart_puts("Enter the number of bits to shift (0<=ishift<=31): ");
	stringInput(str);
	ishift = atoi(str);
	uart_putI(ishift);
	uart_puts("\n");

	// Print the entered message
	uart_puts("You Entered: ");
	uart_puts("Number: ");
	r.content = inumber;
	stringBit = reg2str(r);
	uart_puts(stringBit);
	free(stringBit);
	uart_puts("\n");

	uart_puts("Bit: ");
	uart_putI(ibit);
	uart_puts(", ");
	uart_puts("Nibble: ");
	uart_putI(inibble);
	uart_puts("\n");

	// to reset all bits
	r.content = inumber;
	resetAll(&r);
	uart_puts("resetAll(&r) returned ");
	uart_puts(reg2str(r));
	free(stringBit);
	uart_puts("\n");

	// to set all bits
	r.content = inumber;
	setAll(&r);
	uart_puts("setAll(&r) returned ");
	uart_puts(reg2str(r));
	free(stringBit);
	uart_puts("\n");

	// to set bit
	r.content = inumber;
	uart_puts("setBit(ibit, &r) returned ");
	// Check pre-condition
	if (ibit < 0 || ibit > 31)
	{
		uart_puts("-1");
	}
	else
	{
		setBit(ibit, &r);
	}
	uart_puts("  ");
	uart_puts(reg2str(r));
	free(stringBit);
	uart_puts("\n");

	// get bit
	r.content = inumber;
	getBit(ibit, &r);
	uart_puts("getBit(ibit, &r) returned ");
	uart_putI(getBit(ibit, &r));
	uart_puts("  ");
	uart_puts(reg2str(r));
	free(stringBit);
	uart_puts("\n");

	// get nibble
	r.content = inumber;
	v = getNibble(inibble, &r);
	uart_puts("getNibble(inibble, &r) returned ");
	uart_putI(v);
	uart_puts("  ");
	uart_puts(reg2str(r));
	free(stringBit);
	uart_puts("\n");

	// get assignNibble
	r.content = inumber;
	uart_puts("assignNibble(inibble, inumber, &r) returned ");
	uart_putI(assignNibble(inibble, inumber, &r));
	uart_puts("  ");
	uart_puts(reg2str(r));
	free(stringBit);
	uart_puts("\n");

	// get shiftLeft
	r.content = inumber;
	uart_puts("shiftLeft(ibit, &r) returned ");
	// Check pre-condition
	if (ishift < 0 || ishift > 31)
	{
		uart_puts("-1");
	}
	else
	{
		shiftLeft(ishift, &r);
	}
	uart_puts("  ");
	uart_puts(reg2str(r));
	free(stringBit);
	uart_puts("\n");

	// get shiftRight
	r.content = inumber;
	uart_puts("shiftRight(ibit, &r) returned ");
	// Check pre-condition
	if (ishift < 0 || ishift > 31)
	{
		uart_puts("-1");
	}
	else
	{
		shiftRight(ishift, &r);
	}
	uart_puts("  ");
	uart_puts(reg2str(r));
	free(stringBit);
	uart_puts("\n");

	// resetbit
	r.content = inumber;
	uart_puts("resetBit(ibit, &r) returned ");
	// Check pre-condition
	if (ibit < 0 || ibit > 31)
	{
		uart_puts("-1");
	}
	else
	{
		resetBit(ibit, &r);
	}
	uart_puts("  ");
	uart_puts(reg2str(r));
	free(stringBit);
	uart_puts("\n");

	// Using the uart
	// First, iniialize and clear the channel
	// uart_init();
	// uart_clear();

	// To Display a string
	// uart_puts("String\n");

	// To get one character
	// c=uart_getc();

	// However, to get a number, you need to call uart_getc
	// multiple times until receiving a new line.
	// The results of each call to uart_getc can be stored into str
	// atoi(str) will result a number.
}