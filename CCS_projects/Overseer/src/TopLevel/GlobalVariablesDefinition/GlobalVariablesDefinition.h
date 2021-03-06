/*
 * GlobalVariablesDefinition.h
 *
 *  Created on: 13 Mar 2015
 *      Author: Tai
 */

#ifndef GLOBALVARIABLESDEFINITION_H_
#define GLOBALVARIABLESDEFINITION_H_


// Static objects used for two SPIs to two motor controllers
// in <src/TopLevel/StandaloneCopter/OverseerOptimusPiInterface/OverseerPeripheralInterfaces/MotorController.cpp>

SPIMasterClass OverseerSPIMaster1(1);
SPIMasterClass OverseerSPIMaster2(2);

// Static pointer used for calling ISR in timer interrupt
// in <src/TopLevel/StandaloneCopter/OptimusPiCopter/GPTimer.cpp>

GPTimerClass* Timer;

// Static pointer used for calling ISR in SPISlave interrupt
// in <src/shared/SPI/SPISlave/SPISlave.cpp>

SPISlaveClass* SPISlave0;

// Static pointers used for calling ISR in InputCaptureClass time-out and event capture interrupts
// in <src/TopLevel/StandaloneCopter/OverseerOptimusPiInterface/OverseerPeripheralInterfaces/PinControllers/InputCapture.cpp>

InputCaptureClass* IC0;
InputCaptureClass* IC1;
InputCaptureClass* IC2;
InputCaptureClass* IC3;
InputCaptureClass* IC4;
InputCaptureClass* IC5;
InputCaptureClass* IC6;
InputCaptureClass* IC7;


#endif /* GLOBALVARIABLESDEFINITION_H_ */


