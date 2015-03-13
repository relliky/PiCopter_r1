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
 */

#define MCU_OVERSEER

#include "Overseer.h"

//#include "OptimusPiCopter/AHRS/AHRS.h"

/*
static SPISlaveClass RPiSPISlave(0);
static MotorControllerClass motor0(0);
static MotorControllerClass motor1(1);
static MotorControllerClass motor2(2);
static MotorControllerClass motor3(3);
static PinControllerClass IC0(IC0Pin), IC1(IC1Pin), IC2(IC2Pin), IC3(IC3Pin), IC4(IC4Pin), IC5(IC5Pin), IC6(IC6Pin),
		IC7(IC7Pin), AN0(AN0Pin), AN1(AN1Pin), AN2(AN2Pin), AN3(AN3Pin), AN4(AN4Pin), AN5(AN5Pin);
*/

void main(void)
{

	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_INT);

	ArbitratorClass Arbitrator;

//	PiSlavedCopterClass PiSlavedCopter1;
/*
    motor1.config(BLDC);
	motor1.start();
*/



/*
	#undef DEBUG
	#ifdef DEBUG
			DebugFunctionClass Debug_0;
			Debug_0.RunTests();
	#endif


	ControlClass Control;
	Control.enable();
	delete &Control;
*/

/*
	LEDClass LED1(1);
	LED1.set();
*/

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





/*

	AHRSClass AHRS;
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


	while(1)
	{

		for(int i=0; i<50; i++)
		{

				float dt = 0.01;
				float oneSecDelay = 66666666/2.6666666/2;
				int   delay = (int)(oneSecDelay*dt);
				SysCtlDelay(delay);

			 AHRS.update(dt);
			 Pitch = AHRS.getPitch();
			 Roll = AHRS.getRoll();
			 Yaw = AHRS.getYaw();
			// Data fused out still is approching to 0.


			 X = AHRS.getX();
			 Y = AHRS.getY();
			 Z = AHRS.getZ();
			 P = AHRS.getP();
			 Q = AHRS.getQ();
			 R = AHRS.getR();
			 Temp = AHRS.getTemp();

			 if(PitchM >= Pitch) {PitchM = Pitch;}
			 if(PitchM >= Roll) {RollM = Roll;}
			 if(YawM >= Yaw) {YawM = Yaw;}
		}
		printf("Pitch is %f\n",Pitch);
		printf("Roll is %f\n",Roll);
		printf("Yaw is %f\n",Yaw);

		printf("X is %f\n",X);
		printf("Y is %f\n",Y);
		printf("Z is %f\n",Z);
		printf("P is %f\n",P);
		printf("Q is %f\n",Q);
		printf("R is %f\n",R);
		printf("Temp is %f\n",Temp);

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


}



