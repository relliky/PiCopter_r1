/*
 * main.c
 *
 *
 *
 *
 * Communicate with BLDC - done
 * Read data from MPU - done
 * Communicate with both motor controllers - done
 * @TODO Bounce programming data from pi to BLDC controllers
 * Add input capture support - done
 * Add input capture SPI interface - done
 * Add GPIO input and output - done
 * @TODO Create motor status register to allow overseer to monitor rotation status
 * @TODO Add initial speed parameter to motor startup command
 * @TODO Add motor rotation direction change command
 * 			--- Matthew Waston
 * Move the code from Raspberry Pi down to Overseer  --done
 * including:
 * 1) Adding MPU9150 support, I2C support on Overseer
 * 2)
  */

#define MCU_OVERSEER

#include "Overseer.h"


//#include "OptimusPiCopter/AHRS/AHRS.h"
/*
#include <vector>
class TestDataClass
{
public:
	float Pitch, Roll, Yaw, X, Y, Z, Temp, P, Q, R;
};
*/
void main(void)
{

	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_INT);


//	RPiControlledCopter.running();


	ArbitratorClass Arbitrator;
	Arbitrator.setDtInStandaloneCopterMode(2);
	Arbitrator.start();






	#define DEBUG
	#undef DEBUG
	#ifdef DEBUG
			DebugFunctionClass Debug_0;
			Debug_0.RunTests();
	#endif



//	OptimusPiInterfaceClass OptimusPi;
//	AHRSClass AHRS(&OptimusPi);

	while(1);


/*
	PinControllerClass p7(IC7Pin, GPIOOutputType);
	p7.~PinControllerClass();
*/

/*
	motor1.config(BLDC);
	motor1.start();
*/





/*
	int * a;
	a = new int(1);
	std::cout << *a << std::endl;
*/

/*
    LEDClass LED0(0) ;
    LEDClass LED1(1);

    LED0.LEDClass(0);
*/
//	LEDClass LED1(1);
//	LED1.set();


//	GPTimerClass Timer1(NULL);
//	Timer1.start();

//	LEDClass LED0(0);
//	LED0.set();

/*
	while(1){

		LED1.toggle();

		float oneSecDelay = 66666666/2.6666666/2;
		int   delay = (int)(oneSecDelay/10);
		SysCtlDelay(delay);
	} //Loop here to serve timer interrupt

*/

/*
	OptimusPiInterfaceClass OptimusPi;

	OptimusPiInterfaceClass* OptPiPtr;

	OptPiPtr = &OptimusPi;
	RXInterfaceClass RX_0(OptPiPtr);

	while(1){RX_0.update();}

*/

// operator


	//struct Test_s {float a,b;};


/*

	OptimusPiInterfaceClass OptimusPi;
	AHRSClass AHRS(&OptimusPi);


	//printf("\nThis is MPU9150 scaledSensoredData in AHRS before AHRS.update().fuse(dt) function. dt=0.05 <=> 200Hz.\n");

	std::vector<TestDataClass> TestData(20);

	TestData.at(0).X = 0.031491;
	TestData.at(0).Y = -0.642912;
	TestData.at(0).Z = 0.885281;
	TestData.at(0).P = -39.465649;
	TestData.at(0).Q = -19.389313;
	TestData.at(0).R = 10.854961;
	TestData.at(0).Temp = 27.597059;


	for(int i=0; i<1; i++)
	{
		AHRS.scaledSensorData.x = TestData.at(i).X;
		AHRS.scaledSensorData.y = TestData.at(i).Y;
		AHRS.scaledSensorData.z = TestData.at(i).Z;
		AHRS.scaledSensorData.p = TestData.at(i).P;
		AHRS.scaledSensorData.q = TestData.at(i).Q;
		AHRS.scaledSensorData.r = TestData.at(i).R;
		AHRS.update(0.05);

        float PitchTest = AHRS.getPitch();
        float RollTest = AHRS.getRoll();
        float YawTest = AHRS.getYaw();
        float XTest = AHRS.getX();
        float YTest = AHRS.getY();
        float ZTest = AHRS.getZ();
        float PTest = AHRS.getP();
        float QTest = AHRS.getQ();
        float RTest = AHRS.getR();


        printf("\nThis is data set %d\n", i);
        printf("Pitch is %f\n",PitchTest);
        printf("Roll is %f\n",RollTest);
        printf("Yaw is %f\n",YawTest);
        printf("X is %f\n",XTest);
        printf("Y is %f\n",YTest);
        printf("Z is %f\n",ZTest);
        printf("P is %f\n",PTest);
        printf("Q is %f\n",QTest);
        printf("R is %f\n",RTest);

	}



			while(1);

*/


/*
		for(int i=0; i<50; i++)
		{

				float dt = 0.005;//200Hz
				float oneSecDelay = 66666666/2.6666666/2;
				int   delay = (int)(oneSecDelay*dt);
				SysCtlDelay(delay);


			static float Pitch, PitchM;
			static float Roll, RollM;
			static float Yaw, YawM;
			static float X;
			static float Y;
			static float Z;
			static float P;
			static float Q;
			static float R;
			static float Temp;

			 AHRS.update(dt);
			 Pitch = AHRS.getPitch();
			 Roll = AHRS.getRoll();
			 Yaw = AHRS.getYaw();
			// Data fused out still is approching to 0.



			 if(PitchM >= Pitch) {PitchM = Pitch;}
			 if(PitchM >= Roll) {RollM = Roll;}
			 if(YawM >= Yaw) {YawM = Yaw;}
		}
		printf("Pitch is %f\n",Pitch);
		printf("Roll is %f\n",Roll);
		printf("Yaw is %f\n",Yaw);
		printf("x is %f\n",AHRS.scaledSensorData.x);
		printf("y is %f\n",AHRS.scaledSensorData.y);
		printf("z is %f\n", AHRS.scaledSensorData.z);
		printf("p is %f\n",AHRS.scaledSensorData.p);
		printf("q is %f\n",AHRS.scaledSensorData.q);
		printf("r is %f\n", AHRS.scaledSensorData.r);

	}

*/


/*

	while(1)
	{

		//updateReadBuffers();
		//emptyMessageQueue();

		motor1.setPWMWidth(0xA0);

	}

*/

//	EigenTestClass EigenTest;
//	EigenTest.runEigenTests();
	while(1){}

}



