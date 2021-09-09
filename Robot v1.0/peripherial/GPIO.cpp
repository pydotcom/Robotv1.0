/*
 * GPIO.cpp
 *
 * Created: 11.02.2021 16:52:21
 *  Author: Piotrek
 */ 
#include "GPIO.h"

GPIOClass::GPIOClass() {
	//PMC PIOA set
	PMC->PMC_PCER0 = PMC_PCER0_PID11;
	//enable PIOB in PMC 
	PMC->PMC_PCER0 = PMC_PCER0_PID12;
	
}

/* ************************************************************************** */
/*   This function enable output for corresponding PIN  */
/* ************************************************************************** */
/**
 *
 * \param PORT_ -> the Port for PIN
 * \param portPin -> the pin we want to enable e.g PIO_OER_P0
 * 
 * \return void
 */
void GPIOClass::outputEnable(Pio * PORT_, long int portPin) {
	
	//output enable on pin
	PORT_->PIO_OER = portPin;
	
}

/* ************************************************************************** */
/*   This function enable input for corresponding PIN  */
/* ************************************************************************** */
/**
 * \brief 
 * 
 * \param PORT_ -> the Port for PIN
 * \param portPin -> the pin we want to enable e.g PIO_ODR_P0
 * \param pullup -> is enum value ON or OFF for enable or disable pull-up
 * 
 * \return void
 */
void GPIOClass::inputEnable(Pio * PORT_, long int portPin, Pullup pullup) {
	
	// input enable on pin
	PORT_->PIO_ODR = portPin;
	
	switch(pullup) {
		case ON:
			// pull up on for pin
			PORT_->PIO_PUER = portPin;
			break;
		case OFF:
			// pull up off for pin
			PORT_->PIO_PUDR = portPin;
			break;		
	}
	
}

/* ************************************************************************** */
/*   This function set PIN setting value 1 for corresponding pin  */
/* ************************************************************************** */
/**
 * \brief 
 * 
 * \param PORT_ -> the Port for PIN
 * \param portPin -> the pin we want to set e.g PIO_SODR_P0
 * 
 * \return void
 */
void GPIOClass::setPin(Pio * PORT_, long int portPin) {
	
	//set pin
	PORT_->PIO_SODR = portPin;
}

/* ************************************************************************** */
/*   This function clear PIN setting value 0 for corresponding pin  */
/* ************************************************************************** */
/**
 * \brief 
 * 
 * \param PORT_ -> the Port for PIN
 * \param portPin -> the pin we want to set e.g PIO_CODR_P0
 * 
 * \return void
 */
void GPIOClass::clearPin(Pio * PORT_, long int portPin) {
	
	//clear pin
	PORT_->PIO_CODR = portPin;
}


void GPIOClass::enableExtrInterrupt(Pio * PORT_, long int portPin, LEVEL_EDGE levelEdge) {
	
	// 	configure external interrupt on pin 16
	// pull up on pin 16
	//interrupt enable for pin 16
	PORT_->PIO_PUER = portPin;
	clearInterruptStatus(PORT_);
	PORT_->PIO_IER = portPin;
	
	switch(levelEdge) {
		case LOW:
			PORT_->PIO_LSR = portPin;
			PORT_->PIO_FELLSR = portPin;
			break;
		case HIGH:
			PORT_->PIO_LSR = portPin;
			PORT_->PIO_REHLSR = portPin;
			break;
		case FALLING:
			//interrupt source is an Edge detection event
			PORT_->PIO_ESR = portPin;
			//interrupt on falling edge
			PORT_->PIO_FELLSR = portPin;
			break;
		case RISING:
			//interrupt source is an Edge detection event
			PORT_->PIO_ESR = portPin;
			PORT_->PIO_REHLSR = portPin;
			break;
	}

	
	if(PORT_ == PIOA) {
		NVIC_EnableIRQ(PIOA_IRQn);
	}
	else if(PORT_ == PIOB) {
		NVIC_EnableIRQ(PIOB_IRQn);
	}
}

void GPIOClass::clearInterruptStatus(Pio * PORT_) {
	
	volatile int status = PORT_->PIO_ISR;
}