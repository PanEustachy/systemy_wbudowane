#ifndef USART_H
#define USART_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

// Konfiguracja USART

#define F_CPU 4000000UL  // Czêstotliwoœæ CPU 4 MHz
#define BAUD 9600        // Prêdkoœæ transmisji 9600 bps
#define MYUBRR F_CPU/16/BAUD-1



// Deklaracje funkcji
void USART_Init(void);
void USART_TransmitByte(uint8_t data);
uint8_t USART_ReceiveByte(void);
void USART_TransmitString(const char* str);
void USART_ReceiveString(char* buffer, uint8_t maxLen);
uint8_t USART_GetLastError(void);

#endif