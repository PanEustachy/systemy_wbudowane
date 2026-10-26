#include "usart.h"
#include <util/delay.h>
#include <avr/interrupt.h>



void Timer0_Init(void) {
	TCCR0 = (1 << WGM01) | (1 << CS02) | (1 << CS00) ;  // Tryb CTC, preskaler 256
	OCR0 = 255;                           // Ustawienie wartoœci porównania (dla 1 Hz, F_CPU = 4 MHz)
	TIMSK |= (1 << OCIE0);                // W³¹czenie przerwania od porównania
}



ISR(TIMER0_COMP_vect) {
	PORTA ^= (1 << PA0);  // Zmieniamy stan diody LED_0
}



int main(void) {
	
	 // Inicjalizacja portów A
	 DDRA = 0xFF;  // Ustawienie wszystkich pinów PA0-PA7 jako wyjœcia
	 PORTA = 0x00;  // Ustawienie pocz¹tkowego stanu diod na wy³¹czony

	
	USART_Init();  // Inicjalizacja USART

	
	//zad1
	USART_TransmitString("Wiktor Godlewski\n\r");
	
	
	
	
	//zad2
	USART_TransmitString("Nacisnij klawisz [X]\n\r");
	unsigned char znak = USART_ReceiveByte();
	if(znak == 'x'){
			USART_TransmitString("Podano dobry znak\n\r");
	}	else{
			USART_TransmitString("Podano zly znak\n\r");
	}

	//zad3
	sei();
	Timer0_Init();

	while (1) {
			USART_TransmitString("Nacisnij klawisz [X]\n\r");
			unsigned char cmd = USART_ReceiveByte();
			USART_TransmitString("\n\r");
			
			switch (cmd){
				case '0':
					PORTA ^= (1 << PA0);
					break;
					
				case '1':
					PORTA ^= (1 << PA1);
					break;
				case '2':
					PORTA ^= (1 << PA2);
					break;
				case '3':
					PORTA ^= (1 << PA3);
					break;
				case '4':
					PORTA ^= (1 << PA4);
					break;
				case '5':
					PORTA ^= (1 << PA5);
					break;
				case '6':
					PORTA ^= (1 << PA6);
					break;
				case '7':
					PORTA ^= (1 << PA7);
					break;
				case 'c':
					PORTA = 0x00;
					break;
				case 's':
					PORTA = 0xff;
					break;
				default: 
					break;
			}
		
	}

	return 0;
}