/*
 * adc.h
 *
 * Created: 27.02.2021 15:43:11
 *  Author: Piotrek
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "board.h"


#define u_char unsigned char
#define ADC_PRESCALER 0x8 
#define ADC_TRACKTIM 0x4 

class ADCClass
{
	public:
	ADCClass();
	void adcSetChannel		(u_char prescaler, u_char tracktim, u_char channel);
	void beginConversion	(void);
	protected:
	private:
};

#endif /* ADC_H_ */