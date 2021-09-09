/*
 * clockClass.h
 *
 * Created: 08.02.2021 16:33:48
 *  Author: Piotrek
 */ 


#ifndef CLOCKCLASS_H_
#define CLOCKCLASS_H_

#include "board.h"

#define u_char unsigned char
#define PLL_MUL 0x7
#define MAIN_CLOCK_12MHz 0x2
#define MAIN_CLOCK_ST_TIME 0x8
#define MAIN_CLOCK_PRES PMC_MCKR_PRES_CLK_2
#define MAIN_CLK_CSS 0x1
#define PLL_CLK_CSS 0x2
#define PLL_CLK_CNT 0x3F
#define PLL_DIV_1 0x1

enum {
	prescaler_1 = PMC_MCKR_PRES_CLK_1,
	prescaler_2 = PMC_MCKR_PRES_CLK_2,
	prescaler_4 = PMC_MCKR_PRES_CLK_4,
	prescaler_8 = PMC_MCKR_PRES_CLK_8,
	prescaler_16 = PMC_MCKR_PRES_CLK_16,
	prescaler_32 = PMC_MCKR_PRES_CLK_32,	
	prescaler_64 = PMC_MCKR_PRES_CLK_64,
	prescaler_3 = PMC_MCKR_PRES_CLK_3,
};

enum {
	clock4MHz = 0x0,
	clock8MHz = 0x1,
	clock12MHz = 0x2,	
};

class ClockClass
{
public:
	ClockClass				();
	void PLLInit			(u_char multiplier, u_char counter, u_char divider);
	void switchToXtal		();
	void switchMainClock	(u_char frequency, u_char prescaler);
	void switchToPLL		();
protected:
private:
};

#endif /* CLOCKCLASS_H_ */