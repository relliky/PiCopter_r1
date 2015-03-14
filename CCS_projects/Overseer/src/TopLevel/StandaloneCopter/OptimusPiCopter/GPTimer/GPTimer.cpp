/*
 * TimerFunction.cpp
 *
 *  Created on: 4 Mar 2015
 *      Author: Tai
 *      Comment: This class has a problem in liniking symbols.   --Tai  3rd/Mar/2014
 *      Solution: Declear the the timerclass pointer as static in cpp file rather than in headfile.
 */

#include "GPTimer.h"
// This ControlClass has to be decleared otherwise its pointer cannot be decleared.
// This is to resolve the recursive including between "GPTimer.h" and "Control.h".
// The acutal ControlClass is redefined later in the .cpp file.
// So the pointer class would not be wrong before it is assigned.    ---Tai  13/03/15
#include "../Control/Control.h"

// Static pointer used for calling ISR in timer interrupt
#include "GPTimerGlobalVariables.h"

GPTimerClass::GPTimerClass(ControlClass* controlPtr)
:LED0(0)
{
	//Default dt = 0.1s
	dt = 0.1;
	timerOn = false;
//	control = controlPtr;

	//Use Full-width 32bit Timer2 as GPTimer in this class.
	Timer = this;
	SYSCTL_PERIPH_TIMER = SYSCTL_PERIPH_TIMER2;
	TIMER_BASE = TIMER2_BASE;
	TIMER = TIMER_A;
	INT_TIMERnA_TM4C123 = INT_TIMER0A_TM4C123;

	// Enable the timer peripheral
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER);
}

GPTimerClass::~GPTimerClass()
{
	// TODO Auto-generated destructor stub
	Timer->stop();
}


void GPTimerClass::start()
{
	// Clear the interrupt source now it is disabled and have no source to trigger it.
	TimerIntClear(TIMER_BASE, TIMER_TIMA_TIMEOUT);

	// Ensure the timer is disabled
	TimerDisable(TIMER_BASE, TIMER);
	// Configure the timer as a periodic up counter 32bit
	TimerConfigure(TIMER_BASE, TIMER_CFG_PERIODIC_UP);
	// Ensure the timer interrupt is disabled
	TimerIntDisable(TIMER_BASE, TIMER_TIMA_TIMEOUT);
	// Clear the interrupt source now it is disabled and have no source to trigger it.
	TimerIntClear(TIMER_BASE, TIMER_TIMA_TIMEOUT);
	// Register one of the two static interrupt handlers to the peripheral
	TimerIntRegister(TIMER_BASE, TIMER, ISRStatic);
	//For some reason, once TimerIntRegister is called, the ISR is immediately triggered when JTAG emulator in connected. But it is not desired. Hence using a flag timerOn to jump this excuation of ISR.

	// Set the interrupt priority
	IntPrioritySet(INT_TIMERnA_TM4C123, 0); // @TODO - What should this actually be?

	// The timer interrupt is initially set to be called at 10Hz. Therefore, dt is 0.1.
	// By experiement, 25s in the real life is 30s in the target board as set-up.Therefore, it needs to multiply a factor 30/25=6/5 to tune the timer to count the accurate time.
	float 	 dtFrequency    = 1/dt;
	float 	 clockFrequency = (float)SysCtlClockGet();
	uint32_t loadval        = (float)(clockFrequency/dtFrequency*6/5);
	//Counting from 0 up to the loaded value. Trigger interrupt when the value reaching this value.
	TimerLoadSet(TIMER_BASE, TIMER, loadval);
	//Slow down the clock of the timer by dividing the master clock frequency by 0xFF.
	//TimerPrescaleSet(TIMER_BASE, TIMER, 0xFFFF);

	//Set up timer as a interrupt souce
	TimerIntEnable(TIMER_BASE, TIMER_TIMA_TIMEOUT);
	// Clear the interrupt source now it is disabled and have no source to trigger it.
	TimerIntClear(TIMER_BASE, TIMER_TIMA_TIMEOUT);
	//Enable the timer hardware module. The timer hardware starts to work now.
	TimerEnable(TIMER_BASE, TIMER);

	timerOn = true;
	LED0.set();
}

void GPTimerClass::stop()
{
	//Disable Interrupt source, timer module and clear the interrupt flag as well.
	TimerIntDisable(TIMER_BASE, TIMER_TIMA_TIMEOUT);
	TimerDisable(TIMER_BASE, TIMER);
	TimerIntClear(TIMER_BASE, TIMER_TIMA_TIMEOUT);

}


interrupt void GPTimerClass::ISRStatic()
{
	Timer->ISR();
}

void GPTimerClass::ISR()
{
	//It's ISR's responsiblity to clear the interrupt flag, and otherwise the ISR is just being called all the time since the interrupt flag is not cleared and is always triggered.
	TimerIntClear(TIMER_BASE, TIMER_TIMA_TIMEOUT);
	//For some reason, once TimerIntRegister is called, the ISR is immediately triggered when JTAG emulator in connected. But it is not desired. Hence using a flag timerOn to jump this excuation of ISR.
	if (timerOn == false) return ;

	// Callback to control parent
//	control->update(dt);
//	static int a = 0;
//	a+= dt;

//	static int i1 = 2;
//	if(i1%2 == 0){LED0.clear();}else {LED0.set();}
	LED0.toggle();
//	i1++;
//	printf("This is %d sec.\n",a);

}

float GPTimerClass::getDt()
{
	return dt;
}

// dt cannot be greater than 53.68s, otherwise loadval would overflow.
void GPTimerClass::setDt(float dt_set)
{
	dt = dt_set;
	// The timer interrupt is initially set to be called at 10Hz. Therefore, dt is 0.1.
	// By experiement, 25s in the real life is 30s in the target board as set-up.Therefore, it needs to multiply a factor 30/25=6/5 to tune the timer to count the accurate time.
	uint32_t dtFreqency = (uint32_t)(1/dt);
	uint32_t loadval = SysCtlClockGet()/dtFreqency*6/5;
	//Counting from 0 up to the loaded value. Trigger interrupt when the value reaching this value.
	TimerLoadSet(TIMER_BASE, TIMER, loadval);
}


