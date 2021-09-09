/*
 * timer.h
 *
 * Created: 09.02.2021 17:34:38
 *  Author: Piotrek
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "board.h"

#define u_char unsigned char

enum {
	clock1 = TC_CMR_TCCLKS_TIMER_CLOCK1,
	clock2 = TC_CMR_TCCLKS_TIMER_CLOCK2,
	clock3 = TC_CMR_TCCLKS_TIMER_CLOCK3,
	clock4 = TC_CMR_TCCLKS_TIMER_CLOCK4,
	clock5 = TC_CMR_TCCLKS_TIMER_CLOCK5,	
};


class Timer
{
public:
	Timer				();
	void setChannel		(Tc * TC_, u_char channel, u_char clock, int registerC);
protected:
private:
};


#endif /* TIMER_H_ */