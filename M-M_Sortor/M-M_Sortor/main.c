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
#include <stdlib.h>
#include "Servo.h"
#include "Stepper.h"
#include "Farvesensor.h"
#include "LED_TEST.h"

//int offset = 520;
#define offset 600
#define range 270
int slowturndelay = 120;
int fastturndelay = 80;

//Stepper
//one rev is 135 steps





int main(void)
{
	DDRB |= 0xFF;
	DDRC = 0x0F;
    //initServo(offset);
	//_delay_ms(10000);
	initStepper();
	//initLED();
	//initSensor();
    while(1) {
		//turnOnSensor();
		//readcolor();
		//_delay_ms(50);
		//testRedPW();
		//_delay_ms(50);
		//testGreenPW();
		//_delay_ms(50);
		//testBluePW();
		//_delay_ms(50);
		//turnOffSensor();
		
		//getBluePW();
		//getGreenPW();
		//getRedPW();
		//readcolor();
		//_delay_ms(50);
		
		//_delay_ms(100);
		//turnDegrees(rand() % range);
		//_delay_ms(50);
		
	    step(105, 1);
		_delay_ms(500);
		//turn(fastturndelay,range);
		//_delay_ms(100);
		}
    return 0;
}

