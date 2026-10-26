#ifndef LCD_H
#define LCD_H

unsigned int PINS[6];

#define LCD_RS	PINS[0]
#define LCD_EN	PINS[1]

#define LCD_DB4	PINS[4]
#define LCD_DB5	PINS[5]
#define LCD_DB6	PINS[6]
#define LCD_DB7	PINS[7]

int CURSOR_X;

volatile unsigned char *LCD_DDR;
volatile unsigned char *LCD_PORT;
/*
Ustawienie portu lcd 4 bit mode:
LCD_init('a', {2,3,4,5,6,7});
przykładowe użycie dla portu a gdzie rs = PA2, EN=3, DB4 = 4...DB7 = 7

port - port letter as char
pins[] = {RS,EN,DB1,DB2,DB3,DB4}

Writing the instructions
	4-bit mode, 2-line,5x8 dot
	Turn On Display, Cursor Off
	Cursor Shift in Increment Mode
*/
void LCD_init(char port, unsigned int pins[6]);

void LCD_write_cmd(char command);

void LCD_write_char(char character);

void LCD_write_string(char *text, int lenght);

/*This function ease of setting the cursor position*/
void LCD_set_cursor(int x,int y);

void LCD_clear_y(int y);
void LCD_clear();


#endif