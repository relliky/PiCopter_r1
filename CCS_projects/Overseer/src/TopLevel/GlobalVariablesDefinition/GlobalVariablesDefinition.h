/*
 * GlobalVariablesDefinition.h
 *
 *  Created on: 13 Mar 2015
 *      Author: Rellik
 */

#ifndef GLOBALVARIABLESDEFINITION_H_
#define GLOBALVARIABLESDEFINITION_H_


// Static pointers used for two SPIs to two motor controllers in
// <src/TopLevel/StandaloneCopter/OverseerOptimusPiInterface/OverseerPeripheralInterfaces/MotorController.cpp>
 SPIMasterClass OverseerSPIMaster1(1);
 SPIMasterClass OverseerSPIMaster2(2);


// Static pointer used for calling ISR in timer interrupt
// in <src/TopLevel/StandaloneCopter/OptimusPiCopter/GPTimer.cpp>
// This ControlClass has to be decleared otherwise its pointer cannot be decleared.
// This is to resolve the recursive including between "GPTimer.h" and "Control.h".
// The acutal ControlClass is redefined later in the .cpp file.
// So the pointer class would not be wrong before it is assigned.    ---Tai  13/03/15
 GPTimerClass* Timer;



#endif /* GLOBALVARIABLESDEFINITION_H_ */

 // IsolatedCopter
