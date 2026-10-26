#ifndef KEYBOARD_H
#define KEYBOARD_H



volatile unsigned char* DDR;
volatile unsigned char* PORT;
volatile unsigned char* PIN;

volatile unsigned char* DDRLED;
volatile unsigned char* PORTLED;

void led_init(char led_port);
void led_set(char output);
void set_IO_registers(char port);
void kb_init(char kb_port);
unsigned char get_key(char kb_size);

#endif