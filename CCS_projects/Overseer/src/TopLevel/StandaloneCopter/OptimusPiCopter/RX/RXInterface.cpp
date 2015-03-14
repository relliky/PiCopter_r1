/*
 * RXInterface.cpp
 *
 *  Created on: 19 Aug 2014
 *      Author: matt
 */

#include "RXInterface.h"

#define RX_MAX 160000
#define RX_MIN 80000
#define RX_MID ((RX_MAX + RX_MIN) / 2)


RXInterfaceClass::RXInterfaceClass(OptimusPiInterfaceClass* OptimusPiPtr)
{
	OptimusPi = OptimusPiPtr;
	OptimusPi->IC0.config(InputCaptureType);
	OptimusPi->IC1.config(InputCaptureType);
	OptimusPi->IC2.config(InputCaptureType);
	OptimusPi->IC3.config(InputCaptureType);
	OptimusPi->IC4.config(InputCaptureType);
	OptimusPi->IC5.config(InputCaptureType);
}

RXInterfaceClass::~RXInterfaceClass()
{
	// TODO Auto-generated destructor stub
}

void RXInterfaceClass::update()
{
	rawReceiverData.roll = OptimusPi->IC5.getInputCaptureWidth();
	rawReceiverData.pitch = OptimusPi->IC4.getInputCaptureWidth();
	rawReceiverData.throttle = OptimusPi->IC3.getInputCaptureWidth();
	rawReceiverData.yaw = OptimusPi->IC2.getInputCaptureWidth();
	rawReceiverData.sw1 = OptimusPi->IC1.getInputCaptureWidth();
	rawReceiverData.sw2 = OptimusPi->IC0.getInputCaptureWidth();
	
	receiverData.roll = (float)((int32_t)rawReceiverData.roll - RX_MID) / (float)(RX_MID - RX_MIN);
	receiverData.pitch = (float)((int32_t)rawReceiverData.pitch - RX_MID) / (float)(RX_MID - RX_MIN);
	receiverData.throttle = (float)((int32_t)rawReceiverData.throttle - RX_MIN) / (float)(RX_MAX - RX_MIN);
	receiverData.yaw = (float)((int32_t)rawReceiverData.yaw - RX_MID) / (float)(RX_MID - RX_MIN);
	receiverData.sw1 = rawReceiverData.sw1 > RX_MID;
	receiverData.sw2 = rawReceiverData.sw2 > RX_MID;
	
	constrain(&receiverData.roll, 1.0f);
	constrain(&receiverData.pitch, 1.0f);
	constrain(&receiverData.throttle, 1.0f);
	constrain(&receiverData.yaw, 1.0f);
}

float RXInterfaceClass::getPitch()
{
	return receiverData.pitch;
}

float RXInterfaceClass::getRoll()
{
	return receiverData.roll;
}

float RXInterfaceClass::getThrottle()
{
	return receiverData.throttle;
}

float RXInterfaceClass::getYaw()
{
	return receiverData.yaw;
}

bool RXInterfaceClass::getSw1()
{
	return receiverData.sw1;
}

bool RXInterfaceClass::getSw2()
{
	return receiverData.sw2;
}

inline void RXInterfaceClass::constrain(float* value, float range)
{
	if (*value > range)
		*value = range;
	else if (*value < -range)
		*value = -range;
}
