// 
#include "../include/lcd.h"
#include <avr/io.h>
#include <stdio.h>

#define F_CPU 16000000UL
#include <util/delay.h>

void LCD_init(char port, unsigned int pins[6]){
    switch (port)
	{
		case 'a':
		case 'A':
		LCD_DDR = &DDRA;
		LCD_PORT = &PORTA;
		break;
		case 'b':
		case 'B':
		LCD_DDR= &DDRB;
		LCD_PORT= &PORTB;

		break;
		case 'c':
		case 'C':
		LCD_DDR = &DDRC;
		LCD_PORT = &PORTC;
		break;

		case 'd':
		case 'D':
		LCD_DDR = &DDRD;
		LCD_PORT = &PORTD;
		break;

		default:
		LCD_DDR = &DDRD;
		LCD_PORT = &PORTD;

		break;
	}
	*LCD_DDR=0xFF;

    for(int i =0;i<6;i++){
        PINS[i]=pins[i];
    }

	/*Writing the instructions
	4-bit mode, 2-line,5x10 dot*/
	LCD_write_cmd(0b00110011);
	LCD_write_cmd(0b00110010);
	LCD_write_cmd(0b00101100);
	LCD_write_cmd(0x01);
	/*Turn On Display, Cursor On, blink on*/
	LCD_write_cmd(0b00001111);
	/*Cursor Shift in Increment Mode*/
	LCD_write_cmd(0b00000110);
	
}

void LCD_write_cmd(char command){
	
	*LCD_PORT=(command&0xF0)|(_BV(LCD_EN));
	*LCD_PORT=(command&0xF0);
	_delay_us(50);

	*LCD_PORT=(command<<4)|(_BV(LCD_EN));
	*LCD_PORT=(command<<4);
	_delay_ms(3);
}

void LCD_write_char(char character){
	
	*LCD_PORT=(character&0xF0)|(_BV(LCD_EN))|(_BV(LCD_RS));
	*LCD_PORT=(character&0xF0)|(_BV(LCD_RS));
	_delay_us(50);

	*LCD_PORT=(character<<4)|(_BV(LCD_EN))|(_BV(LCD_RS));
	*LCD_PORT=(character<<4)|(_BV(LCD_RS));
	_delay_ms(3);
}

void LCD_write_string(char *text, int lenght){
	for(int i=0;i<lenght;i++){
		 LCD_write_char(text[i]);
		 if (i ==16){
			LCD_set_cursor(1,0);
		 }
	}
}

/*This function ease of setting the cursor position*/
void LCD_set_cursor(int x,int y){
	char numberOfLines[2]={0x80,0xC0};
	LCD_write_cmd(numberOfLines[x]+y);
	CURSOR_X = x;
}

void LCD_clear_y(int y){
	LCD_set_cursor(CURSOR_X,y);
	for(int i =y;i<16;i++){
		LCD_write_char(' ');
	}
}

void LCD_clear(){
	LCD_write_cmd(0x01);
}