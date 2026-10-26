#ifndef USART_H
#define USART_H

#include <avr/io.h>
#include <avr/interrupt.h>


#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define F_CPU 16000000000UL

// Inicjalizacja USART z konfiguracją prędkości i ramki transmisji
void USART_Init(uint16_t ubrr);

// Funkcja wysyłająca pojedynczy znak przez USART
void USART_Transmit_Byte(uint8_t data);

// Funkcja wysyłająca ciąg znaków przez USART
void USART_Transmit_String(const char* str);

// Funkcja odbioru danych przez USART
uint8_t USART_Receive_Byte(void);

#endif