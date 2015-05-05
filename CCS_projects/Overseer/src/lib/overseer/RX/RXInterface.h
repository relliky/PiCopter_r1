/*
 * RXInterface.h
 *
 *  Created on: 19 Aug 2014
 *      Author: matt
 */

#ifndef RXINTERFACE_H_
#define RXINTERFACE_H_

#include <src/lib/overseer/OverseerOptimusPiInterface/OptimusPiInterface.h>

//debug usage only
//#define DEBUG_RX
#ifdef DEBUG_RX
	#include <stdbool.h>
	#include <stdint.h>
	#include <stdio.h>
	#include <iostream>
#endif


class RXInterfaceClass
{
public:
	RXInterfaceClass(OptimusPiInterfaceClass* OptimusPiPtr);
	virtual ~RXInterfaceClass();
	
	void update();
	float getPitch();
	float getRoll();
	float getThrottle();
	float getYaw();
	bool getSw1();
	bool getSw2();

private:
	void constrain(float* value, float range);
	
	OptimusPiInterfaceClass* OptimusPi;

	struct
	{
		uint32_t roll, pitch, throttle, yaw, sw1, sw2;
	} rawReceiverData;

	struct
	{
		float roll, pitch, throttle, yaw;
		bool sw1, sw2;
	} receiverData;
};

#endif /* RXINTERFACE_H_ */