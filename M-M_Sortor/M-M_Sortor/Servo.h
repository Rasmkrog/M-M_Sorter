/*
 * Servo.h
 *
 * Created: 24-01-2023 14:12:16
 *  Author: rasmk
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_
void initServo(unsigned int _offset);
void turn(unsigned int _turndelay, unsigned int range);
void turndegree(unsigned int degree);
void clockwise();
void counterClockwise();
void delay_ms(unsigned char milliseconds);

#endif /* INCFILE1_H_ */