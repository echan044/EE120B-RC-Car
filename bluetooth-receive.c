/*
 * echan044_bluetooth.c
 *
 * Created: 6/5/2018 6:14:43 PM
 * Author : TheEr
 */ 

#include <avr/io.h>
#include "usart.h"

int main(void) {
	//DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port C's 8 pins as outputs,
	
	initUSART(0);
	
	
	char data;
	
	
	
    /* Replace with your application code */
    while (1) {
		data = USART_Receive(0);
		if (data == '1') {
			PORTB = 0x01;
		}
		else if (data == '2') {
			PORTB = 0x02;
		}
		else if (data == '3') {
			PORTB = 0x04;
		}
		
    }
}

