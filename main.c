/*
 * LCDtest.c
 *
 * Created: 2024-03-26 3:38:53 PM
 * Author : Justin
 */ 

#include <avr/io.h>
#include "LCD.h"

int main(void)
{
    LCD_init();
	
	LCD_string("Group 13 Storm");
	LCD_instruct(DDRAM | LOWER_ROW);
	LCD_string("Warning Project!");
	
	while(1);
}

