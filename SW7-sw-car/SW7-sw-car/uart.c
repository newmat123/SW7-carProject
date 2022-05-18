/************************************************
* "uart.c":                                     *
* Implementation file for Mega2560 UART driver. *
* Using UART 0.                                 *
* Henning Hargaard, 5/4 2019                    *
*************************************************/
#include <avr/io.h>
#include <stdlib.h>
#include "uart.h"

// Target CPU frequency
#define XTAL 16000000

/*************************************************************************
UART 0 initialization:
    Asynchronous mode.        a
    Baud rate = 9600.
    Data bits = 8.            a
    RX and TX enabled.        a
    No interrupts enabled.    a
    Number of Stop Bits = 1.  a
    No Parity.                a
    Baud rate = 9600.
    Data bits = 8.            a
*************************************************************************/
void InitUART1()
{
	//UCSR0A = 0b00100000;
	UCSR0B = 0b00011000;
	UCSR0C = 0b00000110;
	
	UBRR0  = 103;
	//UBRR0H = 0b;
	//UBRR0L = 0b;
}
void InitUART(unsigned long baudRate, unsigned char dataBit)
{
	//UCSR0A = 0b00100000;
	UCSR0B = 0b00011000;
	UCSR0C = 0b00000110;
	
	UBRR0  = (XTAL+(8*baudRate))/(16*baudRate)-1;
	//UBRR0H = 0b;
	//UBRR0L = 0b;
}


/*************************************************************************
  Returns 0 (FALSE), if the UART has NOT received a new character.
  Returns value <> 0 (TRUE), if the UART HAS received a new character.
*************************************************************************/
unsigned char CharReady()
{
	return UCSR0A & (1<<7);
}

/*************************************************************************
Awaits new character received.
Then this character is returned.
*************************************************************************/
char ReadChar()
{
	while((UCSR0A & 0b10000000) == 0)
	{
	}
	return UDR0;
}

/*************************************************************************
Awaits transmitter register ready.
Then send the character.
Parameter :
	Tegn : Character for sending. 
*************************************************************************/
void SendChar(char Tegn)
{
	while((UCSR0A & 0b00100000) == 0)
	{
	}
	UDR0 = Tegn;
}

/*************************************************************************
Sends 0 terminated string.
Parameter:
   Streng: Pointer to the string. 
*************************************************************************/
void SendString(char* Streng)
{
	while (*Streng != 0)
	{
		SendChar(*Streng);
		
		Streng++;
	}
}

/*************************************************************************
Converts the integer "Tal" to an ASCII string - and then sends this string
using the USART.
Makes use of the C standard library <stdlib.h>.
Parameter:
    Tal: The integer to be converted and sent. 
*************************************************************************/
void SendInteger(int Tal)
{
	char array[7];
	itoa(Tal, array, 10);
	SendString(array);
}

/************************************************************************/