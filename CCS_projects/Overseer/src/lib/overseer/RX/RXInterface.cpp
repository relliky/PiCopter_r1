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
	// HobbyKing 2.4 Ghz RX chanel 1
	rawReceiverData.roll = OptimusPi->IC5.getInputCaptureWidth();
	// HobbyKing 2.4 Ghz RX chanel 2
	rawReceiverData.pitch = OptimusPi->IC4.getInputCaptureWidth();
	// HobbyKing 2.4 Ghz RX chanel 3
	rawReceiverData.throttle = OptimusPi->IC3.getInputCaptureWidth();
	// HobbyKing 2.4 Ghz RX chanel 4
	rawReceiverData.yaw = OptimusPi->IC2.getInputCaptureWidth();
	// HobbyKing 2.4 Ghz RX chanel 5
	rawReceiverData.sw1 = OptimusPi->IC1.getInputCaptureWidth();
	// HobbyKing 2.4 Ghz RX chanel 6
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

	#ifdef DEBUG_RX
	std::cout << "receiverData.roll is " << receiverData.roll << std::endl;
	std::cout << "receiverData.pitch is " << receiverData.pitch << std::endl;
	std::cout << "receiverData.throttle is " << receiverData.throttle << std::endl;
	std::cout << "receiverData.yaw is " << receiverData.yaw << std::endl;
	std::cout << "receiverData.sw1 is " << receiverData.sw1 << std::endl;
	std::cout << "receiverData.sw2 is " << receiverData.sw2 << std::endl;
	#endif

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
