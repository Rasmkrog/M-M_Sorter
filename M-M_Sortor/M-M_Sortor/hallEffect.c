/*
 * hallEffect.c
 *
 * Created: 30-03-2023 13:47:09
 *  Author: rasmk
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "Servo.h"
#include "Stepper.h"
#include "Farvesensor.h"
#include "LED_TEST.h"

void inithallEffect(){
	DDRC = 0b00100001;
	
}

int detect(){
	if(PINC0 == 0){
		//PORTC &= (1<<5);
	PORTC = 0b100000;
	
	return 1;
		
	}
	else PORTC = 0b000000;
	return 0;

	
}


