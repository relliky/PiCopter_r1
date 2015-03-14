/*
 * RPiControlledCopter.h
 *
 *  Created on: 13 Mar 2015
 *      Author: Rellik
 */

#ifndef RPICONTROLLEDCOPTER_H_
#define RPICONTROLLEDCOPTER_H_

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/sysctl.h"

#include <src/shared/SPI/SPISlave/SPISlave.h>
#include <src/shared/SPI/SPICommands/SPICommands.h>
#include <src/TopLevel/StandaloneCopter/OverseerOptimusPiInterface/OverseerPeripheralInterfaces/MotorController.h>
#include <src/TopLevel/StandaloneCopter/OverseerOptimusPiInterface/OverseerPeripheralInterfaces/PinController.h>

class RPiControlledCopterClass
{
public:
	RPiControlledCopterClass();
	virtual ~RPiControlledCopterClass();

	void updateReadBuffers();
	void emptyMessageQueue();

private:
	SPISlaveClass RPiSPISlave;
	MotorControllerClass motor0, motor1, motor2, motor3;
	PinControllerClass IC0, IC1, IC2, IC3, IC4, IC5, IC6, IC7, AN0, AN1, AN2, AN3, AN4, AN5;
};



#endif /* RPICONTROLLEDCOPTER_H_ */
