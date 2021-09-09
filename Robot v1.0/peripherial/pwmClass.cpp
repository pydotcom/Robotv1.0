/*
 * pwmClass.cpp
 *
 * Created: 06.02.2021 16:56:19
 *  Author: Piotrek
 
 */
 #include "pwmClass.h"
 
PWMClass::PWMClass() {
		
	
	
	//enable PWM in PMC
	PMC->PMC_PCER0 = PMC_PCER0_PID31;
		
		
	//NVIC_EnableIRQ(PWM_IRQn)
}

/* ************************************************************************** */
/*   This function adding new channel for PWM  */
/* ************************************************************************** */
/**
 * 
 * \param peripheral -> the peripheral number used for PWM output:
 *			1 -> Peripheral A; 0 -> Peripheral B
 * \param peripheralPin -> the pin we want to use for PWM e.g. PIO_ABCDSR_P14 or PIO_PSR_P14 etc.
 * \param PORT_ -> the Port which corresponds with PWM output PIN
 * \param channel -> channel number for PWM
 * \param prescaler -> enum prescalerx value where is 2^x e.g. prescaler2, prescaler4 etc.
 * \param period -> the period value
 * \param duty -> the duty must be between 0 and period 
 * 
 * \return void
 */
void PWMClass::pwmAddChannel(u_char peripheral, long int peripheralPin, Pio * PORT_ , u_char channel, u_char prescaler, int period, int duty) {
	
	//enable peripheral B
	if (!peripheral) {
		PORT_->PIO_ABCDSR[peripheral] = peripheralPin;
	}
	
	
	//disable PIO pin
	PORT_->PIO_PDR = peripheralPin;
	
	//set prescaler and divider (enable CLKA and CLKB)
// 	PWM->PWM_MR |= PWM_MR_PREB_MCKDIV32
// 	| PWM_MR_DIVB(PWM_DIV);

	//choose channel, set period 20ms, duty 50% for clk 12MHz
	PWM->PWM_CH_NUM[channel].PWM_CMR = prescaler;
	PWM->PWM_CH_NUM[channel].PWM_CPRD = period;
	PWM->PWM_CH_NUM[channel].PWM_CDTY = duty; 
	
	//enable interrupt CH0
	//PWM->PWM_IER = PWM_IER_CHID30;
	//enable channel 
	PWM->PWM_ENA = (0x1 << channel);
	

} 

// TODO change adcValue from double to int

/* ************************************************************************** */
/*   This function update duty cycle for servo.  */
/* ************************************************************************** */
/**
 * 
 * \param adcValue -> value receive from ADC from range 0 - 1024 (0 - 3.3V)
 * \param channel -> channel number for PWM
 * 
 * \return void
 */
void PWMClass::pwmServoUpdateDuty(double adcValue, u_char channel) {
	
	double duty;
	
	duty = adcValue * PWM_SERVO_MULTIPIER + PWM_SERVO_ADC_CONST;
	
	//PWM update duty
	PWM->PWM_CH_NUM[channel].PWM_CMR = PWM->PWM_CH_NUM[channel].PWM_CMR & ~PWM_CMR_CPD;
	PWM->PWM_CH_NUM[channel].PWM_CUPD = (int)duty;
}

/* ************************************************************************** */
/*   This function update duty cycle.  */
/* ************************************************************************** */
/**
 * \brief 
 * 
 * \param newValue -> new value for duty cycle
 * \param channel -> channel number for PWM
 * 
 * \return void
 */
void PWMClass::pwmUpdateDuty(int newValue, u_char channel) {
	
	//PWM update duty
	PWM->PWM_CH_NUM[channel].PWM_CMR &= ~PWM_CMR_CPD;
	PWM->PWM_CH_NUM[channel].PWM_CUPD = newValue;
}
