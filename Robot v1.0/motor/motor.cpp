/*
 * motorDriver.cpp
 *
 * Created: 11.02.2021 16:34:30
 *  Author: Piotrek
 */ 
#include "motor.h"

Motor::Motor(CHANNEL channel) {
	
	this->channel = channel;
	configurePWM();
	//initialize pwm channel for Motor
	motorPWM.pwmAddChannel(pwmConfig.peripheral, pwmConfig.peripheralPin, pwmConfig.pwmPORT, pwmConfig.channel, pwmConfig.prescaler, pwmConfig.period, pwmConfig.duty);
		
	//initialize output pins for DIR and set 0 for output
	motorGPIO.outputEnable(pwmConfig.motorPORT, pwmConfig.dirPin);
	motorGPIO.clearPin(pwmConfig.motorPORT, pwmConfig.dirPin); //go forward
	
	
	this->DIR = FORWARD;
	
}

/* ************************************************************************** */
/*   This function configure initial values for PWM channels depends on which */
/*   channel was chosen and fill structure according to channel */
/* ************************************************************************** */
/**
 * 
 * 
 * \return void
 */
void Motor::configurePWM() {
	
	switch(this->channel) {
		
		case CH_1:
			pwmConfig.peripheral = B;
			pwmConfig.peripheralPin = PIO_OER_P24;
			pwmConfig.pwmPORT = PIOA;
			pwmConfig.channel = 1;
			pwmConfig.prescaler = prescaler8;
			pwmConfig.period = PERIOD;
			pwmConfig.duty = DUTY;
			pwmConfig.motorPORT = PIOB;
			pwmConfig.dirPin = PIO_OER_P2;
			break;
			
		case CH_2:
			pwmConfig.peripheral = A;
			pwmConfig.peripheralPin = PIO_OER_P2;
			pwmConfig.pwmPORT = PIOA;
			pwmConfig.channel = 2;
			pwmConfig.prescaler = prescaler8;
			pwmConfig.period = PERIOD;
			pwmConfig.duty = DUTY;
			pwmConfig.motorPORT = PIOA;
			pwmConfig.dirPin = PIO_OER_P3;
			break;
	}
}

/* ************************************************************************** */
/*   This function change the motor speed to forward  */
/* ************************************************************************** */

/**
 * 
 * \param speed	-> new value of speed in range 0-100
 * 
 * \return void
 */
void Motor::goForward(unsigned int speed) {
	
	this->speed = speed;
	this->DIR = 0;	
	
	updateMotor();
}

/* ************************************************************************** */
/*   This function change the motor speed to reverse */
/* ************************************************************************** */

/**
 * 
 * \param speed	-> new value of speed in range 0-100
 * 
 * \return void
 */
void Motor::goBackward(unsigned int speed) {
	

	this->speed = speed;
	this->DIR = 1;
	
	updateMotor();
}

/* ************************************************************************** */
/*   This function stop motor  */
/* ************************************************************************** */

/**
 * 
 * \return void
 */
void Motor::stop() {
	
	this->speed = 0;
	
	updateMotor();	
}


void Motor::updateMotor() {
	
	updateDirection();
	updateSpeed();
}

/* ************************************************************************** */
/*   This function update motor direction*/
/* ************************************************************************** */
/**
 * 
 * 
 * \return void
 */
void Motor::updateDirection() {
	
	if(this->DIR == 1) {
		motorGPIO.setPin(pwmConfig.motorPORT, pwmConfig.dirPin); //go back
	}
	else if(this->DIR == 0) {
		motorGPIO.clearPin(pwmConfig.motorPORT, pwmConfig.dirPin); //go forward
	}
	
}


void Motor::updateSpeed() {
	
	motorPWM.pwmUpdateDuty(calculateSpeed(), pwmConfig.channel);	
	
}

/* ************************************************************************** */
/*   This function calculate speed for PWM based on PERIOD value*/
/* ************************************************************************** */
/**
 * 
 * 
 * \return int -> return speed value for PWM
 */
int Motor::calculateSpeed() {
	
	int speed;
	speed = this->speed * (-30) + PERIOD;
	
	return speed;
}

// void Motor::changeSpeed(unsigned int speed) {
// 	
// }
