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
#include "LED_TEST.h"
#include "hallEffect.h"

//int offset = 520;
#define offset 600
#define range 180
int slowturndelay = 120;
int fastturndelay = 80;

//Stepper
//one rev is 200 aka 50 steps called to the function stepper steps


//Servo
#define RedAngle 50
#define GreenAngle 70
#define BlueAngle 95
#define YelloAngle 115
#define OrangeAngle 140
#define BrownAngle 165

int main(void)
{
	DDRC = 0b00100011;
	//initSensor();
	//inithallEffect();
    initServo(offset);
	initStepper();
	int counter = 0;
	int angle= 20;
	//setAngle(170);
	//_delay_ms(1000);
	
	//setup_io();
	//_delay_ms(100);
	//step(50,1);
	
	//_delay_ms(1000);
	
	/*readcolor();
	_delay_ms(3000);*/
    while(1) {	
		
		step(25,1);
		_delay_ms(1000);

		//rotate_stepper(10);			
		/*if(PINC5 == 1){
		PORTC = 0b00100000;	
		}*/
		//getGreenPW();
		//testBluePW();
		/*readcolor();
		_delay_ms(2000);*/
		
		if(PINC & (1<<1)){
			counter++;
			_delay_ms(1000);
		}
		switch(counter){
			case 1 :{
				setAngle(RedAngle);
				break;
			}
			case 2:{
				setAngle(GreenAngle);
				break;
			}
			case 3:{
				setAngle(BlueAngle);
				break;
			}
			case 4:{
				setAngle(YelloAngle);
				break;
			}
			case 5:{
				setAngle(OrangeAngle);
				break;
			}
			case 6:{
				setAngle(BrownAngle);
				break;
			}
		}
		if(counter > 6){
			counter = 1;
		}
		
		//while(detect());
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
		}
    return 0;
}

