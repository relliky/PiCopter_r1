/* 
 * File:   ExtendedKalman.cpp
 * Author: matt
 * 
 * Created on 14 March 2013, 17:26
 */

#include "ExtendedKalman.h"

ExtendedKalmanClass::ExtendedKalmanClass()
{
	Q = Q.Zero();
	x = x.Zero();
	F = F.Zero();
	P = P.Zero();
	z = z.Zero();
	h = h.Zero();
	y = y.Zero();
	H = H.Zero();
	S = S.Zero();
	R = R.Zero();
	K = K.Zero();

	I = I.Identity();
	P = P.Identity();
	P *= 10000000;

	Q(0, 0) = 0;
	Q(1, 1) = 0;
	Q(2, 2) = 0;
	Q(3, 3) = 0;
	Q(4, 4) = 0.2;
	Q(5, 5) = 0.2;
	Q(6, 6) = 0.2;

	R(0, 0) = 1000000;
	R(1, 1) = 1000000;
	R(2, 2) = 1000000;

	x(0) = 1;
	x(1) = 0;
	x(2) = 0;
	x(3) = 0;
	x(4) = 0;
	x(5) = 0;
	x(6) = 0;

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "ExtendedKalmanClass constuctor initialisation" << std::endl;
	#endif

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix Q is " << std::endl << Q << std::endl;
	#endif

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix x is " << std::endl<< x << std::endl;
	#endif

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix F is " << std::endl<< F << std::endl;
	#endif

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix P is " << std::endl<< P << std::endl;
	#endif

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix z is " << std::endl<< z << std::endl;
	#endif

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix h is " << std::endl<< h << std::endl;
	#endif

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix y is " << std::endl<< y << std::endl;
	#endif

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix H is " << std::endl<< H << std::endl;
	#endif

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix S is " << std::endl<< S << std::endl;
	#endif

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix R is " << std::endl<< R << std::endl;
	#endif

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix K is " << std::endl<< K << std::endl;
	#endif

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix I is " << std::endl<< I << std::endl;
	#endif



}

ExtendedKalmanClass::~ExtendedKalmanClass()
{
}

void ExtendedKalmanClass::predict(float gyro_p, float gyro_q, float gyro_r, float dt, QuaternionClass *quaternion)
{
	float q0 = x(0);
	float q1 = x(1);
	float q2 = x(2);
	float q3 = x(3);
	float wxb = x(4);
	float wyb = x(5);
	float wzb = x(6);
	float wx = gyro_p * (pi / 180);
	float wy = gyro_q * (pi / 180);
	float wz = gyro_r * (pi / 180);

	//Half dt since dt is only ever used in this form, saves on evaluating dt/2 multiple times
	dt /= 2;

	//Predicted state estimate, x = f(x,u)
	x(0) = q0 + dt * (-q1 * (wx - wxb) - q2 * (wy - wyb) - q3 * (wz - wzb));
	x(1) = q1 + dt * (q0 * (wx - wxb) - q3 * (wy - wyb) + q2 * (wz - wzb));
	x(2) = q2 + dt * (q3 * (wx - wxb) + q0 * (wy - wyb) - q1 * (wz - wzb));
	x(3) = q3 + dt * (-q2 * (wx - wxb) + q1 * (wy - wyb) + q0 * (wz - wzb));
	//Gyro biases x(4:6) don't change

	//Normalise to unit quaternion
	float norm = sqrtf((float)(x(0) * x(0) + x(1) * x(1) + x(2) * x(2) + x(3) * x(3)));
	x(0) /= norm;
	x(1) /= norm;
	x(2) /= norm;
	x(3) /= norm;

	q0 = x(0);
	q1 = x(1);
	q2 = x(2);
	q3 = x(3);

	//Build jacobian of f(x,u), F(row,column)
	F(0, 0) = 1;
	F(0, 1) = -dt * (wx - wxb);
	F(0, 2) = -dt * (wy - wyb);
	F(0, 3) = -dt * (wz - wzb);
	F(0, 4) = dt * q1;
	F(0, 5) = dt * q2;
	F(0, 6) = dt * q3;
	F(1, 0) = dt * (wx - wxb);
	F(1, 1) = 1;
	F(1, 2) = dt * (wz - wzb);
	F(1, 3) = -dt * (wy - wyb);
	F(1, 4) = -dt * q0;
	F(1, 5) = dt * q3;
	F(1, 6) = -dt * q2;
	F(2, 0) = dt * (wy - wyb);
	F(2, 1) = -dt * (wz - wzb);
	F(2, 2) = 1;
	F(2, 3) = dt * (wx - wxb);
	F(2, 4) = -dt * q3;
	F(2, 5) = -dt * q0;
	F(2, 6) = dt * q1;
	F(3, 0) = dt * (wz - wzb);
	F(3, 1) = dt * (wy - wyb);
	F(3, 2) = -dt * (wx - wxb);
	F(3, 3) = 1;
	F(3, 4) = dt * q2;
	F(3, 5) = -dt * q1;
	F(3, 6) = -dt * q0;
	F(4, 0) = 0;
	F(4, 1) = 0;
	F(4, 2) = 0;
	F(4, 3) = 0;
	F(4, 4) = 1;
	F(4, 5) = 0;
	F(4, 6) = 0;
	F(5, 0) = 0;
	F(5, 1) = 0;
	F(5, 2) = 0;
	F(5, 3) = 0;
	F(5, 4) = 0;
	F(5, 5) = 1;
	F(5, 6) = 0;
	F(6, 0) = 0;
	F(6, 1) = 0;
	F(6, 2) = 0;
	F(6, 3) = 0;
	F(6, 4) = 0;
	F(6, 5) = 0;
	F(6, 6) = 1;

	//Covariance of estimate
	P = F * P * F.transpose() + Q;

	quaternion->w = x(0);
	quaternion->x = x(1);
	quaternion->y = x(2);
	quaternion->z = x(3);
}

void ExtendedKalmanClass::update(float acc_x, float acc_y, float acc_z, float dt, QuaternionClass *quaternion)
{

	float q0 = x(0);
	float q1 = x(1);
	float q2 = x(2);
	float q3 = x(3);

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "ExtendKalmanClass update test start in Overseer" << std::endl;
	#endif

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "q0 is " << q0 << std::endl;
		std::cout << "q1 is " << q1 << std::endl;
		std::cout << "q2 is " << q2 << std::endl;
		std::cout << "q3 is " << q3 << std::endl;
	#endif

	// std::cout << "Matrix x is " << std::endl<< x << std::endl;
    // introduces a run-time error which set processor into an interrupt fault handler
	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix x is " << std::endl << x(0) << std::endl << x(1) << std::endl << x(2) << std::endl << x(3) << std::endl;
	#endif

	//Normalise accelerometer triad
	{
		float norm = sqrtf(pow(acc_x, 2) + pow(acc_y, 2) + pow(acc_z, 2));

		#ifdef DEBUG_EXTENDEDKALMAN
			std::cout << "norm is " << norm << std::endl;
		#endif

		z(0) = acc_x / norm;
		z(1) = acc_y / norm;
		z(2) = acc_z / norm;

		#ifdef DEBUG_EXTENDEDKALMAN
			std::cout << "Matrix z is " << std::endl << z(0) << std::endl << z(1) << std::endl << z(2) << std::endl;
		#endif

	}

//	std::cout << "Matrix z is " << z << std::endl;

	//Map measurements to states
	h(0) = 2 * q0 * q2 - 2 * q1 * q3;
	h(1) = -2 * q0 * q1 - 2 * q2 * q3;
	h(2) = -q0 * q0 + q1 * q1 + q2 * q2 - q3 * q3;

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix h is " << std::endl << h(0) << std::endl << h(1) << std::endl << h(2) << std::endl;
	#endif

	//Measurement residual
	y = z - h;
	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix y is " << std::endl << y(0) << std::endl << y(1) << std::endl << y(2) << std::endl;
	#endif

	//Populate h jacobian
	H(0, 0) = 2 * q2;
	H(0, 1) = -2 * q3;
	H(0, 2) = 2 * q0;
	H(0, 3) = -2 * q1;
	H(0, 4) = 0;
	H(0, 5) = 0;
	H(0, 6) = 0;
	H(1, 0) = -2 * q1;
	H(1, 1) = -2 * q0;
	H(1, 2) = -2 * q3;
	H(1, 3) = -2 * q2;
	H(1, 4) = 0;
	H(1, 5) = 0;
	H(1, 6) = 0;
	H(2, 0) = -2 * q0;
	H(2, 1) = 2 * q1;
	H(2, 2) = 2 * q2;
	H(2, 3) = -2 * q3;
	H(2, 4) = 0;
	H(2, 5) = 0;
	H(2, 6) = 0;

//	std::cout << "Matrix H is " << H(litai,0)<<" "<< H(litai,1)<<" " << H(litai,2)<<" " << H(litai,3)<<" " << H(litai,4) <<" "<< H(litai,5)<<" " << H(litai,6) <<" " << std::endl;


	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix H is " << std::endl << H(0,0)<<" "<< H(0,1)<<" " << H(0,2)<<" " << H(0,3)<<" " << H(0,4) <<" "<< H(0,5)<<" " << H(0,6) <<" " << std::endl;
		std::cout << H(1,0)<<" "<< H(1,1)<<" " << H(1,2)<<" " << H(1,3)<<" " << H(1,4) <<" "<< H(1,5)<<" " << H(1,6) <<" " << std::endl;
		std::cout << H(2,1)<<" " << H(2,2)<<" " << H(2,3)<<" " << H(2,4) <<" "<< H(2,5)<<" " << H(2,6) <<" " << std::endl;
	#endif


	//Measurement covariance update + Kalman gain calculation + corrected prediction
	//S = H*P*H' + R
	S = H * P * H.transpose() + R; //H*P*H' is evaluating to 0 for some reason

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix S is " << std::endl << S(0,0)<<" "<< S(0,1)<<" " << S(0,2) << std::endl;
		std::cout << S(1,0)<<" "<< S(1,1)<<" " << S(1,2) << std::endl;
		std::cout << S(2,0)<<" "<< S(2,1)<<" " << S(2,2) << std::endl;
	#endif


	//K = P*H'/S
	K = P * H.transpose() * S.inverse();
	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix K is " << std::endl << K(0,0)<<" "<< K(0,1)<<" " << K(0,2) << std::endl;
		std::cout << K(1,0)<<" "<< K(1,1)<<" " << K(1,2) << std::endl;
		std::cout << K(2,0)<<" "<< K(2,1)<<" " << K(2,2) << std::endl;
		std::cout << K(3,0)<<" "<< K(3,1)<<" " << K(3,2) << std::endl;
		std::cout << K(4,0)<<" "<< K(4,1)<<" " << K(4,2) << std::endl;
		std::cout << K(5,0)<<" "<< K(5,1)<<" " << K(5,2) << std::endl;
		std::cout << K(6,0)<<" "<< K(6,1)<<" " << K(6,2) << std::endl;
	#endif

	//Correct state estimate
	x = x + K * y;

	#ifdef DEBUG_EXTENDEDKALMAN
	std::cout << "Matrix x is " << std::endl << x(0) << std::endl << x(1) << std::endl << x(2) << std::endl << x(3) << std::endl;
	#endif

	//Normalise to unit quaternion
	{
		float norm = sqrtf((float)(x(0) * x(0) + x(1) * x(1) + x(2) * x(2) + x(3) * x(3)));

		#ifdef DEBUG_EXTENDEDKALMAN
			std::cout << "norm is " << norm << std::endl;
		#endif

		x(0) /= norm;
		x(1) /= norm;
		x(2) /= norm;
		x(3) /= norm;

		#ifdef DEBUG_EXTENDEDKALMAN
			std::cout << "Matrix x is " << std::endl << x(0) << std::endl << x(1) << std::endl << x(2) << std::endl << x(3) << std::endl;
		#endif

	}

	//Update state covariance
	P = (I - K * H) * P;

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix P is " << std::endl << P(0,0)<<" "<< P(0,1)<<" " << P(0,2)<<" " << P(0,3)<<" " << P(0,4) <<" "<< P(0,5)<<" " << P(0,6) <<" " << std::endl;
		std::cout << P(1,0)<<" "<< P(1,1)<<" " << P(1,2)<<" " << P(1,3)<<" " << P(1,4) <<" "<< P(1,5)<<" " << P(1,6) <<" " << std::endl;
		std::cout << P(2,0)<<" "<< P(2,1)<<" " << P(2,2)<<" " << P(2,3)<<" " << P(2,4) <<" "<< P(2,5)<<" " << P(2,6) <<" " << std::endl;
		std::cout << P(3,0)<<" "<< P(3,1)<<" " << P(3,2)<<" " << P(3,3)<<" " << P(3,4) <<" "<< P(3,5)<<" " << P(3,6) <<" " << std::endl;
		std::cout << P(4,0)<<" "<< P(4,1)<<" " << P(4,2)<<" " << P(4,3)<<" " << P(4,4) <<" "<< P(4,5)<<" " << P(4,6) <<" " << std::endl;
		std::cout << P(5,0)<<" "<< P(5,1)<<" " << P(5,2)<<" " << P(5,3)<<" " << P(5,4) <<" "<< P(5,5)<<" " << P(5,6) <<" " << std::endl;
		std::cout << P(6,0)<<" "<< P(6,1)<<" " << P(6,2)<<" " << P(6,3)<<" " << P(6,4) <<" "<< P(6,5)<<" " << P(6,6) <<" " << std::endl;
	#endif


	quaternion->w = x(0);
	quaternion->x = x(1);
	quaternion->y = x(2);
	quaternion->z = x(3);

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "Matrix x is " << std::endl << x(0) << std::endl << x(1) << std::endl << x(2) << std::endl << x(3) << std::endl;
	#endif

	#ifdef DEBUG_EXTENDEDKALMAN
		std::cout << "quaternion.w is " << quaternion->w << std::endl;
		std::cout << "quaternion.x is " << quaternion->x << std::endl;
		std::cout << "quaternion.y is " << quaternion->y << std::endl;
		std::cout << "quaternion.z is " << quaternion->z << std::endl;
	#endif


}