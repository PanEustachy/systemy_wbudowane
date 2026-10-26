#ifndef KEYBOARD1_H
#define KEYBOARD1_H



char* DDR;
char* PORT;
char* PIN;
char* DDRLED;
char* PORTLED;

void led_init(char led_port);
void led_set(char output);
void set_IO_registers(char port);
void kb_init(char kb_port);
unsigned char get_key(char kb_size);

#endif