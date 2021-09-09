/*
 * GPIO.h
 *
 * Created: 11.02.2021 16:52:00
 *  Author: Piotrek
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include "board.h"

#define u_char unsigned char

enum Pullup {
	ON,
	OFF,
};

enum LEVEL_EDGE {
	LOW,
	HIGH,
	FALLING,
	RISING,	
};

class GPIOClass
{
public:
	GPIOClass						();
	void outputEnable				(Pio * PORT_, long int portPin);
	void inputEnable				(Pio * PORT_, long int portPin, Pullup pullup);
	void setPin						(Pio * PORT_, long int portPin);
	void clearPin					(Pio * PORT_, long int portPin);
	void enableExtrInterrupt		(Pio * PORT_, long int portPin, LEVEL_EDGE levelEdge);
	void clearInterruptStatus		(Pio * PORT_);
protected:
private:
};


#endif /* GPIO_H_ */