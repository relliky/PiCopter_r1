/*
 * StandaloneCopter.h
 *
 *  Created on: 14 Mar 2015
 *      Author: Rellik
 */

#ifndef STANDALONECOPTER_H_
#define STANDALONECOPTER_H_

#include <src/shared/SPI/SPISlave/SPISlave.h>
#include <src/shared/SPI/SPICommands/SPICommands.h>
#include "OptimusPiCopter/Control/Control.h"


class StandaloneCopterClass
{
public:
	StandaloneCopterClass();
	virtual ~StandaloneCopterClass();

	void checkModeStatus();
	void setRPiControlledCopterMode();
	bool isSwitchedToRPiControlledCopterMode();
	void clearRPiControlledCopterMode();
	void running();
	void setDt(float dt_set);

private:
	SPISlaveClass   RPiSPISlave;
	ControlClass    Control;
	bool            SwitchToRPiControlledCopterMode;
};

#endif /* STANDALONECOPTER_H_ */
