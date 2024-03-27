/*
 * LCD.h
 *
 * Created: 2024-03-25 12:10:16 PM
 *  Author: Justin
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>

#define RS 2
#define EN 3

//instructions
#define CLEAR 0x01
#define RETURN 0x02
#define ENTRY_MODE 0x04
#define DISPLAY 0x08
#define CURSOR 0x10
#define FUNCTION 0x20
#define CGRAM 0x40
#define DDRAM 0x80

//DDRAM addresses
#define UPPER_ROW 0x00
#define LOWER_ROW 0x40

void LCD_init();
void LCD_instruct(uint8_t cmd);
void LCD_enable();
void LCD_char(uint8_t cmd);
void LCD_string(char* str);
void LCD_clear();


#endif /* LCD_H_ */