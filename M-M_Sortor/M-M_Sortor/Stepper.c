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
// Define the CPU frequency
#define F_CPU 12000000UL

// Include the necessary libraries
#include <avr/io.h>
#include <util/delay.h>

// Define the delay time for each step and the pins used by the stepper motor
#define delayms 20
#define pin10 0b00000100
#define pin11 0b00001000
#define pin12 0b00010000
#define pin13 0b00100000
#define step1 2
#define step2 3
#define step3 5
#define step4 4

// Define the step order for the motor, both forward and reversed
int stepOrder[] ={step1, step2, step3, step4};
int stepOrderReversed[] = {step4, step3, step2, step1};

// Define the pin order for clockwise and counterclockwise movement
int cw[] = {pin10, pin11, pin13, pin12};
int ccw[] = {pin12, pin13, pin11, pin10};

// Function to initialize the stepper motor
void initStepper(){
	DDRB |= (1 << step1) | (1 << step2) | (1 << step3) | (1 << step4); // Set the pins used by the motor to output
}

// Function to step the motor
void step(float steps, int direction){
	if(direction){
		for(float j = 0; j < steps; j++){ // Loop through the number of steps to take
			for (int i = 0; i < 4; i++) // Loop through the four pins used by the motor
			{
				PORTB |= (1 << stepOrderReversed[i]); // Set the current pin to high
				_delay_ms(5); // Wait a short time to ensure the pin is high before moving to the next one
				PORTB &= ~(1<< stepOrderReversed[i]); // Set the current pin to low
				_delay_ms(delayms); // Wait for the set delay time before moving to the next pin
			}
		}
	}
	else{ // Same as above but for counterclockwise movement
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
