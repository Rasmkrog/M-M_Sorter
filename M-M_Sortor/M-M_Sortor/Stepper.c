/*
 * Stepper.c
 *
 * Created: 02-03-2023 12:50:31
 *  Author: rasmk
 */ 
/*
10 - 13
pin 10 - nr1 - out1 (RØD)
pin 11 - nr2 - out2 (BLÅ)
pin 12 - nr3 - out3 (GRØN)
pin 13 - nr4 - out4 (SORT)

CunterClockwise 
pin10
pin11
pin13
pin12

Clockwise
pin12
pin13
pin11
pin10
*/
#include <avr/io.h>
#include <util/delay.h>

#define delayms 40
#define pin10 0b000100
#define pin11 0b001000
#define pin12 0b010000
#define pin13 0b100000
int cw[] = {pin10, pin11, pin13, pin12};
int ccw[] = {pin13, pin10, pin12, pin11};

void initStepper(){
	DDRB |= 0xFF;
}

void step(float _steps, int direction){
	if(direction){
		for(float j = 0; j <= _steps; j++){
			for (int i = 0; i < 4; i++)
			{
				PORTB = cw[i];
				_delay_ms(delayms);
			}
		}
		PORTB = 0b0;

	}
	else{
		for(float j = 0; j < _steps; j++){
			for (int i = 0; i < 4; i++)
			{
				PORTB = ccw[i];
				_delay_ms(delayms);
			}
		}
		PORTB = 0b00000000;
	}
		
}

#define STEPPER_PIN_1 2
#define STEPPER_PIN_2 4
#define STEPPER_PIN_3 5
#define STEPPER_PIN_4 3

void setup_io(){
	DDRB |= (1 << STEPPER_PIN_1) | (1 << STEPPER_PIN_2) | (1 << STEPPER_PIN_3) | (1 << STEPPER_PIN_4);
}


void rotate_stepper(int degrees){
	const int STEPS_PER_REV = 200;
	const int DELAY_TIME_MS = 40;
	const float STEPS_PER_DEGREE = (float) STEPS_PER_REV / 360;

	int steps = (int) (degrees * STEPS_PER_DEGREE);
	
	for (int i = 0; i < steps; i++) {
	PORTB |= (1 << STEPPER_PIN_1);
	_delay_ms(DELAY_TIME_MS);
	PORTB |= (1 << STEPPER_PIN_2);
	_delay_ms(DELAY_TIME_MS);
	PORTB |= (1 << STEPPER_PIN_3);
	_delay_ms(DELAY_TIME_MS);
	PORTB |= (1 << STEPPER_PIN_4);
	_delay_ms(DELAY_TIME_MS);
	
	PORTB &= ~(1 << STEPPER_PIN_1);
	_delay_ms(DELAY_TIME_MS);
	PORTB &= ~(1 << STEPPER_PIN_2);
	_delay_ms(DELAY_TIME_MS);
	PORTB &= ~(1 << STEPPER_PIN_3);
	_delay_ms(DELAY_TIME_MS);
	PORTB &= ~(1 << STEPPER_PIN_4);
	_delay_ms(DELAY_TIME_MS);
	}
	PORTB = 0b00;	 

 }

