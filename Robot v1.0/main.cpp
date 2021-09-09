// /*
//  * Robot v1.0.cpp
//  *
//  * Created: 27.02.2021 15:34:38
//  * Author : Piotrek
//  */ 


#include "board.h"
#include "peripherial/ADCClass.h"
#include "peripherial/clockClass.h"
#include "peripherial/GPIO.h"
#include "peripherial/pwmClass.h"
#include "peripherial/timer.h"
#include "motor/motor.h"
#include "motor/motorDrive.h"



#define PWM_SERVO PIO_PSR_P0
#define PWM_LED PIO_PSR_P14

/**
 * Timer TCO interrupt handler.
 * Toogle LED output pin
 */

volatile bool oldKeyValue = true;
volatile double adcMeasureValue = 0;
//volatile bool pwmUpdateFlag = false;

PWMClass pwm_1;
ADCClass adc_1;
GPIOClass gpio_1;
MotorDrive motorDrive;

void TC0_Handler() {
	

	/* ************************************************************************** */
	/*   This code ON/OFF LED when we press key. Timer 10ms for contact vibration */
	/* ************************************************************************** */
	volatile unsigned long status = TC0->TC_CHANNEL[0].TC_SR;	
	if(!(PIOA->PIO_PDSR & (1 << 15)) && oldKeyValue) {
		//	PIOA->PIO_ODSR ^= ~(PIOA->PIO_ODSR & 1 << 25);
		oldKeyValue= false;
		if(PIOA->PIO_ODSR & (1 << 25)) {
			PIOA->PIO_CODR = 1 << 25;
		}
		else {
			PIOA->PIO_SODR = 1 << 25;
		}
	}
	else if(PIOA->PIO_PDSR & (1 << 15)) {
		oldKeyValue = true;
	}
	
	// blue LED
// 	if(PIOA->PIO_ODSR & (1 << 23)) {
// 		PIOA->PIO_CODR = 1 << 23;
// 	}
// 	else {
// 		PIOA->PIO_SODR = 1 << 23;
// 	}
	
//PWM update
// 	PWM->PWM_CH_NUM[0].PWM_CMR = PWM->PWM_CH_NUM[0].PWM_CMR & ~PWM_CMR_CPD;
// 	PWM->PWM_CH_NUM[0].PWM_CUPD = 3375;
	//PIOA->PIO_SODR = 1 << 25;
//	if((TC0->TC_IMR_CPCS) & !(PIOA->PIO_PDSR & (PIO_PDR_P15))) {
//		PIOA->PIO_SODR = 1 << 25;
//	}
	
}

void PIOA_Handler() {
	PIOA->PIO_SODR = 1 << 25;
	gpio_1.clearInterruptStatus(PIOA);
}

void ADC_Handler() {
	
	adcMeasureValue = ADC->ADC_LCDR;
	adcMeasureValue = ADC->ADC_CDR[0];
	
	int adcValueCH1 = ADC->ADC_CDR[1];
	int adcValueCH2 = ADC->ADC_CDR[2];
	motorDrive.getADCValue(adcValueCH1, adcValueCH2);
	
	//update PWM for servoS
	pwm_1.pwmServoUpdateDuty(adcMeasureValue, 0);
	//start new measure
	adc_1.beginConversion();
}

// void timerInit(void) {
// 	//PMC TC set
// 	PMC->PMC_PCER0 = PMC_PCER0_PID23;
// 	//enable clock
// 	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN;
// 	//prescaler 128
// 	TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_TCCLKS_TIMER_CLOCK4;
// 	
// 	//set TC to 10ms
// 	TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_WAVSEL_UP_RC;
// 	
// 	TC0->TC_CHANNEL[0].TC_RC = 3750;
// 	//interrupt on RC compare
// 	TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;
// 	volatile unsigned long status = TC0->TC_CHANNEL[0].TC_SR;
// 	TC0->TC_CHANNEL[0].TC_CCR |= TC_CCR_SWTRG;
// 	NVIC_EnableIRQ(TC0_IRQn);
// }
// 
// void GPIOInit() {
// 	//PMC PIOA set
// 	PMC->PMC_PCER0 = PMC_PCER0_PID11;
// 	//enable PIOB in PMC for LED (PWM)
// 	PMC->PMC_PCER0 = PMC_PCER0_PID12;
// 	
// 	//PA25 LED 3
// 	PIOA->PIO_OER = 1 << 25;
// 	PIOA->PIO_CODR = 1 << 25;
// 	
// 	//PA 23 LED 1
// 	PIOA->PIO_OER = 1 << 23;
// 	PIOA->PIO_CODR = 1<< 23;
// 	
// 	PIOA->PIO_ODR = 1 << 15;
// 	// pull up on pin 15
// 	PIOA->PIO_PUER = 1 << 15;
// 	
// 	PIOA->PIO_OWER = 1 << 25;
// 	
// // 	configure external interrupt on pin 14
// // 		// pull up on pin 14
// // 		//interrupt enable for pin 14
// // 		PIOA->PIO_PUER = PIO_PUER_P14;
// // 		volatile int status = PIOA->PIO_ISR;
// // 		PIOA->PIO_IER = PIO_IER_P14;
// // 		//interrupt source is an Edge detection event
// // 		PIOA->PIO_ESR = PIO_ESR_P14;
// // 		//interrupt on falling edge
// // 		PIOA->PIO_FELLSR = PIO_FELLSR_P14;
// // 		NVIC_EnableIRQ(PIOA_IRQn);
// }


int main(void)
{
	
	
    /* Initialize the SAM system */
    //SystemInit();
	
	ClockClass clock_1;
	clock_1.switchToXtal();
	
	
	
	gpio_1.outputEnable(PIOA, PIO_OER_P25);
	gpio_1.outputEnable(PIOA, PIO_OER_P23);
	gpio_1.inputEnable(PIOA, PIO_ODR_P15, ON);
	gpio_1.enableExtrInterrupt(PIOA, PIO_ODR_P16, FALLING);
	
	//timer init
	Timer timer_1;
	timer_1.setChannel(TC0, 0, clock4, 3750);
	
	
// 	pwm_1.pwmAddChannel(A, PWM_SERVO, PIOB, 0, prescaler64, 3750, 3562);
// 	pwm_1.pwmAddChannel(B, PWM_LED, PIOB, 3, prescaler128, 9375, 4687);
	
	
	adc_1.adcSetChannel(0x8, 0x4, 0);
	adc_1.beginConversion();
	
// 		configure external interrupt on pin 16
//  		 		// pull up on pin 16
//  		 		//interrupt enable for pin 16
//  		 		PIOA->PIO_PUER = PIO_PUER_P16;
//  		 		volatile int status = PIOA->PIO_ISR;
//  		 		PIOA->PIO_IER = PIO_IER_P16;
//  		 		//interrupt source is an Edge detection event
//  		 		PIOA->PIO_ESR = PIO_ESR_P16;
//  		 		//interrupt on falling edge
//  		 		PIOA->PIO_FELLSR = PIO_FELLSR_P16;
//  		 		NVIC_EnableIRQ(PIOA_IRQn);
	
    /* Replace with your application code */
    while (1) 
    {
		//pwmServoUpdateDuty(adcMeasureValue);
    }
}
