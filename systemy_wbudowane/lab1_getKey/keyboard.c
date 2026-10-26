#include "keyboard.h"
// #include <stdio.h>

#include <stdio.h>

//przypisanie zmiennym uniwersalnym odpowiedniego portu
void led_init(char led_port)
{   set_IO_registers(led_port);
	DDRLED = DDR;
	PORTLED = PORT;
	*DDRLED = 0xFF; //ustawienie led�w na wyj�cie
}

void led_set(char output)
{
	*PORTLED = output;
}

//przypisanie zmiennym uniwersalnym odpowiedniego portu
void set_IO_registers(char port)
{
	switch (port)
	{
		case 'a':
		case 'A':
		DDR = &DDRA;
		PORT = &PORTA;
		PIN = &PINA;
		break;
		case 'b':
		case 'B':
		DDR = &DDRB;
		PORT = &PORTB;
		PIN = &PINB;
		PORTB = 0x02;
		break;
		case 'c':
		case 'C':
		DDR = &DDRC;
		PORT = &PORTC;
		PIN = &PINC;
		break;
		case 'd':
		case 'D':
		DDR = &DDRD;
		PORT = &PORTD;
		PIN = &PIND;
		break;
		default:
		break;
	}
}

void kb_init(char kb_port)
{
	set_IO_registers(kb_port);
	*DDR = 0xF0;
	*PORT = 0x0F;
}

unsigned char get_key(char kb_size)
{
	unsigned char out = 0x00;
	*DDR = 0x0f;
	*PORT = 0xF0;
	char cols = *PIN;
	*DDR = 0xf0;
	*PORT = 0x0f;
	char rows = *PIN;
	int row =-1;
	int col=-1;
	int i;
	for( i = 0; i<4; i++){
		if(!(rows & (1 << i))){
			for(int j = 4; j<8; j++){
				if(!(cols & (1 << (j)))){
					row = i;
					col = j;
					break;
				}
			}
			break;
		}
	}


	if(row != -1 && col !=-1)
	{

		out |= _BV(row);
		out |= _BV(col);
	}
	return out;
}