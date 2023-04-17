/*
 * TestScript.c
 *
 * Created: 17-04-2023 22:19:48
 *  Author: rasmk
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

#define offset 600
#define range 180
#define RedAngle 50
#define GreenAngle 75
#define BlueAngle 100
#define YelloAngle 120
#define OrangeAngle 145
#define BrownAngle 170
int order[]  = {RedAngle, BlueAngle, YelloAngle, BrownAngle, GreenAngle, OrangeAngle, GreenAngle, BrownAngle, BlueAngle, RedAngle};


void test()
{
	// Set port C pins 0, 1, and 5 to output mode
	DDRC = 0b00100011;
	// Initialize sensor, servo, and stepper
	initSensor();
	initServo(offset);
	initStepper();
	// Initialize counter and angle
	int counter = 0;
	int angle= 20;
	// Wait for 1 second
	_delay_ms(1000);
	// Move the stepper motor 13 steps clockwise
	step(13,1);
	// Wait for 1 second
	_delay_ms(1000);

	// Loop 10 times
	while(counter < 10) {
		// Set the angle of the servo to the current value in the order array at index counter
		setAngle(order[counter]);
		// Increment the counter by 1
		counter = counter+1;
		// Wait for 1 second
		_delay_ms(1000);
		// Move the stepper motor 12 steps clockwise
		for(unsigned char i = 0; i < 12; i++)
		step(1,1);
		// Wait for 1 second
		_delay_ms(1000);
		// Set the angle of the servo to the next value in the order array at index counter
		setAngle(order[counter]);
		// Increment the counter by 1
		counter = counter+1;
		// Wait for 1.5 seconds
		_delay_ms(1500);

		// Move the stepper motor 13 steps clockwise
		for(unsigned char i = 0; i < 13; i++)
		step(1,1);
		// Wait for 1.5 seconds
		_delay_ms(1500);
	}
}