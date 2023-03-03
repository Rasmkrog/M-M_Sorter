/*
 * LED_TEST.c
 *
 * Created: 03-03-2023 16:53:43
 *  Author: rasmk
 */ 
#define F_CPU 12000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_MASK 0x0F // define the LED mask for 4 LEDs
#define redLed 0
#define orangeLed 1
#define yellowLed 2
#define greenLed 3

void initLED(){
	DDRC |= LED_MASK;
}

void LEDTEST(){
	// turn on LEDs 0-3 in order
	PORTC |= (1 << 0); // LED 0 on
	_delay_ms(500); // wait for 500ms
	PORTC |= (1 << 1); // LED 1 on
	_delay_ms(500); // wait for 500ms
	PORTC |= (1 << 2); // LED 2 on
	_delay_ms(500); // wait for 500ms
	PORTC |= (1 << 3); // LED 3 on
	_delay_ms(500); // wait for 500ms
	
	//turn off LED's 0-3 in order
	PORTC &= ~(1 << 0); // LED 0 off
	_delay_ms(500); // wait for 500ms
	PORTC &= ~(1 << 1); // LED 1 off
	_delay_ms(500); // wait for 500ms
	PORTC &= ~(1 << 2); // LED 2 off
	_delay_ms(500); // wait for 500ms
	PORTC &= ~(1 << 3); // LED 3 off
	_delay_ms(500); // wait for 500ms
}


void turnOnLed(int color){
	DDRC |= LED_MASK;
	switch(color){
		case 0:
		PORTC |= (1<<redLed);
		break;
		
		case 1:
		PORTC |= (1<<orangeLed);
		break;
		
		case 2:
		PORTC |= (1<<yellowLed);
		break;
		
		case 3:
		PORTC |= (1<<greenLed);
		break;
		
		//last to colors blue and brown
		default:
		LEDTEST();
		break;
	}
}

void turnOffLED(){
	// turn off all LEDs
	PORTC &= ~(LED_MASK); // turn off all LEDs
}






