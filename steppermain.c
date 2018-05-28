#include <avr/io.h>

#include "io.c"
#include <avr/interrupt.h>
#include <keypad.h>

#include <util/delay.h>
#include "stepper.c"

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

#define A0 (~PINA & 0x01)
#define A1 (~PINA & 0x02)


void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
	OCR1A = 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}

void TimerISR() {
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

enum LCD_states {start, noMove, speedUp, slowDown} currentState;

void LCD_tick() {
	unsigned char keypress = GetKeypadKey();
	
	//first set of switch statements - state transitions
	
	//second state of switch statements - declaratives
	switch(keypress) {
		case '\0':
			
			break;
		case '1':
			LCD_WriteData(1 + '0');
			break; 
		case '2':
			LCD_WriteData(2 + '0');
			break;
	}
}

void main() {

	//Initialize the stepper library
	StepperInit();

	_delay_loop_2(1000);

	while(1) {

		for(uint16_t i=0;i<24*85;i++)
		{
			StepperStepCW();     //Step Clock wise

			_delay_loop_2(5000);
		}

		for(uint16_t i=0;i<24*85;i++)
		{
			StepperStepCCW();    //Step Counter Clock wise

			_delay_loop_2(5000);
		}
	}

}

