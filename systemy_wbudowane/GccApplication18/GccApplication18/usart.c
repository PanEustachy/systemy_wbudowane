#include "usart.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

volatile uint8_t last_error = 0; // Zmienna do przechowywania ostatniego b��du USART


// Inicjalizacja USART
void USART_Init(void) {
	// Ustawienie warto�ci UBRR
	uint16_t ubrr = MYUBRR;
	UBRRH = (uint8_t)(ubrr >> 8);  // Wy�szy bajt UBRR
	UBRRL = (uint8_t)ubrr;         // Ni�szy bajt UBRR

	// W��czenie nadajnika, odbiornika oraz przerwa� odbioru i opr�nienia rejestru danych
	UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE) | (1 << UDRIE);

	// Konfiguracja formatu ramki: 8 bit�w danych, brak parzysto�ci, 1 bit stopu
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);

	// Zerowanie flagi b��d�w
	last_error = 0;
}

// Funkcja do nadawania pojedynczego bajtu
void USART_TransmitByte(uint8_t data) {
	while (!(UCSRA & (1 << UDRE)));  // Czekanie na opr�nienie rejestru
	UDR = data;                      // Wys�anie bajtu danych
}

// Funkcja do odbierania pojedynczego bajtu
uint8_t USART_ReceiveByte(void) {
	while (!(UCSRA & (1 << RXC)));  // Czekanie na zako�czenie odbioru
	if (UCSRA & ((1 << FE) | (1 << DOR) | (1 << PE))) {
		last_error = UCSRA & ((1 << FE) | (1 << DOR) | (1 << PE));  // Zapis b��du
		return 0;  // Zwr�� 0 przy b��dzie
	}
	char znak = UDR;
	USART_TransmitByte(znak);
	return znak;  // Zwr�� odebrany bajt
}

// Funkcja do wysy�ania ci�gu znak�w (string)
void USART_TransmitString(const char* str) {
	while (*str) {
		USART_TransmitByte(*str);
		str++;
	}
}

// Funkcja do odbierania ci�gu znak�w (z okre�leniem maksymalnej d�ugo�ci)
void USART_ReceiveString(char* buffer, uint8_t maxLen) {
	uint8_t i = 0;
	for (i = 0; i < maxLen - 1; i++) {
		char received = USART_ReceiveByte();
		if (received == '\n' || received == '\r') break;  // Zako�czenie stringu przy znaku nowej linii
		buffer[i] = received;
	}
	buffer[i] = '\0';  // Dodanie null-terminatora
}

// Funkcja do pobrania ostatniego b��du USART
uint8_t USART_GetLastError(void) {
	uint8_t error = last_error;
	last_error = 0;  // Wyzerowanie b��du po odczycie
	return error;
}


// Przerwanie odbioru danych (RX Complete)
ISR(USART_RXC_vect) {
	// Obs�uga odbioru danych � opcjonalnie mo�na doda� przetwarzanie w przerwaniu
	uint8_t received_data = UDR;
	if (UCSRA & ((1 << FE) | (1 << DOR) | (1 << PE))) {
		last_error = UCSRA & ((1 << FE) | (1 << DOR) | (1 << PE));  // Zapis b��du
	}
	// Dodaj kod do obs�ugi odbioru, np. buforowanie danych
}

