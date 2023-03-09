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

#define F_CPU 12000000UL

#define delayms 40
#define pin10 0b000100
#define pin11 0b001000
#define pin12 0b010000
#define pin13 0b100000
int cw[] = {pin10, pin11, pin13, pin12};
int ccw[] = {pin13, pin10, pin12, pin11};

void initStepper(){
	DDRB = 0xFF;
}

void step(float steps, int direction){
	if(direction){
		for(int j = 0; j < steps; j++){
			for (int i = 0; i < 4; i++)
			{
				PORTB = cw[i];
				_delay_ms(delayms);
			}
		}
	}
	else{
		for(int j = 0; j < steps; j++){
			for (unsigned int i = 0; i < 4; i++)
			{
				PORTB = ccw[i];
				_delay_ms(delayms);
			}
		}
	}	
}

