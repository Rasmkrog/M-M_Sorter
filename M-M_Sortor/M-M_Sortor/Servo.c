/*
 * Servo.c
 *
 * Created: 24-01-2023 14:14:29
 *  Author: rasmk
 */ 
#include <util/delay.h>
#include <avr/io.h>
int offset;

void initServo(unsigned int _offset){
	DDRB |= 1 << PINB1;
	// Set pin 9 on arduino to output
	/* 1. Set Fast PWM mode 14: set WGM11, WGM12, WGM13 to 1 */
	/* 3. Set pre-scaler of 8 */
	/* 4. Set Fast PWM non-inverting mode */
	TCCR1A |= (1 << WGM11) | (1 << COM1A1);
	TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11);
	/* 2. Set ICR1 register: PWM period */
	ICR1 = 39999;
	/* Offset for correction */
	offset = _offset;
	/* 5. Center servo point */
	setAngle(100);
	//delay
	//_delay_ms(20000);
}


void setAngle(unsigned int degrees)
{
	/* Works like in math - 0 is the most counterclockwise point
	Calculates what 1 degree in stepps.
	*/
	int step = ((3999 + offset) - (1999 - offset))/180;
	//Takes the minimum point of the servo and adds the Steps times the argument degrees
	OCR1A = (1999 - offset) + (step * degrees);
}
/*
Function for turning from minimum point to max point in a continuous motion.
the function takes the parameters _turndelay, and range 
which is use to determine the speed of servo and the range which the servo should operate in.
*/
void turn(unsigned int _turndelay, unsigned int range){
	//Firste the servo goes from zero to the assigned range
	for(int j=1; j < range; j++){
		turnDegrees(j);
		delay_ms(_turndelay);
	}
	//Goes from assigned range to zero
	for(int j=range; j > 0; j--){
		turnDegrees(j);
		delay_ms(_turndelay);
	}
}

//these function is not use in the project but is keept for use in later projekts
void clockwise(){
	OCR1A = 3999 + offset;
}

void counterClockwise(){
	OCR1A = 1999 - offset;
}


//converts milliseconds to nanoseconds
void delay_ms(unsigned char milliseconds)
{
	while(milliseconds > 0)
	{
		milliseconds--;
		_delay_us(990);
	}
}
