
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "../include/lcd.h"

#define S_DELAY_MS  1500

int main(void)
{	

	// char out[5];
	// char text[2][7] = {{'.',' ',' ',',',' ',' ','.'},
	// 					{'.',' ',' ',' ',' ',' ','.'}};

	// int timer = 0;



    unsigned int pin_conf[6]={2,3,4,5,6,7};
	LCD_init('d',pin_conf);
	
    while (1) 
    {
		LCD_set_cursor(0,0);

		for(int i =0;i<30;i++){
			if(i==16)	LCD_set_cursor(1,0);
			LCD_write_char('#');
			
		}

		LCD_clear_y(5);
		_delay_ms(S_DELAY_MS);
		LCD_clear();
		_delay_ms(S_DELAY_MS);
    }
}