/*
 * motorDrive.cpp
 *
 * Created: 25.02.2021 18:09:14
 *  Author: Piotrek
 */ 

#include "motorDrive.h"

MotorDrive::MotorDrive() 
:motor1(CHANNEL::CH_1), motor2(CHANNEL::CH_2){
	
	adc.adcSetChannel(ADC_PRESCALER, ADC_TRACKTIM, 1);
	adc.adcSetChannel(ADC_PRESCALER, ADC_TRACKTIM, 2);
}

/* ************************************************************************** */
/*   This function move robot. Positive speed move forward negative backward */
/* ************************************************************************** */
/**
 * 
 * \param speedM1 -> motor1 speed takes values positive and negative from -100 to 100
 * \param speedM2 -> motor2 speed takes values positive and negative from -100 to 100
 * 
 * \return void
 */
void MotorDrive::move(int speedM1, int speedM2) {
	
	//MOTOR 1
	if(speedM1 >= 0 && speedM1 <= 100) {
		motor1.goForward(speedM1);
	}
	else if(speedM1 >= -100 && speedM1 < 0) {
		motor1.goBackward(-speedM1);
	}
	
	//MOTOR 2
	if(speedM2 >= 0 && speedM2 <= 100) {
		motor2.goForward(speedM2);
	}
	else if(speedM2 >= -100 && speedM2 < 0) {
		motor2.goBackward(-speedM2);
	}
}

void MotorDrive::getADCValue(int adcValueCH1, int adcValueCH2) {
	
	setSpeed(adcValueCH1, adcValueCH2);
	//setSpeed(adcValueCH2, M2);
	move(this->speedM1, this->speedM2);// this do not work correctly
}

/* ************************************************************************** */
/*   This function set speed for motors depending on adc values from analogs */
/*	 If analog 1 have value 0 we can turn right or left by using value from  */
/*	 analog 2. If analog 1 value is different than 0 robot move forward or */
/*	 backward but motors speed is subtracted by analog 2 value divided by */
/*	 @MOTOR_SPEED_DIVIDER which give us possibility to turn robot during moving*/
/* ************************************************************************** */
/**

 * 
 * \param adcValueCH1 -> digital value from first analog
 * \param adcValueCH2 -> digital value from second analog
 * 
 * \return void
 */
void MotorDrive::setSpeed(int adcValueCH1, int adcValueCH2) {
	
	int tempSpeedCH1 = calculateSpeed(adcValueCH1);
	int tempSpeedCH2 = calculateSpeed(adcValueCH2);
	
	if(tempSpeedCH1 == 0) {
		//here need to use only adcValue2 to move right or left
		this->speedM1 = - tempSpeedCH2;
		this->speedM2 = tempSpeedCH2;
	}
	else if(tempSpeedCH1 < 0) {
		if(tempSpeedCH2 < 0) {
			this->speedM1 = tempSpeedCH1 - (tempSpeedCH2 / MOTOR_SPEED_DIVIDER);
			this->speedM2 = tempSpeedCH1;
		}
		else if(tempSpeedCH2 > 0) {
			this->speedM1 = tempSpeedCH1;
			this->speedM2 = tempSpeedCH1 + (tempSpeedCH2 / MOTOR_SPEED_DIVIDER);
		}
		else {
			this->speedM1 = tempSpeedCH1;
			this->speedM2 = tempSpeedCH1;
		}
	}
	else if(tempSpeedCH1 > 0) {
		//here need to from speed backward subtract by MOTOR_POWER_DIVIDER of adcValueCH2 speed for corresponding motor
		
		if(tempSpeedCH2 < 0) {
			this->speedM1 = tempSpeedCH1 + (tempSpeedCH2 / MOTOR_SPEED_DIVIDER);
			this->speedM2 = tempSpeedCH1;
		}
		else if(tempSpeedCH2 > 0) {
			this->speedM1 = tempSpeedCH1;
			this->speedM2 = tempSpeedCH1 - (tempSpeedCH2 / MOTOR_SPEED_DIVIDER);
		}
		else {
			this->speedM1 = tempSpeedCH1;
			this->speedM2 = tempSpeedCH1;
		}
	}

}

int MotorDrive::calculateSpeed(int adcValue) {
	
	double speed;
	speed = MULTIPIER * adcValue + EQ_CONST;
	if(speed >= -8 && speed <= 8) {
		speed = 0;
	}
	return (int)speed;
}