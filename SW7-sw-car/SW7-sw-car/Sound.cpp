/*
 * Sound.cpp
 *
 * Created: 10/05/2022 08.56.09
 *  Author: Nicklas
 */ 

#include <avr/io.h>
#include <stdlib.h>
#define XTAL 16000000

void SendComand(int comandArr[8])
{
	for (int i = 0; i < 8; i++)
	{
		while((UCSR1A & 0b00100000) == 0)
		{
		}
		UDR1 = comandArr[i];
	}
}

bool checkComand(int comandArr[8])
{
	for (int i = 0; i < 6; i++)
	{
		while ( (UCSR1A & (1<<7)) == 0 )
		{}
		if(comandArr[i] != UDR1){
			return false;
		}
	}
	return true;
}

void initSound(){
	//baud mega 2560 = 115200
	// baud target 9600
	//1 stop bit
	//8 data bit
	// no paritet
	UCSR1A = 0b00100000;
	UCSR1B = 0b00011000;
	UCSR1C = 0b00000110;
	
	unsigned long baudRate = 9600;
	UBRR1 = (XTAL+(8*baudRate))/(16*baudRate)-1;
	
	//sets max volume
	int comand[8] = {0x7E, 0x06, 0x00, 0x00, 0x1E, 0xFF, 0xDC, 0xEF};
	SendComand(comand);
}


void playTrack(int trackNum){
	if(trackNum >= 1 && trackNum <= 15){
		//7E 03 00 00 (01) FF FC EF  (01) = track 1 op til 16 fx 0A = 10
		int checksum = 0xFFFF - (0x03+0x00+0x00+trackNum)+1; 
		int comand[8] = {0x7E, 0x03, 0x00, 0x00, trackNum, 0xFF, checksum, 0xEF};
		SendComand(comand);
	}
}

bool isPlaying(int trackNum){
	//7E 3D 00 00 02 FF C1 EF	int checksum = 0xFFFF - (0x3D+0x00+0x00+trackNum)+1;
	int comand[8] = {0x7E, 0x3D, 0x00, 0x00, trackNum, 0xFF, checksum, 0xEF};
	if(checkComand(comand)){		return false;	}else{		return true;	}
}

void stopTrack(){
	int comand[8] = {0x7E, 0x16, 0x00, 0x00, 0x00, 0xFF, 0xEA, 0xEF};
	SendComand(comand);
}


void testSound(){
	DDRA = 0;
	DDRB = 0xFF;

	PORTB = 0;
	
	while(1){
		
		if (~PINA & (1 << 0)){
			
			playTrack(0x01);
		}
		if (~PINA & (1 << 1)){
			
			playTrack(0x02);
		}
		
		if (~PINA & (1 << 5))
		{
			stopTrack();
		}
		if (~PINA & (1 << 6))
		{
			//sets volume to 5
			int comand[8] = {0x7E, 0x06, 0x00, 0x00, 0x05, 0xFF, 0xF5, 0xEF};
			SendComand(comand);
		}
		if (~PINA & (1 << 7))
		{
			//sets max volume
			int comand[8] = {0x7E, 0x06, 0x00, 0x00, 0x1E, 0xFF, 0xDC, 0xEF};
			SendComand(comand);
		}
	}
}