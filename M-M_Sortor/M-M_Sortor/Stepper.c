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
#define F_CPU 12000000UL
#include <avr/io.h>
#include <util/delay.h>


#define delayms 20
#define pin10 0b00000100
#define pin11 0b00001000
#define pin12 0b00010000
#define pin13 0b00100000
#define step1 2
#define step2 3
#define step3 5
#define step4 4

int stepOrder[] ={step1, step2, step3, step4};
int stepOrderReversed[] = {step4, step3, step2, step1};

int cw[] = {pin10, pin11, pin13, pin12};
int ccw[] = {pin12, pin13, pin11, pin10};

void initStepper(){
    DDRB |= (1 << step1) | (1 << step2) | (1 << step3) | (1 << step4);
}

void step(float steps, int direction){
	if(direction){
		for(float j = 0; j < steps; j++){
			for (int i = 0; i < 4; i++)
			{
				PORTB |= (1 << stepOrderReversed[i]);
				_delay_ms(5);
				PORTB &= ~(1<< stepOrderReversed[i]);
				_delay_ms(delayms);
			}
		}
		

	}
	else{
		for(float j = 0; j < steps; j++){
			for (int i = 0; i < 4; i++)
			{
				PORTB |= (1 << stepOrder[i]);
				_delay_ms(5);
				PORTB &= ~(1<< stepOrder[i]);
				_delay_ms(delayms);
			}
		}
	
	}
}

/*
void step(float steps, int direction, int _delay){
	if(direction){
		for(float j = 0; j < steps; j++){
			for (int i = 0; i < 4; i++)
			{
				PORTB = ccw[i];
				_delay_ms(5);
				PORTB = 0b000000;
				_delay_ms(delayms);
			}
		}
		PORTB = 0b00000000;

	}
	else{
		for(float j = 0; j < steps; j++){
			for (int i = 0; i < 4; i++)
			{
				PORTB = ccw[i];
				_delay_ms(delayms);
			}
		}
		PORTB = 0b000000;
	}
		
}
*/