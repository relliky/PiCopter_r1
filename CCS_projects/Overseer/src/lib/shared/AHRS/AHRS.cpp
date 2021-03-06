/*
 * File:   AHRS.cpp
 * Author: matt
 *
 * Created on 29 October 2012, 22:38
 */

#include "AHRS.h"



AHRSClass::AHRSClass(OptimusPiInterfaceClass* OptimusPiPtr)
{
	OptimusPi = OptimusPiPtr;

	accCalibData.xb = 0.0045f;
	accCalibData.yb = -0.0041;
	accCalibData.zb = -0.0479;
	accCalibData.coef00 = 0.9904f;
	accCalibData.coef01 = 0.0005f;
	accCalibData.coef02 = -0.0015f;
	accCalibData.coef11 = 0.9964f;
	accCalibData.coef12 = 0.0016f;
	accCalibData.coef22 = 0.9997;	
}

AHRSClass::~AHRSClass()
{
}

void AHRSClass::update(float dt)
{
	getSensors();
	MerayoCalibClass::apply(&scaledSensorData.x, &scaledSensorData.y, &scaledSensorData.z, &accCalibData);
	fuse(dt);
	transformOrientation();

}

void AHRSClass::getSensors()
{
	if (OptimusPi->MPU.getScaledSensorData(&scaledSensorData) < 0)
	{
		std::cerr << "Failed to getScaledSensorData in AHRSClass::getSensors()" << std::endl;
	}
}

void AHRSClass::fuse(float dt)
{
	if (dt < 0.03) // Don't bother predicting over long dt, will be too inaccurate
	{
		EKF.predict(-scaledSensorData.p, -scaledSensorData.q, scaledSensorData.r, dt, &quaternion);
	}
	EKF.update(scaledSensorData.x, scaledSensorData.y, -scaledSensorData.z, dt, &quaternion);

	quaternionToYPR(&quaternion, &orientation);
}

/**
 * Function to transform the resulting EKF orientation into one that represents the vehicle the board is contained within.
 */
void AHRSClass::transformOrientation()
{
	float pitchTemp = orientation.pitch;
	float rollTemp = orientation.roll;
	float yawTemp = orientation.yaw;
	
	orientation.pitch = rollTemp;
	orientation.roll = -pitchTemp;
	orientation.yaw = yawTemp;
	
}

QuaternionClass AHRSClass::getQuaternion()
{
	return quaternion;
}

float AHRSClass::getPitch()
{
	return orientation.pitch;
}

float AHRSClass::getRoll()
{
	return orientation.roll;
}

float AHRSClass::getYaw()
{
	return orientation.yaw;
}

float AHRSClass::getX()
{
	return scaledSensorData.x;
}

float AHRSClass::getY()
{
	return scaledSensorData.y;
}

float AHRSClass::getZ()
{
	return scaledSensorData.z;
}

// Returns p relative to vehicle body
float AHRSClass::getP()
{
	return -scaledSensorData.q;
}

// Returns q relative to vehicle body 
float AHRSClass::getQ()
{
	return -scaledSensorData.p;
}

// Returns q relative to vehicle body 
float AHRSClass::getR()
{
	return -scaledSensorData.r;
}

float AHRSClass::getMagX()
{
	return 0.0f;
}

float AHRSClass::getMagY()
{
	return 0.0f;
}

float AHRSClass::getMagZ()
{
	return 0.0f;
}

float AHRSClass::getTemp()
{
	return scaledSensorData.temp;
}

void AHRSClass::quaternionToYPR(QuaternionClass* q, euler_s* orientation)
{

	#ifdef DEBUG_AHRS

	std::cout << "quaternion.w is " << q->w << std::endl;
	std::cout << "quaternion.x is " << q->x << std::endl;
	std::cout << "quaternion.y is " << q->y << std::endl;
	std::cout << "quaternion.z is " << q->z << std::endl;


	std::cout << std::endl << "This is running AHRSClass::quaternionToYPR, involing <math.h> and atan2(), and pow() IN DOUBLE TYPE" << std::endl;

	double test1 = (0.953422 * 0.301277 + 0.0147571*0);
	std::cout << "double test1 result is derived from manipulation of 4 constants. Results should be 0.287244 and actual result is " << test1 << std::endl;

	float q1 = 0.953422;
	float q2 = 0.301277;
	float q3 = 0.0147571;
	float q4 = 0;

	double test2 = (q1 * q2 + q3 * q4);
	std::cout << "double test2 result is derived from manipulation of 4 floats. Results should be 0.287244 and actual result is " << test2 << std::endl;

	double qd1 = 0.953422;
	double qd2 = 0.301277;
	double qd3 = 0.0147571;
	double qd4 = 0;

	double test3 = (qd1 * qd2 + qd3 * qd4);
	std::cout << "double test3 result is derived from manipulation of 4 doubles. Results should be 0.287244 and actual result is " << test3 << std::endl;


	double v1 = ((q->w) * (q->x) + (q->y) * (q->z));
	double v2 = (pow(q->x, 2) + pow(q->y, 2));
	double v3 = (q->w * q->y - q->z * q->x);
	double v4 = (q->w * q->z + q->x * q->y);
	double v5 = (pow(q->y, 2) + pow(q->z, 2));

	double v6 = atan2(2 * v1, 1 - 2 * v2);
	double v7 = asin(2 * v3);
	double v8 = atan2(2 * v4, 1 - 2 * v5);

	double v9 = -(180 / pi) * v6;
	double v10 = (180 / pi) * v7;
	double v11 = (180 / pi) * v8;

	std::cout << "v1 is " << v1 << std::endl;
	std::cout << "v2 is " << v2 << std::endl;
	std::cout << "v3 is " << v3 << std::endl;
	std::cout << "v4 is " << v4 << std::endl;
	std::cout << "v5 is " << v5 << std::endl;
	std::cout << "v6 is " << v6 << std::endl;
	std::cout << "v7 is " << v7 << std::endl;
	std::cout << "v8 is " << v8 << std::endl;
	std::cout << "v9 is " << v9 << std::endl;
	std::cout << "v10 is " << v10 << std::endl;
	std::cout << "v11 is " << v11 << std::endl;


	std::cout << std::endl << "This is running AHRSClass::quaternionToYPR, involing <math.h> and atan2(), and pow() IN FLOAT TYPE" << std::endl;

	float test4 = (0.953422 * 0.301277 + 0.0147571*0);
	std::cout << "float test4 result is derived from manipulation of 4 constants. Results should be 0.287244 and actual result is " << test4 << std::endl;

	float qf1 = 0.953422;
	float qf2 = 0.301277;
	float qf3 = 0.0147571;
	float qf4 = 0;

	float test5 = (qf1 * qf2 + qf3 * qf4);
	std::cout << "double test5 result is derived from manipulation of 4 floats. Results should be 0.287244 and actual result is " << test5 << std::endl;


	float vf1 = ((q->w) * (q->x) + (q->y) * (q->z));
	float vf2 = (pow(q->x, 2) + pow(q->y, 2));
	float vf3 = (q->w * q->y - q->z * q->x);
	float vf4 = (q->w * q->z + q->x * q->y);
	float vf5 = (pow(q->y, 2) + pow(q->z, 2));

	float vf6 = atan2(2 * vf1, 1 - 2 * vf2);
	float vf7 = asin(2 * vf3);
	float vf8 = atan2(2 * vf4, 1 - 2 * vf5);

	float vf9 = -(180 / pi) * vf6;
	float vf10 = (180 / pi) * vf7;
	float vf11 = (180 / pi) * vf8;

	std::cout << "vf1 is " << vf1 << std::endl;
	std::cout << "vf2 is " << vf2 << std::endl;
	std::cout << "vf3 is " << vf3 << std::endl;
	std::cout << "vf4 is " << vf4 << std::endl;
	std::cout << "vf5 is " << vf5 << std::endl;
	std::cout << "vf6 is " << vf6 << std::endl;
	std::cout << "vf7 is " << vf7 << std::endl;
	std::cout << "vf8 is " << vf8 << std::endl;
	std::cout << "vf9 is " << vf9 << std::endl;
	std::cout << "vf10 is " << vf10 << std::endl;
	std::cout << "vf11 is " << vf11 << std::endl;


	#endif


	orientation->pitch = -(180 / pi) * atan2(2 * (q->w * q->x + q->y * q->z), 1 - 2 * (pow(q->x, 2) + pow(q->y, 2)));
	orientation->roll = (180 / pi) * asin(2 * (q->w * q->y - q->z * q->x));
	orientation->yaw = (180 / pi) * atan2(2 * (q->w * q->z + q->x * q->y), 1 - 2 * (pow(q->y, 2) + pow(q->z, 2)));
}

