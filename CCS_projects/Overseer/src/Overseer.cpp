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

static SPISlaveClass RPiSPISlave(0);
static MotorControllerClass motor0(0);
static MotorControllerClass motor1(1);
static MotorControllerClass motor2(2);
static MotorControllerClass motor3(3);
static PinControllerClass IC0(IC0Pin), IC1(IC1Pin), IC2(IC2Pin), IC3(IC3Pin), IC4(IC4Pin), IC5(IC5Pin), IC6(IC6Pin),
		IC7(IC7Pin), AN0(AN0Pin), AN1(AN1Pin), AN2(AN2Pin), AN3(AN3Pin), AN4(AN4Pin), AN5(AN5Pin);

void main(void)
{
	uint8_t a = 0,b = 0, c = 0, d = 0, e = 0;
	uint16_t i = 0;

	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_INT);

 //   motor0.config(BLDC);
//	motor0.start();

	I2CClass I2CClass_0;


	#define MPU9150_ADDRESS_AD0_LOW  0X68
	#define MPU9150_RA_WHO_AM_I 0x75
	#define MPU9150_RA_TEST_RW 0x74

	#define TEST_REG_VALUE 0x0f


		I2CClass_0.readRegisters8(MPU9150_ADDRESS_AD0_LOW, MPU9150_RA_WHO_AM_I, &a, 1);
		while(a != 0x68){}
		//pass

		//test bit 3 of b (4th bit) out of 0x68, which is 0b0110_1000[3] = 0x1
		I2CClass_0.readBit8(MPU9150_ADDRESS_AD0_LOW, MPU9150_RA_WHO_AM_I, 3, &b);
		while(b != 0x1){}
		//pass

		//test [5:3] of b => 0b0110_1000[5:3]=> 0b101 => 0x5
		I2CClass_0.readbits8(MPU9150_ADDRESS_AD0_LOW, MPU9150_RA_WHO_AM_I, 5, 3, &c);
		while(c != 0x5){}
		//pass

		//N.B. readRegisters16 CANNOT BE tested for MPU9150  due to its special usage.
		while(1){}





//		b = I2CClass_0.readI2C0(MPU9150_ADDRESS_AD0_LOW, MPU9150_RA_WHO_AM_I);

//		c = I2CClass_0.readI2C0(MPU9150_ADDRESS_AD0_LOW, MPU9150_RA_TEST_RW);




		// a always get 0xff;
	//	d = I2CClass_0.readI2C0(MPU9150_ADDRESS_AD0_LOW, MPU9150_RA_TEST_RW);


	//	for(i=0;i<600;i++){}
//		e = I2CClass_0.readI2C0(MPU9150_ADDRESS_AD0_LOW, MPU9150_RA_WHO_AM_I);

//		for(i=0;i<600;i++){}
		//updateReadBuffers();
		//emptyMessageQueue();

//		motor0.setPWMWidth(0xA0);



}

/**
 * Updates the SPI slave read buffers with new data.
 */
void updateReadBuffers()
{
	// Currently broken as 24/7 polling just floods the SPI bus, we need to either poll these registers on demand or at a fixed interval
//	RPiSPISlave.updateReadResponse(OVERSEER_GET_MOTOR_STATUS_0, motor0.running());
//	RPiSPISlave.updateReadResponse(OVERSEER_GET_MOTOR_STATUS_1, motor1.running());
//	RPiSPISlave.updateReadResponse(OVERSEER_GET_MOTOR_STATUS_2, motor2.running());
//	RPiSPISlave.updateReadResponse(OVERSEER_GET_MOTOR_STATUS_3, motor3.running());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_IC0_WIDTH, IC0.getICPeriod());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_IC1_WIDTH, IC1.getICPeriod());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_IC2_WIDTH, IC2.getICPeriod());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_IC3_WIDTH, IC3.getICPeriod());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_IC4_WIDTH, IC4.getICPeriod());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_IC5_WIDTH, IC5.getICPeriod());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_IC6_WIDTH, IC6.getICPeriod());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_IC7_WIDTH, IC7.getICPeriod());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_IC0_GPIO_INPUT_STATUS, IC0.getGPIOInputState());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_IC1_GPIO_INPUT_STATUS, IC1.getGPIOInputState());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_IC2_GPIO_INPUT_STATUS, IC2.getGPIOInputState());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_IC3_GPIO_INPUT_STATUS, IC3.getGPIOInputState());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_IC4_GPIO_INPUT_STATUS, IC4.getGPIOInputState());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_IC5_GPIO_INPUT_STATUS, IC5.getGPIOInputState());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_IC6_GPIO_INPUT_STATUS, IC6.getGPIOInputState());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_IC7_GPIO_INPUT_STATUS, IC7.getGPIOInputState());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_AN0_GPIO_INPUT_STATUS, AN0.getGPIOInputState());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_AN1_GPIO_INPUT_STATUS, AN1.getGPIOInputState());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_AN2_GPIO_INPUT_STATUS, AN2.getGPIOInputState());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_AN3_GPIO_INPUT_STATUS, AN3.getGPIOInputState());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_AN4_GPIO_INPUT_STATUS, AN4.getGPIOInputState());
	RPiSPISlave.updateReadResponse(OVERSEER_GET_AN5_GPIO_INPUT_STATUS, AN5.getGPIOInputState());
}

/**
 * Empties the message queue, performaing a switch statement on every message command in order to carry out the
 * requested operation.
 *
 * @TODO this could be implemented using a dictionary class to neaten things up
 */
void emptyMessageQueue()
{
	message_s message;
	while (RPiSPISlave.getMessage(&message))
	{
		switch (message.command)
		{
		case OVERSEER_CONFIG_MOTOR_CH0_BLDC:
			motor0.config(BLDC);
			break;
		case OVERSEER_CONFIG_MOTOR_CH0_BRUSHED:
			motor0.config(brushed);
			break;
		case OVERSEER_CONFIG_MOTOR_CH0_STEPPER:
			motor0.config(stepper);
			break;
		case OVERSEER_CONFIG_MOTOR_CH1_BLDC:
			motor1.config(BLDC);
			break;
		case OVERSEER_CONFIG_MOTOR_CH1_BRUSHED:
			motor1.config(brushed);
			break;
		case OVERSEER_CONFIG_MOTOR_CH1_STEPPER:
			motor1.config(stepper);
			break;
		case OVERSEER_CONFIG_MOTOR_CH2_BLDC:
			motor2.config(BLDC);
			break;
		case OVERSEER_CONFIG_MOTOR_CH2_BRUSHED:
			motor2.config(brushed);
			break;
		case OVERSEER_CONFIG_MOTOR_CH2_STEPPER:
			motor2.config(stepper);
			break;
		case OVERSEER_CONFIG_MOTOR_CH3_BLDC:
			motor3.config(BLDC);
			break;
		case OVERSEER_CONFIG_MOTOR_CH3_BRUSHED:
			motor3.config(brushed);
			break;
		case OVERSEER_CONFIG_MOTOR_CH3_STEPPER:
			motor3.config(stepper);
			break;
		case OVERSEER_START_MOTOR_0:
			motor0.start();
			break;
		case OVERSEER_START_MOTOR_1:
			motor1.start();
			break;
		case OVERSEER_START_MOTOR_2:
			motor2.start();
			break;
		case OVERSEER_START_MOTOR_3:
			motor3.start();
			break;
		case OVERSEER_STOP_MOTOR_0:
			motor0.stop();
			break;
		case OVERSEER_STOP_MOTOR_1:
			motor1.stop();
			break;
		case OVERSEER_STOP_MOTOR_2:
			motor2.stop();
			break;
		case OVERSEER_STOP_MOTOR_3:
			motor3.stop();
			break;
		case OVERSEER_SET_MOTOR_PWM_0:
			motor0.setPWMWidth(message.parameters[0]);
			break;
		case OVERSEER_SET_MOTOR_PWM_1:
			motor1.setPWMWidth(message.parameters[0]);
			break;
		case OVERSEER_SET_MOTOR_PWM_2:
			motor2.setPWMWidth(message.parameters[0]);
			break;
		case OVERSEER_SET_MOTOR_PWM_3:
			motor3.setPWMWidth(message.parameters[0]);
			break;
		case OVERSEER_CONFIG_IC0_INPUT_CAPTURE:
			IC0.config(InputCaptureType);
			break;
		case OVERSEER_CONFIG_IC0_GPIO_OUTPUT:
			IC0.config(GPIOOutputType);
			break;
		case OVERSEER_CONFIG_IC0_GPIO_INPUT:
			IC0.config(GPIOInputType);
			break;
		case OVERSEER_CONFIG_IC1_INPUT_CAPTURE:
			IC1.config(InputCaptureType);
			break;
		case OVERSEER_CONFIG_IC1_GPIO_OUTPUT:
			IC1.config(GPIOOutputType);
			break;
		case OVERSEER_CONFIG_IC1_GPIO_INPUT:
			IC1.config(GPIOInputType);
			break;
		case OVERSEER_CONFIG_IC2_INPUT_CAPTURE:
			IC2.config(InputCaptureType);
			break;
		case OVERSEER_CONFIG_IC2_GPIO_OUTPUT:
			IC2.config(GPIOOutputType);
			break;
		case OVERSEER_CONFIG_IC2_GPIO_INPUT:
			IC2.config(GPIOInputType);
			break;
		case OVERSEER_CONFIG_IC3_INPUT_CAPTURE:
			IC3.config(InputCaptureType);
			break;
		case OVERSEER_CONFIG_IC3_GPIO_OUTPUT:
			IC3.config(GPIOOutputType);
			break;
		case OVERSEER_CONFIG_IC3_GPIO_INPUT:
			IC3.config(GPIOInputType);
			break;
		case OVERSEER_CONFIG_IC4_INPUT_CAPTURE:
			IC4.config(InputCaptureType);
			break;
		case OVERSEER_CONFIG_IC4_GPIO_OUTPUT:
			IC4.config(GPIOOutputType);
			break;
		case OVERSEER_CONFIG_IC4_GPIO_INPUT:
			IC4.config(GPIOInputType);
			break;
		case OVERSEER_CONFIG_IC5_INPUT_CAPTURE:
			IC5.config(InputCaptureType);
			break;
		case OVERSEER_CONFIG_IC5_GPIO_OUTPUT:
			IC5.config(GPIOOutputType);
			break;
		case OVERSEER_CONFIG_IC5_GPIO_INPUT:
			IC5.config(GPIOInputType);
			break;
		case OVERSEER_CONFIG_IC6_INPUT_CAPTURE:
			IC6.config(InputCaptureType);
			break;
		case OVERSEER_CONFIG_IC6_GPIO_OUTPUT:
			IC6.config(GPIOOutputType);
			break;
		case OVERSEER_CONFIG_IC6_GPIO_INPUT:
			IC6.config(GPIOInputType);
			break;
		case OVERSEER_CONFIG_IC7_INPUT_CAPTURE:
			IC7.config(InputCaptureType);
			break;
		case OVERSEER_CONFIG_IC7_GPIO_OUTPUT:
			IC7.config(GPIOOutputType);
			break;
		case OVERSEER_CONFIG_IC7_GPIO_INPUT:
			IC7.config(GPIOInputType);
			break;
		case OVERSEER_CONFIG_AN0_ANALOG_INPUT:
			AN0.config(AnalogInputType);
			break;
		case OVERSEER_CONFIG_AN0_GPIO_OUTPUT:
			AN0.config(GPIOOutputType);
			break;
		case OVERSEER_CONFIG_AN0_GPIO_INPUT:
			AN0.config(GPIOInputType);
			break;
		case OVERSEER_CONFIG_AN1_ANALOG_INPUT:
			AN1.config(AnalogInputType);
			break;
		case OVERSEER_CONFIG_AN1_GPIO_OUTPUT:
			AN1.config(GPIOOutputType);
			break;
		case OVERSEER_CONFIG_AN1_GPIO_INPUT:
			AN1.config(GPIOInputType);
			break;
		case OVERSEER_CONFIG_AN2_ANALOG_INPUT:
			AN2.config(AnalogInputType);
			break;
		case OVERSEER_CONFIG_AN2_GPIO_OUTPUT:
			AN2.config(GPIOOutputType);
			break;
		case OVERSEER_CONFIG_AN2_GPIO_INPUT:
			AN2.config(GPIOInputType);
			break;
		case OVERSEER_CONFIG_AN3_ANALOG_INPUT:
			AN3.config(AnalogInputType);
			break;
		case OVERSEER_CONFIG_AN3_GPIO_OUTPUT:
			AN3.config(GPIOOutputType);
			break;
		case OVERSEER_CONFIG_AN3_GPIO_INPUT:
			AN3.config(GPIOInputType);
			break;
		case OVERSEER_CONFIG_AN4_ANALOG_INPUT:
			AN4.config(AnalogInputType);
			break;
		case OVERSEER_CONFIG_AN4_GPIO_OUTPUT:
			AN4.config(GPIOOutputType);
			break;
		case OVERSEER_CONFIG_AN4_GPIO_INPUT:
			AN4.config(GPIOInputType);
			break;
		case OVERSEER_CONFIG_AN5_ANALOG_INPUT:
			AN5.config(AnalogInputType);
			break;
		case OVERSEER_CONFIG_AN5_GPIO_OUTPUT:
			AN5.config(GPIOOutputType);
			break;
		case OVERSEER_CONFIG_AN5_GPIO_INPUT:
			AN5.config(GPIOInputType);
			break;
		case OVERSEER_SET_IC0_GPIO_OUTPUT_STATUS:
			IC0.setGPIOOutputState((bool) message.parameters[0]);
			break;
		case OVERSEER_SET_IC1_GPIO_OUTPUT_STATUS:
			IC1.setGPIOOutputState((bool) message.parameters[0]);
			break;
		case OVERSEER_SET_IC2_GPIO_OUTPUT_STATUS:
			IC2.setGPIOOutputState((bool) message.parameters[0]);
			break;
		case OVERSEER_SET_IC3_GPIO_OUTPUT_STATUS:
			IC3.setGPIOOutputState((bool) message.parameters[0]);
			break;
		case OVERSEER_SET_IC4_GPIO_OUTPUT_STATUS:
			IC4.setGPIOOutputState((bool) message.parameters[0]);
			break;
		case OVERSEER_SET_IC5_GPIO_OUTPUT_STATUS:
			IC5.setGPIOOutputState((bool) message.parameters[0]);
			break;
		case OVERSEER_SET_IC6_GPIO_OUTPUT_STATUS:
			IC6.setGPIOOutputState((bool) message.parameters[0]);
			break;
		case OVERSEER_SET_IC7_GPIO_OUTPUT_STATUS:
			IC7.setGPIOOutputState((bool) message.parameters[0]);
			break;
		case OVERSEER_SET_AN0_GPIO_OUTPUT_STATUS:
			AN0.setGPIOOutputState((bool) message.parameters[0]);
			break;
		case OVERSEER_SET_AN1_GPIO_OUTPUT_STATUS:
			AN1.setGPIOOutputState((bool) message.parameters[0]);
			break;
		case OVERSEER_SET_AN2_GPIO_OUTPUT_STATUS:
			AN2.setGPIOOutputState((bool) message.parameters[0]);
			break;
		case OVERSEER_SET_AN3_GPIO_OUTPUT_STATUS:
			AN3.setGPIOOutputState((bool) message.parameters[0]);
			break;
		case OVERSEER_SET_AN4_GPIO_OUTPUT_STATUS:
			AN4.setGPIOOutputState((bool) message.parameters[0]);
			break;
		case OVERSEER_SET_AN5_GPIO_OUTPUT_STATUS:
			AN5.setGPIOOutputState((bool) message.parameters[0]);
			break;
		}
	}
}
