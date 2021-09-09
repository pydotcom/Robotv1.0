/*
 * pwmClass.h
 *
 * Created: 06.02.2021 16:55:46
 *  Author: Piotrek
 */ 


#ifndef PWMCLASS_H_
#define PWMCLASS_H_

#include "board.h"

#define PWM_DIV 0x2
#define PWM_LED PIO_PSR_P14
#define PWM_SERVO PIO_PSR_P0
#define PWM_SERVO_DEGREE_CONST 3562
#define PWM_SERVO_ADC_CONST 3281 /*3375*///for 1ms - 2ms
#define PWM_SERVO_MULTIPIER 0.36621 /*0.18262*///for 1ms - 2ms
#define u_char unsigned char

enum {
	prescaler0 = PWM_CMR_CPRE_MCK,
	prescaler2 = PWM_CMR_CPRE_MCKDIV2,
	prescaler4 = PWM_CMR_CPRE_MCKDIV4,
	prescaler8 = PWM_CMR_CPRE_MCKDIV8,
	prescaler16 = PWM_CMR_CPRE_MCKDIV16,
	prescaler32 = PWM_CMR_CPRE_MCKDIV32,
	prescaler64 = PWM_CMR_CPRE_MCKDIV64,
	prescaler128 = PWM_CMR_CPRE_MCKDIV128,
	prescaler256 = PWM_CMR_CPRE_MCKDIV256,
	prescaler512 = PWM_CMR_CPRE_MCKDIV512,
	prescaler1024 = PWM_CMR_CPRE_MCKDIV1024,
};

enum {
	A = 1,
	B = 0,
};

class PWMClass
{
public:
	PWMClass();
	void pwmAddChannel				(u_char peripheral, long int peripheralPin, Pio * PORT_ , u_char channel, u_char prescaler, int period, int duty);
	void pwmServoUpdateDuty			(double adcValue, u_char channel);
	void pwmUpdateDuty				(int newValue, u_char channel);
protected:
private:
};



#endif /* PWMCLASS_H_ */