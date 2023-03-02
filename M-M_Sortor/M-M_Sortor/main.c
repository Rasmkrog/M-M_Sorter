/*
 * M-M_Sortor.c
 *
 * Created: 02-03-2023 10:37:17
 * Author : rasmk
 */ 
/*
Pins i brug
Farvesensor
S0 : pin 4
S1 : pin 5
S2 : pin 6
S3 : pin 7 
sensorOut/Out : 8

Servo
PWM timer x : pin 9

Stepper
pin 10 , 11 , 12 , 13


*/


#define F_CPU 12000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Servo.h"
#include "Stepper.h"

int offset = 520;
int range = 180;
int slowturndelay = 120;
int fastturndelay = 50;




int main(void)
{
	DDRB |= 0xFF;
    initServo(offset);
	initStepper();
    while(1) {
	    step(10, 1);
		turn(fastturndelay,range);
		//_delay_ms(100);
		
		}
    return 0;
}

