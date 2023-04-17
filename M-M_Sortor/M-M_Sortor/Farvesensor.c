/*
 * Farvesensor.c
 *
 * Created: 03-03-2023 09:53:29
 *  Author: rasmk
 */ 
/*
Power off
S0 = low
S1 = low

Scaling 20%
s0 = high
s1 = low
*/
/*
SO
*/


#define F_CPU 12000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LED_TEST.h"
#include "Servo.h"

#define delay 25
#define S0_PIN 3
#define S1_PIN 4
#define S2_PIN 5
#define S3_PIN 6
#define SENSOR_OUT_PIN 7

float redPW;
int red;
float greenPW;
int green;
float bluePW;
int blue;
float PW;

//Servo
#define RedAngle 50
#define GreenAngle 70
#define BlueAngle 95
#define YelloAngle 115
#define OrangeAngle 140
#define BrownAngle 165


volatile unsigned long timer_count = 0;

void setup_timer0() {
	// Set timer0 to run at 1 MHz
	TCCR0B |= (1 << CS01);
	// Enable overflow interrupt for timer0
	TIMSK0 |= (1 << TOIE0);
	// Enable global interrupts
	sei();
}

ISR(TIMER0_OVF_vect) {
	// Increment timer count every time timer0 overflows
	timer_count += 256;
}

unsigned long micros(){
	// Calculate the number of microseconds based on the timer count and clock frequency
	return (timer_count * 1200000UL) / F_CPU;
}

void initSensor(){
	//activate pins as output and input
	DDRD |= 0b01111000;
	//set pulse with scaling to 20%
	//PORTD = 0b00001000;	
	// Set S0 - S3 as outputs
	DDRD |= (1 << S0_PIN) | (1 << S1_PIN) | (1 << S2_PIN) | (1 << S3_PIN);
	// Set Pulse Width scaling to 20%
	PORTD |= (1 << S0_PIN);
	PORTD &= ~(1 << S1_PIN);
	// Set Sensor output as input
	DDRD &= ~(1 << SENSOR_OUT_PIN);
	PORTD &= ~(1 << SENSOR_OUT_PIN);
	
	setup_timer0();
}

void turnOffSensor(){
	PORTD = 0b00000000;
}

void turnOnSensor(){
	//Set PWM scaling to 20%
	PORTD = PORTD &= ~(1<< S0_PIN);
}
unsigned int getRedPW(){
	// Set sensor to read Red only
	PORTD &= ~(1 << S2_PIN);
	PORTD &= ~(1 << S3_PIN);
	_delay_ms(10);
	// Wait for the output to go LOW
	while (PIND & (1 << SENSOR_OUT_PIN)) {}
	// Wait for the output to go HIGH
	while (!(PIND & (1 << SENSOR_OUT_PIN))) {}
	// Measure the pulse width
	unsigned long startTime = micros();
	while (PIND & (1 << SENSOR_OUT_PIN)) {}
	unsigned long endTime = micros();
	// Calculate the pulse width in microseconds
	PW = endTime - startTime;
	// Return the value
	return PW;
}
unsigned int getGreenPW(){
	// Set sensor to read Green only
	//PORTD &= (1 << S2_PIN);
	//PORTD &= (1 << S3_PIN);
	PORTD = 0b01101000;
	_delay_ms(10);
	// Wait for the output to go LOW
	while (PIND & (1 << SENSOR_OUT_PIN)) {}
	// Wait for the output to go HIGH
	while (!(PIND & (1 << SENSOR_OUT_PIN))) {}
	// Measure the pulse width
	unsigned long startTime = micros();
	while (PIND & (1 << SENSOR_OUT_PIN)) {}
	unsigned long endTime = micros();
	// Calculate the pulse width in microseconds
	PW = endTime - startTime;
	// Return the value
	return PW;
}

unsigned int getBluePW(){
	// Set sensor to read Blue only
	//PORTD &= ~(1 << S2_PIN);
	//PORTD &= (1 << S3_PIN);
	PORTD = 0b01001000;
	_delay_ms(10);
	// Wait for the output to go LOW
	while (PIND & (1 << SENSOR_OUT_PIN)) {}
	// Wait for the output to go HIGH
	while (!(PIND & (1 << SENSOR_OUT_PIN))) {}
	// Measure the pulse width
	unsigned long startTime = micros();
	while (PIND & (1 << SENSOR_OUT_PIN)) {}
	unsigned long endTime = micros();
	// Calculate the pulse width in microseconds
	PW = endTime - startTime;
	// Return the value
	return PW;
}

void readcolor(){
	redPW = getRedPW(); // Read value for red light from color sensor
	_delay_ms(10);	 // Wait for sensor to stabilize
	greenPW = getGreenPW(); // Read value for green light from color sensor
	_delay_ms(10);	// Wait for sensor to stabilize
	bluePW = getBluePW(); // Read value for blue light from color sensor
	_delay_ms(10); // Wait for sensor to stabilize
	
	if(redPW > 100 && redPW < 130 && greenPW >125  && greenPW < 140 && bluePW < 100 && bluePW > 80) // If detected color is red
		setAngle(RedAngle); // Set the angle of the servo motor to sort the red object
	else if(redPW > 120 && redPW <140 && greenPW > 100 && greenPW <125 && bluePW < 90 && bluePW >75) // If detected color is green
		setAngle(GreenAngle); // Set the angle of the servo motor to sort the green object
	else if(redPW > 140 && redPW < 155 && greenPW >	115 && greenPW < 130 && bluePW > 60 && bluePW < 75) // If detected color is blue
		setAngle(BlueAngle); // Set the angle of the servo motor to sort the blue object	
	else{ // If detected color is not red, green or blue
		setAngle(BrownAngle); // Set the angle of the servo motor to sort the object as brown
	}	
	_delay_ms(100); // Wait for the servo to move to the desired position
	return; // End function
}


float testRedPW(){
	// Set sensor to read Red only
	PORTD &= ~(1 << S2_PIN);
	PORTD &= ~(1 << S3_PIN);
	_delay_ms(10);
	// Define integer to represent Pulse Width
	int PW;
	// Wait for the output to go LOW
	while (PIND & (1 << SENSOR_OUT_PIN)) {}
	// Wait for the output to go HIGH
	while (!(PIND & (1 << SENSOR_OUT_PIN))) {}
	// Measure the pulse width
	unsigned long startTime = micros();
	while (PIND & (1 << SENSOR_OUT_PIN)) {}
	unsigned long endTime = micros();
	// Calculate the pulse width in microseconds
	PW = endTime - startTime;
	// Return the value
	return PW;
}

float testGreenPW(){
	// Set sensor to read Green only
	PORTD &= (1 << S2_PIN);
	PORTD &= (1 << S3_PIN);
	_delay_ms(10);
	// Define integer to represent Pulse Width
	int PW;
	// Wait for the output to go LOW
	while (PIND & (1 << SENSOR_OUT_PIN)) {}
	// Wait for the output to go HIGH
	while (!(PIND & (1 << SENSOR_OUT_PIN))) {}
	// Measure the pulse width
	unsigned long startTime = micros();
	while (PIND & (1 << SENSOR_OUT_PIN)) {}
	unsigned long endTime = micros();
	// Calculate the pulse width in microseconds
	PW = endTime - startTime;
	// Return the value
	return PW;
}

float testBluePW(){
	// Set sensor to read Blue only
	//PORTD &= ~(1 << S2_PIN);
	//PORTD &= (1 << S3_PIN);
	PORTD = 0b01001000;
	
	_delay_ms(10);
	// Define integer to represent Pulse Width
	int PW;
	// Wait for the output to go LOW
	while (PIND & (1 << SENSOR_OUT_PIN)) {}
	// Wait for the output to go HIGH
	while (!(PIND & (1 << SENSOR_OUT_PIN))) {}
	// Measure the pulse width
	unsigned long startTime = micros();
	while (PIND & (1 << SENSOR_OUT_PIN)) {}
	unsigned long endTime = micros();
	// Calculate the pulse width in microseconds
	PW = endTime - startTime;
	// Return the value
	return PW;
}

