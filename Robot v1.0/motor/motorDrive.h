/*
 * motorDrive.h
 *
 * Created: 25.02.2021 18:01:07
 *  Author: Piotrek
 */ 


#ifndef MOTORDRIVE_H_
#define MOTORDRIVE_H_

#include "board.h"
#include "motor.h"
#include "ADCClass.h"

#define MULTIPIER -0.1953125
#define EQ_CONST 100
#define MOTOR_SPEED_DIVIDER 5


#endif /* MOTORDRIVE_H_ */

enum MOTOR {
	M1,
	M2,	
};

class MotorDrive
{
public:
	MotorDrive				();
	void move				(int speedM1, int speedM2);
	void getADCValue		(int adcValueCH1, int adcValueCH2);
	
protected:
private:
	Motor motor1;
	Motor motor2;
	ADCClass adc;
	int speedM1;
	int speedM2;
	void setSpeed			(int adcValueCH1, int adcValueCH2);
	int calculateSpeed		(int adcValue);
};