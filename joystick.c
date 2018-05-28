/*
PINOUT FOR JOYSTICK HERE: https://www.parallax.com/sites/default/files/downloads/27800-2-Axis-Joystick-Documentation-v1.2.pdf
LEDS to PORTB
LCD to PORTS D and C
*/


#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "io.c"


void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0XFF; PORTD = 0x00;

	unsigned char magnitude = 0x00;

	LCD_init();	
	ADC_init();
	LCD_Cursor(1);
	while (1) {
		magnitude = ADC;
		
		unsigned char tempVal = 0x00;
		
		tempVal = (char)magnitude;
		
		LCD_Cursor(1);
		/*
		LCD_WriteData('x');
		LCD_WriteData('=');
		*/
		LCD_WriteData(tempVal + '0');
		
		if (tempVal + '0' == 'N') {
			PORTB = 0x04;
		}
		else if (tempVal + '0' == 'W') {
			PORTB = 0x08;
		}
		else {
			PORTB = 0x02;
		}
		
		/*
		LCD_WriteData('y');
		LCD_WriteData('=');
		*/
	}
}

