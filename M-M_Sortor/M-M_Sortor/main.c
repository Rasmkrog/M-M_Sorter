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

Hall effect
port C pin A0

Knap 
port C pin A1

*/

#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include "Servo.h"
#include "Stepper.h"
#include "Farvesensor.h"
#include "TestScript.h"
#define offset 600
#define range 180
#define RedAngle 50
#define GreenAngle 75
#define BlueAngle 100
#define YelloAngle 120
#define OrangeAngle 145
#define BrownAngle 170

int main(void)
{
	DDRC = 0b00100011;
	initSensor();
	//inithallEffect();
    initServo(offset);
	initStepper();
	int counter = 0;
	int angle= 20;
	//setAngle(170);
	_delay_ms(1000);
	step(13,1);
	_delay_ms(1000);
	
    while(1) {		
		readcolor(); // Read color sensor
		_delay_ms(1500);
		for(unsigned char i = 0; i < 12; i++) // Move stepper motor
			step(1,1);
		_delay_ms(1000);
		readcolor(); // Read color sensor again
		_delay_ms(1500);
		
		for(unsigned char i = 0; i < 13; i++) // Move stepper motor
			step(1,1);		
	}
	return 0;
}

