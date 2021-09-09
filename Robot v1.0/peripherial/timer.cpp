/*
 * timer.cpp
 *
 * Created: 09.02.2021 17:35:19
 *  Author: Piotrek
 */

#include "timer.h"

Timer::Timer() {
	//PMC TC set
	PMC->PMC_PCER0 = PMC_PCER0_PID23;
	
} 

void Timer::setChannel(Tc * TC_, u_char channel, u_char clock, int registerC) {
	//enable clock
	TC_->TC_CHANNEL[channel].TC_CCR = TC_CCR_CLKEN;
	//prescaler
	TC_->TC_CHANNEL[channel].TC_CMR |= clock;
	
	//set TC to 10ms
	TC_->TC_CHANNEL[channel].TC_CMR |= TC_CMR_WAVSEL_UP_RC;
	
	TC_->TC_CHANNEL[channel].TC_RC = registerC;
	
	//interrupt on RC compare
	TC_->TC_CHANNEL[channel].TC_IER = TC_IER_CPCS;
	/*volatile unsigned long status = TC0->TC_CHANNEL[channel].TC_SR;*/
	TC_->TC_CHANNEL[channel].TC_CCR |= TC_CCR_SWTRG;
	
	// this might not work just like this
	if(TC_ == TC0) {
		NVIC_EnableIRQ(TC0_IRQn);	
	}
	else if(TC_ == TC1) {
		NVIC_EnableIRQ(TC1_IRQn);	
	}
}
