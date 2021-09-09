/*
 * adc.cpp
 *
 * Created: 27.02.2021 16:19:15
 *  Author: Piotrek
 */ 

#include "adcClass.h"

ADCClass::ADCClass() {
	
	//ADC enable interrupt
	NVIC_EnableIRQ(ADC_IRQn);
	//enable ADC in PMC
	PMC->PMC_PCER0 = PMC_PCER0_PID29;
}

/* ************************************************************************** */
/*   This function set new channel for ADC  */
/* ************************************************************************** */
/**
 * \brief 
 * 
 * \param prescaler
 * \param tracktim
 * \param channel
 * 
 * \return void
 */
void ADCClass::adcSetChannel(u_char prescaler, u_char tracktim, u_char channel) {
	
	
	//set ADC prescaler, freerun and Track time
	ADC->ADC_MR = ADC_MR_PRESCAL(prescaler)
				| ADC_MR_TRACKTIM(tracktim);
	//enable interrupt of EOC CH0
	ADC->ADC_IER = (1 << channel); /*ADC_IER_EOC0;*/
	//int temp = ADC->ADC_ISR;
	//enable CH0 --> PA17
	ADC->ADC_CHER = (1 << channel);
		
}

void ADCClass::beginConversion() {
	//begins adc conversion
	ADC->ADC_CR = ADC_CR_START;
}