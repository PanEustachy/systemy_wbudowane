#include <avr/io.h>
#include <avr/interrupt.h>
#include "../include/usart.h"

// Inicjalizacja Timer 0 do generowania przerwania co pewien czas (dla migania LED_0)
void Timer0_Init(void) {
    TCCR0 = (1 << WGM01) | (1 << CS02);  // Tryb CTC, preskaler 256
    OCR0 = 77;                           // Ustawienie wartości porównania (dla 1 Hz, F_CPU = 4 MHz)
    TIMSK |= (1 << OCIE0);                // Włączenie przerwania od porównania
}

// ISR dla przerwania Timer 0 (do migania LED_0)
ISR(TIMER0_COMP_vect) {
    PORTA ^= (1 << PA0);  // Zmieniamy stan diody LED_0
}

int main(void) {
    // Inicjalizacja portów A
    DDRA = 0xFF;  // Ustawienie wszystkich pinów PA0-PA7 jako wyjścia
    PORTA = 0x00;  // Ustawienie początkowego stanu diod na wyłączony

    // Inicjalizacja USART
    USART_Init(MYUBRR);  
    sei();  // Włączenie globalnych przerwań

    // Inicjalizacja Timera 0
    Timer0_Init();

    // Wysyłanie początkowego komunikatu
    USART_Transmit_String("Program uruchomiony\n");
    USART_Transmit_String("Nacisnij klawisz [1-7] aby sterowac diodami\n");

    while (1) {
        // Główna pętla programu - czeka na przerwania
    }
}