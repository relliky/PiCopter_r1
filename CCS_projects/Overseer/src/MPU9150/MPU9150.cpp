/*
 * MPU9150.cpp
 *
 *  Created on: 7 Aug 2014
 *      Author: matt
 */

#include "MPU9150.h"

/**
 * Constructor, the status of the AD0 pin must be specified in order to initialise with
 * the right address.
 *
 * @param AD0Status
 */
MPU9150Class::MPU9150Class(bool AD0Status)
		: I2C("/dev/i2c-1")
{
	if (AD0Status)
		MPUAddress = MPU9150_ADDRESS_AD0_HIGH;
	else
		MPUAddress = MPU9150_ADDRESS_AD0_LOW;
	
	magAddress = MPU9150_RA_MAG_ADDRESS;

	accel_sf = 16384;
	gyro_sf = 131;
}

MPU9150Class::~MPU9150Class()
{
}

/**
 * Tests connection by reading the WHO_AM_I register, which always holds the value 0x68, regardless of the status of the AD0 pin.
 *
 * @return true if 0x68 is read, otherwise 0
 */
bool MPU9150Class::testConnection()
{
	uint8_t buf;
	I2C.readRegisters8(MPUAddress, MPU9150_RA_WHO_AM_I, &buf, 1);
	return (0x68 == buf);
}

/**
 * Gets the raw 16 bit sensor data from the three accelerometers, temperature sensor, and three gyroscopes.
 * 
 * @param data - struct defined in MPU9150.h
 * @return - 0 on success, -1 on error
 */
int MPU9150Class::getRawSensorData(sensorData_s<int16_t>* data)
{
	uint16_t buf[7];
	uint8_t buf2[6];
	int err = I2C.readRegisters16(MPUAddress, MPU9150_RA_ACCEL_XOUT_H, buf, 7);
	err += I2C.readRegisters8(magAddress, MPU9150_RA_MAG_XOUT_L, buf2, 6); // Magnetometer's high and low bytes are packed the opposite way around to be fucking awkward, this is a workaround.
	data->x = (int16_t) buf[0];
	data->y = (int16_t) buf[1];
	data->z = (int16_t) buf[2];
	data->temp = (int16_t) buf[3];
	data->p = (int16_t) buf[4];
	data->q = (int16_t) buf[5];
	data->r = (int16_t) buf[6];
	data->magx = (int16_t)buf2[0] & ((int16_t)buf2[1] << 8);
	data->magy = (int16_t)buf2[2] & ((int16_t)buf2[3] << 8);
	data->magz = (int16_t)buf2[4] & ((int16_t)buf2[5] << 8);

	return err;
}

/**
 * Gets the scaled sensor data, with measurements in g, degrees/s, and degrees Celcius
 * 
 * @param data - struct defined in MPU9150.h
 * @return - 0 on success, -1 on error
 */
int MPU9150Class::getScaledSensorData(sensorData_s<float>* data)
{
	sensorData_s<int16_t> rawData;
	int err = this->getRawSensorData(&rawData);

	data->x = (float) rawData.x / accel_sf;
	data->y = (float) rawData.y / accel_sf;
	data->z = (float) rawData.z / accel_sf;
	data->temp = (float) (rawData.temp + 12412.0f) / 340.0f;
	data->p = (float) rawData.p / gyro_sf;
	data->q = (float) rawData.q / gyro_sf;
	data->r = (float) rawData.r / gyro_sf;
	//@TODO write code to read calibration data and then correctly calculate magnetometer outputs
	//data->magx

	return err;
}

/**
 * This register specifies the divider from the gyroscope output rate used to generate the
 * sample rate for the MPU-9150. The sensor register output, FIFO output and DMP sampling
 * are all based on the Sample Rate. The Sample Rate is generated by dividing the gyroscope
 * output rate by SMPLRT_DIV: Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV) where
 * Gyroscope Output Rate = 8kHz when the DLPF is disabled (DLPF_CFG = 0 or 7), and 1kHz
 * when the DLPF is enabled (see Register 26). Note: The accelerometer output rate is 1kHz.
 * This means that for a Sample Rate greater than 1kHz, the same accelerometer sample may
 * be output to the FIFO, DMP, and sensor registers more than once.
 *
 * @param value - 8-bit unsigned value. The Sample Rate is determined by dividing the
 * 				  gyroscope output rate by this value.
 * @return - 0 on success, -1 on error
 */
int MPU9150Class::setSampleRateDivider(uint8_t data)
{
	return (I2C.writeRegisters8(MPUAddress, MPU9150_RA_SMPLRT_DIV, &data, 1));
}

/**
 * The DLPF_CFG parameter sets the digital low pass filter configuration. It
 * also determines the internal sampling rate used by the device as shown in
 * the table below.
 *
 * Note: The accelerometer output rate is 1kHz. This means that for a Sample
 * Rate greater than 1kHz, the same accelerometer sample may be output to the
 * FIFO, DMP, and sensor registers more than once.
 *
 *          | ACCELEROMETER      | GYROSCOPE
 * DLPF_CFG | Bandwidth | Delay  | Bandwidth | Delay  | Sample Rate
 * ---------+-----------+--------+-----------+--------+-------------
 * 		  0 | 260Hz 	| 0ms 	 | 256Hz     | 0.98ms | 8kHz
 *        1 | 184Hz 	| 2.0ms  | 188Hz     | 1.9ms  | 1kHz
 *        2 | 94Hz 		| 3.0ms  | 98Hz      | 2.8ms  | 1kHz
 *        3 | 44Hz 		| 4.9ms  | 42Hz      | 4.8ms  | 1kHz
 *        4 | 21Hz 		| 8.5ms  | 20Hz      | 8.3ms  | 1kHz
 *        5 | 10Hz 		| 13.8ms | 10Hz      | 13.4ms | 1kHz
 *        6 | 5Hz 		| 19.0ms | 5Hz       | 18.6ms | 1kHz
 *        7 | -- Reserved --     | -- Reserved --     | Reserved
 *
 * @param cutoff - Must be one of MPU9150_DLPF_BW_256, MPU9150_DLPF_BW_188, MPU9150_DLPF_BW_98
 * 				   MPU9150_DLPF_BW_42, MPU9150_DLPF_BW_20, MPU9150_DLPF_BW_10, or
 * 				   MPU9150_DLPF_BW_5.
 * @return - 0 on success, -1 on error
 */
int MPU9150Class::setDLPFCornerFrequency(uint8_t data)
{
	return I2C.writeBits8(MPUAddress, MPU9150_RA_CONFIG, MPU9150_CFG_DLPF_CFG_BIT, MPU9150_CFG_DLPF_CFG_LENGTH, data);
}

/**
 * Sets the full scale gyroscope range.
 *
 * @param data - Must be one of:
 * 				 MPU9150_GYRO_FS_250
 * 				 MPU9150_GYRO_FS_500
 * 				 MPU9150_GYRO_FS_1000
 * 				 MPU9150_GYRO_FS_2000
 * @return - 0 on success, -1 on error
 */
int MPU9150Class::setGyroRange(uint8_t data)
{
	int err = I2C.writeBits8(MPUAddress, MPU9150_RA_GYRO_CONFIG, MPU9150_GCONFIG_FS_SEL_BIT, MPU9150_GCONFIG_FS_SEL_LENGTH,
			data);
	if (err >= 0)
	{
		switch (data)
		{
		case MPU9150_GYRO_FS_250:
			gyro_sf = 131;
			break;
		case MPU9150_GYRO_FS_500:
			gyro_sf = 65.5;
			break;
		case MPU9150_GYRO_FS_1000:
			gyro_sf = 32.8;
			break;
		case MPU9150_GYRO_FS_2000:
			gyro_sf = 16.4;
			break;
		}
	}

	return err;
}

/**
 * Sets the full scale accelerometer range.
 *
 * @param data - Must be one of:
 * 			  	 MPU9150_ACCEL_FS_2
 * 			  	 MPU9150_ACCEL_FS_4
 * 			  	 MPU9150_ACCEL_FS_8
 * 				 MPU9150_ACCEL_FS_16
 * @return - 0 on success, -1 on error
 */
int MPU9150Class::setAccelRange(uint8_t data)
{
	int err = I2C.writeBits8(MPUAddress, MPU9150_RA_ACCEL_CONFIG, MPU9150_ACONFIG_AFS_SEL_BIT,
	MPU9150_ACONFIG_AFS_SEL_LENGTH,
			data);
	if (err >= 0)
	{
		switch (data)
		{
		case MPU9150_ACCEL_FS_2:
			accel_sf = 16384;
			break;
		case MPU9150_ACCEL_FS_4:
			accel_sf = 8192;
			break;
		case MPU9150_ACCEL_FS_8:
			accel_sf = 4096;
			break;
		case MPU9150_ACCEL_FS_16:
			accel_sf = 2048;
			break;
		default:
			while (1)
				; // Halt on error
		}
	}
	return err;
}

/**
 * Enable/disable the I2C passthrough. This must be enabled in order to access the magnetometer.
 * 
 * @param enable - true to enable passthrough
 * @return - 0 on success, -1 on error
 */
int MPU9150Class::setI2CPassthrough(bool enable)
{
	uint8_t buf;
	if (enable) buf = 1;
	else if (!enable) buf = 0;
	return I2C.writeBit8(MPUAddress, MPU9150_RA_INT_PIN_CFG, MPU9150_INTCFG_I2C_BYPASS_EN_BIT, buf);
}

/**
 * Sets the status of the sleep bit. By setting SLEEP to 1, the MPU-9150 can be put into low
 * power sleep mode. This sometimes doesn't seem to set correctly, hence the extra checking.
 *
 * @param data - True to enable sleep
 * @return - 0 on success, -1 on error
 */
int MPU9150Class::setSleepStatus(bool data)
{
	uint8_t buf;
	if (data)
		buf = 1;
	else if (!data)
		buf = 0;
	uint8_t res;
	do
	{
		if (I2C.writeBit8(MPUAddress, MPU9150_RA_PWR_MGMT_1, MPU9150_PWR1_SLEEP_BIT, buf) < 0)
			return -1;
		if (I2C.readBit8(MPUAddress, MPU9150_RA_PWR_MGMT_1, MPU9150_PWR1_SLEEP_BIT, &res) < 0)
			return -1;
	} while (res != buf);
	return 0;
}

/**
 * Sets the clock source. An internal 8MHz oscillator, gyroscope based clock, or external
 * sources can be selected as the MPU-9150 clock source. When the internal 8 MHz oscillator
 * or an external source is chosen as the clock source, the MPU-9150 can operate in low power
 * modes with the gyroscopes disabled.
 *
 * Upon power up, the MPU-9150 clock source defaults to the internal oscillator. However,
 * it is highly recommended that the device be configured to use one of the gyroscopes
 * (or an external clock source) as the clock reference for improved stability.
 *
 * @param data - Must be one of:
 * 				 MPU9150_CLOCK_INTERNAL
 * 				 MPU9150_CLOCK_PLL_XGYRO
 * 				 MPU9150_CLOCK_PLL_YGYRO
 * 				 MPU9150_CLOCK_PLL_ZGYRO
 * 				 MPU9150_CLOCK_PLL_EXT32K
 *				 MPU9150_CLOCK_PLL_EXT19M
 *				 MPU9150_CLOCK_KEEP_RESET
 * @return - 0 on success, -1 on error
 */
int MPU9150Class::setClockSource(uint8_t data)
{
	return I2C.writeBits8(MPUAddress, MPU9150_RA_PWR_MGMT_1, MPU9150_PWR1_CLKSEL_BIT, MPU9150_PWR1_CLKSEL_LENGTH, data);
}

/**
 * Resets the device by setting the DEVICE_RESET bit. This bit clears once the reset completes.
 *
 * @return - 0 on success, -1 on error
 */
int MPU9150Class::reset()
{
	uint8_t res;
	do
	{
		if (I2C.writeBit8(MPUAddress, MPU9150_RA_PWR_MGMT_1, MPU9150_PWR1_DEVICE_RESET_BIT, 1) < 0)
			return -1;
		if (I2C.readBit8(MPUAddress, MPU9150_RA_PWR_MGMT_1, MPU9150_PWR1_DEVICE_RESET_BIT, &res) < 0)
				return -1;
	} while (res != 0);
	return 0;
}
