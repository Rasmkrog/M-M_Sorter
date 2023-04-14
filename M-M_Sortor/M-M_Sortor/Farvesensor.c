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

#define delay 50
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

int map(float x, int in_min, int in_max, int out_min, int out_max){
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void readcolor(){
	/*int avrRed;
	//get red PW and set it as redPW
	for(int i = 0; i<9;i++){
		redPW = getRedPW();
		avrRed = avrRed + map(redPW, 100 , 0 , 0 , 255);
		_delay_ms(delay);
	}
	red = avrRed/10; 
	
	int avrGreen;
	//get red PW and set it as redPW
	for(int i = 0; i<9;i++){
		greenPW = getGreenPW();
		avrGreen = avrGreen + map(greenPW, 100 , 0 , 0 , 255);
		_delay_ms(delay);
	}
	green = avrGreen/10;
	
	//get blue PW and set is as bluePW
	int avrBlue;
	for(int i = 0; i<9;i++){
		bluePW = getBluePW();
		avrBlue = avrBlue + map(bluePW, 100 , 0, 0 , 255);
		_delay_ms(delay);
	}
	blue = avrBlue/10;*/
	
	redPW = getRedPW();
	red + map(redPW, 100 , 0 , 0 , 255);
	_delay_ms(delay);
	
	greenPW = getGreenPW();
	green = map(greenPW, 100 , 0 , 0 , 255);
	_delay_ms(delay);
	
	bluePW = getBluePW();
	blue = map(bluePW, 100 , 0, 0 , 255);
	_delay_ms(delay);
	
	
	if(blue >red && blue >green){
		setAngle(BlueAngle);
	}
	else if(red > blue && red > green){
		setAngle(RedAngle);
	}	
	else if(green > blue && green > red){
		setAngle(GreenAngle);
	}
	return;
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




	





