#include "keyboard.h"
// #include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

//przypisanie zmiennym uniwersalnym odpowiedniego portu
void led_init(char led_port)

{   
	if(led_port != 'a' || led_port != 'A' ||
	led_port != 'b' || led_port != 'B' ||
	led_port != 'c' || led_port != 'C' ||
	led_port != 'd' || led_port != 'D'){
		led_port = 'a';
	}
	set_IO_registers(led_port);
	DDRLED = DDR;
	PORTLED = PORT;
	*DDRLED = 0xFF; //ustawienie ledów na wyjœcie
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
		DDR = &DDRB;
		PORT = &PORTB;
		PIN = &PINB;

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
	char out = 0x00;
	//sprawdzenie wierszy
	*DDR = 0x0f;
	*PORT = 0xF0;
	char cols = *PIN;
	//je¿eli wiersz jest wciœniêty

	// sprawdzenie kolumn
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
						col = j-4;
						break;
					}
				}
				break;
			}
		}
	
	if(kb_size == 'm'){
		if (row != 0){
			return 0x00;
		}
	}

	if(row != -1 && col !=-1)
	{

		//out |= _BV(row);
		//out |= _BV(col);
		
		
		out = 4*col+row;
		
	}
	// }
	return out;
}