/*
 * Timer.h
 *
 *  Created on: 4 Mar 2015
 *      Author: Rellik
 *      Comment: This class cannot be called TimerClass, otherwise there is a problem in liniking symbols.   --Tai  3rd/Mar/2014
 */

#ifndef GPTIMERCLASS_H_
#define GPTIMERCLASS_H_

#define PART_TM4C123AH6PM //Needed to make pin_map include properly, isnt used in examples
// stdint has to be defined before other drivers.
#include <stdint.h>

#include <stdbool.h>
#include <stdio.h>
#include <iostream>

#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"

//for testing
#include <src/shared/LED/LED.h>

// This ControlClass has to be decleared (just a prototype) otherwise its pointer cannot be decleared.
// The acutal ControlClass is defined later in the .cpp file.
// This is to resolve the recursive including between "GPTimer.h" and "Control.h".
// So the pointer class would not be wrong before it is assigned.    ---Tai  13/03/15
class ControlClass;

class GPTimerClass
{
public:
	GPTimerClass(ControlClass* controlPtr);
	virtual ~GPTimerClass();

	float getDt();
	void setDt(float dt_set);
	void start();
	void stop();
	void ISR();


private:
	// Register abstractors and accessors
	uint32_t SYSCTL_PERIPH_TIMER;
	uint32_t TIMER_BASE;
	uint32_t INT_TIMERnA_TM4C123;
	uint32_t TIMER;
//	static	GPTimerClass* Timer;

	void calcdt();
	static void ISRStatic();

	float    dt;
	bool 	 timerOn;
	ControlClass* control;
	LEDClass LED0;

};


#endif /* TIMER_H_ */
