/*
 * LCD.c
 *
 * Created: 2024-03-25 12:10:33 PM
 *  Author: Justin
 */ 
#include "LCD.h"

void LCD_init()
{
	DDRD |= 0x0C;
	DDRC |= 0x0F;
	
	_delay_ms(20);
	
	//4-bit mode, as defined by HD44780 datasheet
	PORTC = (PORTC & 0xF0) | 0x03;
	LCD_enable();
	_delay_ms(5);
	PORTD = (PORTC & 0xF0) | 0x03;
	LCD_enable();
	_delay_us(200);
	PORTC = (PORTC & 0xF0) | 0x03;
	LCD_enable();
	_delay_us(100);
	LCD_instruct(0x02);
	
	//2-line display mode
	LCD_instruct(FUNCTION | 0x08);
	//display on, no cursor
	LCD_instruct(DISPLAY | 0x04);
	//increment cursor
	LCD_instruct(ENTRY_MODE | 0x02);
	LCD_instruct(CLEAR);
	
	_delay_ms(2);
}

void LCD_instruct(uint8_t cmd)
{
	//mask bits 0-3 and shift MSB
	PORTC = (PORTC & 0xF0) | (cmd >> 4);
	PORTD &= ~(1 << RS);
	LCD_enable();
	
	_delay_us(100);
	
	//mask bits 0-3 and mask LSB
	PORTC = (PORTC & 0xF0) | (cmd & 0x0F);
	LCD_enable();
	
	_delay_ms(2);
}

void LCD_enable()
{
	PORTD |= (1 << EN);
	_delay_us(1);
	PORTD &= ~(1 << EN);
	_delay_us(1);
}

void LCD_char(uint8_t cmd)
{
	//MSB
	PORTC = (PORTC & 0xF0) | (cmd >> 4);
	PORTD |= (1 << RS);
	LCD_enable();
	
	_delay_us(100);
	
	//LSB
	PORTC = (PORTC & 0xF0) | (cmd & 0x0F);
	LCD_enable();
	
	_delay_ms(2);
}

void LCD_string(char* str)
{
	uint8_t n = 0;
	
	while (str[n] != 0)
	{
		LCD_char(str[n]);
		n++;
	}
}

void LCD_clear()
{
	LCD_instruct(CLEAR);
	_delay_ms(2);
	LCD_instruct(DDRAM | UPPER_ROW);
}