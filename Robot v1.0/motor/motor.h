/*
 * motorDriver.h
 *
 * Created: 11.02.2021 16:34:05
 *  Author: Piotrek
 */ 


#ifndef MOTORDRIVER_H_
#define MOTORDRIVER_H_

#include "board.h"
#include "pwmClass.h"
#include "GPIO.h"


#define DIR1_PIN PIO_OER_P2 //PB2
//PA3
#define MOTOR_1_PORT PIOB
#define MOTOR_2_PORT PIOA
#define PERIOD 3000
#define DUTY 3000

enum {
	FORWARD = 0,
	BACKWARD = 1,	
};

enum CHANNEL {
	CH_1,
	CH_2,	
};

struct PWMConfiguration {
	
	Pio * pwmPORT;
	u_char peripheral;
	u_char channel;
	u_char prescaler;
	int period;
	int duty;
	long int peripheralPin;
	long int dirPin;
	Pio * motorPORT;
		
};

class Motor
{
public:
	Motor						();
	Motor						(CHANNEL channel);
	void goForward				(unsigned int speed); 
	void goBackward				(unsigned int speed);
	void stop					();
	
protected:
private:
	PWMClass motorPWM;
	GPIOClass motorGPIO;
	PWMConfiguration pwmConfig;
	u_char DIR;
	unsigned int speed;
	CHANNEL channel;
	void updateMotor			();
	int calculateSpeed			();
	void updateSpeed			();
	void updateDirection		();
	void configurePWM			();
};



#endif /* MOTORDRIVER_H_ */