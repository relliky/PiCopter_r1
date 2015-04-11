/*
 * main.h
 *
 *  Created on: 18 Jul 2014
 *      Author: admin
 */

#ifndef OVERSEER_H_
#define OVERSEER_H_



#include <stdbool.h>
#include <stdint.h>
// for debug usage
#include <stdio.h>
#include <iostream>



#define DEBUG
// Enable debug printf and run tests based on "scr/Debug/DebugOptions.h"
#ifdef DEBUG
#include <src/shared/DebugFunction/DebugFunction.h>
#endif


#include "driverlib/sysctl.h"
#include <src/TopLevel/Arbitrator/ArbitratorClass.h>
#include <src/TopLevel/GlobalVariablesDefinition/GlobalVariablesDefinition.h>


// The following headers just for debug usage

//#include <src/TopLevel/PiSlavedCopter/PiSlavedCopter.h>

#include <src/shared/OverseerOptimusPiInterface/OptimusPiInterface.h>

//#include <src/shared/OverseerOptimusPiInterface/OverseerPeripheralInterfaces/PinController.h>
//#include <cstddef>
//#include <src/TopLevel/StandaloneCopter/StandaloneCopter.h>
#include <src/TopLevel/RPiControlledCopter/RPiControlledCopter.h>

#include <src/TopLevel/StandaloneCopter/OptimusPiCopter/AHRS/AHRS.h>

//#include <src/TopLevel/StandaloneCopter/OptimusPiCopter/AHRS/test/EigenTest.h>



//#include <src/TopLevel/StandaloneCopter/OptimusPiCopter/Control/Control.h>

// LED for testing timers
//#include <src/shared/LED/LED.h>
//#include <src/OptimusPiCopter/GPTimer/GPTimer.h>
//#include <src/TopLevel/IsolatedCopter/OverseerOptimusPiInterface/OptimusPiInterface.h>
//#include <src/TopLevel/IsolatedCopter/OptimusPiCopter/RX/RXInterface.h>


/*
#include "shared/SPI/SPISlave/SPISlave.h"
#include "shared/SPI/SPICommands/SPICommands.h"
#include "OverseerOptimusPiInterface/OptimusPiInterface.h"
#include "shared/I2C/I2C.h"
*/




#endif /* OVERSEER_H_ */
