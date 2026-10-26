#include "../include/usart.h"



volatile uint8_t transmit_data = 0; // Przechowywany bajt do wysłania
volatile uint8_t data_ready = 0;    // Flaga gotowości bajtu do wysłania
volatile const char *transmit_string =0; // Wskaźnik na łańcuch znaków do wysłania

// Inicjalizacja USART
void USART_Init(uint16_t ubrr) {
    UBRRH = (uint8_t)(ubrr >> 8);
    UBRRL = (uint8_t)ubrr;
    UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE); // Włączenie odbioru, nadawania i przerwań RX
    UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); // 8 bitów danych, 1 bit stopu
}

// Funkcja wysyłająca pojedynczy bajt przez USART
void USART_Transmit_Byte(uint8_t data) {
    while (!(UCSRA & (1 << UDRE))); // Czekaj, aż bufor nadawczy będzie pusty
    UDR = data;                     // Załaduj bajt do rejestru UDR
}

// Funkcja wysyłająca ciąg znaków
void USART_Transmit_String(const char* str) {
    transmit_string = str; // Ustaw wskaźnik na łańcuch znaków do wysłania
    USART_Transmit_Byte(*transmit_string++); // Rozpocznij wysyłanie od pierwszego znaku
}

// Funkcja odbioru pojedynczego bajtu przez USART
uint8_t USART_Receive_Byte(void) {
    while (!(UCSRA & (1 << RXC))); // Czekaj, aż bajt zostanie odebrany
    return UDR;                     // Zwróć odebrany bajt
}

// ISR dla przerwania odbioru danych (USART_RXC_vect)
ISR(USART_RXC_vect) {
    uint8_t received_char = UDR;
    if (received_char >= '1' && received_char <= '7') {
        // Przełącz diodę LED odpowiadającą klawiszowi
        uint8_t led_number = received_char - '1';
        PORTA ^= (1 << led_number);
        USART_Transmit_Byte(received_char);  // Wysłanie odebranego znaku na terminal
    }
    else if (received_char == 'c') {
        // Wyłącz wszystkie diody LED_1 do LED_7
        PORTA &= 0x00; // Wyłącz diody
        USART_Transmit_String("\nDiody wylaczone\n");
    }
    else if (received_char == 's') {
        // Włącz wszystkie diody LED_1 do LED_7
        PORTA |= 0xFF; // Włącz diody
        USART_Transmit_String("\nDiody wlaczone\n");
    }
    else {
        // Błędny znak
        USART_Transmit_String("\nBlędny znak\n");
    }
}