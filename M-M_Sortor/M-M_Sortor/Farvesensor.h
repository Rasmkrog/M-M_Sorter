/*
 * Farvesensor.h
 *
 * Created: 03-03-2023 09:53:45
 *  Author: rasmk
 */ 


#ifndef FARVESENSOR_H_
#define FARVESENSOR_H_
void setup_timer0();
unsigned long micros();
void initSensor();
void turnOffSensor();
void turnOnSensor();
unsigned int getRedPW();
unsigned int getGreenPW();
unsigned int getBluePW();
void readcolor();
float testRedPW();
float testGreenPW();
float testBluePW();


#endif /* FARVESENSOR_H_ */