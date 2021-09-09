/*
 * clockClass.cpp
 *
 * Created: 08.02.2021 16:35:58
 *  Author: Piotrek
 */ 

#include "clockClass.h"

ClockClass::ClockClass() {
	
}

/* ************************************************************************** */
/*   This function init PLL parameters  */
/*	 After we initialize PLL we need to use one of the clock source by choosing */
/*	 function switchToXtal or switchMainClock. */
/*	 At the end we must use function switchPLL to activate PLL. */
/* ************************************************************************** */
/**
 * 
 * \param multiplier -> when PLL is used multiplier must be set between 1-2047. 0: PLL is deactivated
 * \param counter -> specifies the number of cycles before LOCK bit is set in PMC_SR
 * \param divider -> the divider must be set to 1 if we just want to use PLL or between 2-255 if we want divede clock
 * \param clockSource ->
 * 
 * \return 
 */
void ClockClass::PLLInit(u_char multiplier, u_char counter, u_char divider) {
	//initialize PLL
	PMC->CKGR_PLLAR = CKGR_PLLAR_MULA(multiplier)
					| CKGR_PLLAR_ONE
					| CKGR_PLLAR_PLLACOUNT(counter)
					| CKGR_PLLAR_DIVA(divider);
	while(!(PMC->PMC_SR & PMC_SR_LOCKA));
	
// 	if(clockSource) {
// 		switchToXtal();
// 	}
// 	else {
// 		switchMainClock();
// 	}
}

/* ************************************************************************** */
/*   This function switch clock to Xtal 12MHz  */
/* ************************************************************************** */
void ClockClass::switchToXtal() {
	//enable Xtal
	PMC->CKGR_MOR = CKGR_MOR_MOSCXTST(MAIN_CLOCK_ST_TIME)
					| CKGR_MOR_MOSCRCEN
					| CKGR_MOR_MOSCXTEN
					| CKGR_MOR_KEY(0x37);
	while(!(PMC->PMC_SR & PMC_SR_MOSCXTS));//MOSCXTS only in case of use XTAL
	
	//switch to XTAL oscillator
	PMC->CKGR_MOR =	 CKGR_MOR_MOSCXTST(MAIN_CLOCK_ST_TIME)
					| CKGR_MOR_MOSCSEL
					| CKGR_MOR_MOSCRCEN
					| CKGR_MOR_MOSCXTEN
					| CKGR_MOR_KEY(0x37);
	while(!(PMC->PMC_SR & PMC_SR_MOSCSELS));
}

/* ************************************************************************** */
/*   This function change parameters of main clock  */
/* ************************************************************************** */
/**
 * 
 * \param frequency -> frequency is enum value: clock4MHz, clock8MHz or clock12MHz for corresponding clock
 * \param prescaler -> prescalerx is enum value 2^x e.g. prescaler2, prescaler4 etc.
 * 
 * \return void
 */
void ClockClass::switchMainClock(u_char frequency, u_char prescaler) {
	//here we set only main clock
	PMC->CKGR_MOR = CKGR_MOR_MOSCRCF(frequency)
					| CKGR_MOR_MOSCXTST(MAIN_CLOCK_ST_TIME)
					| CKGR_MOR_MOSCRCEN
					| CKGR_MOR_KEY(0x37);
	while(!(PMC->PMC_SR & PMC_SR_MCKRDY));
	
	//set main clock prescaler
	PMC->PMC_MCKR = prescaler | MAIN_CLK_CSS;
	while(!(PMC->PMC_SR & PMC_SR_MCKRDY));
}

/* ************************************************************************** */
/*   This function switch to PLL after initialization  */
/* ************************************************************************** */
/**
 * 
 * 
 * \return void
 */
void ClockClass::switchToPLL() {
	
	//switch to PLL
	PMC->PMC_MCKR = (MAIN_CLOCK_PRES & ~PMC_MCKR_CSS_Msk)
 				  | PMC_MCKR_CSS(PLL_CLK_CSS);
	while(!(PMC->PMC_SR & PMC_SR_MCKRDY));
}