/*
 * Stepper.h
 *
 * Created: 02-03-2023 12:50:07
 *  Author: rasmk
 */ 


#ifndef STEPPER_H_
#define STEPPER_H_
void initStepper();
void step(float steps, unsigned int direction);
void takestep();
#endif /* STEPPER_H_ */