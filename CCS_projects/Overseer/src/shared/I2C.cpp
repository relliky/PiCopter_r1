/*
 * I2C.cpp
 *
 *  Created on: 14 Nov 2014
 *      Author: Tai
 */

#include "I2C.h"

I2CClass::I2CClass()
{
	this->openI2C();
}

I2CClass::~I2CClass()
{

}


int I2CClass::openI2C()
{
	//This function is for eewiki and is to be updated to handle any port

	//enable I2C module
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

	//reset I2C module
	SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);

	//enable GPIO peripheral that contains I2C
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

	// Configure the pin muxing for I2C0 functions on port B2 and B3.
	GPIOPinConfigure(GPIO_PB2_I2C0SCL);
	GPIOPinConfigure(GPIO_PB3_I2C0SDA);

	// Select the I2C function for these pins.
	GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
	GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

	// Enable and initialize the I2C0 master module.  Use the system clock for
	// the I2C0 module.  The last parameter sets the I2C data transfer rate.
	// If false the data rate is set to 100kbps and if true the data rate will
	// be set to 400kbps.
	I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);

	// Set data rate to 400kbps by following code
	//I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), true);

	//clear I2C FIFOs
	HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;

	return 0;

}

//read specified register on slave device
int I2CClass::readI2CAByte(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* buf)
{

	//specify that we are writing (a register address) to the
    //slave device
    I2CMasterSlaveAddrSet(I2C0_BASE, slaveAddress, false);

    //specify register to be read
    I2CMasterDataPut(I2C0_BASE, registerAddress);

    //send control byte and register address byte to slave device
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

    //wait for MCU to finish transaction
    while(I2CMasterBusy(I2C0_BASE));

    //specify that we are going to read from slave device
    I2CMasterSlaveAddrSet(I2C0_BASE, slaveAddress, true);

    //send control byte and read from the register we
    //specified
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

    //wait for MCU to finish transaction
    while(I2CMasterBusy(I2C0_BASE));

    //return data pulled from the specified register
    *buf = I2CMasterDataGet(I2C0_BASE);

    return 0;
}


//write specified register on slave device
int I2CClass::writeI2CAByte(uint8_t slaveAddress, uint8_t registerAddress, uint8_t buf)
{

	//specify that we are writing (a register address) to the
    //slave device
    I2CMasterSlaveAddrSet(I2C0_BASE, slaveAddress, false);

    //specify register to be write
    I2CMasterDataPut(I2C0_BASE, registerAddress);

    //send control byte and register address byte to slave device
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

    //wait for MCU to finish transaction
    while(I2CMasterBusy(I2C0_BASE));

    //Put the data needs to be written into the specified register
    I2CMasterDataPut(I2C0_BASE, buf);

    //send control byte and write to the register we
    //specified
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);

    //wait for MCU to finish transaction
    while(I2CMasterBusy(I2C0_BASE));

    return 0;
}

// The array of data is Little Endian
int I2CClass::readRegisters8(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, uint8_t len)
{
	uint8_t buf_internal;
	uint8_t offset = 0;
	int err = 0;

	if(len < 1)
		//error handle for invalid value.
		return -1;

	if(len == 1)
	{
		err += this->readI2CAByte(slaveAddress, registerAddress, &buf_internal);
		*data = buf_internal;
		return err;
	}else
		{
			for(offset=0; offset<len-1; offset++)
			{
				err += this->readI2CAByte(slaveAddress, registerAddress + offset, &buf_internal);
				data[offset] = buf_internal;
			}
			return err;
		}

}

// The every two bytes for following 16 bits registers are big endian, which is [7:0],[15:8] against to address, address+1. !! For reading ACCEL_XOUT_L,ACCEL_XOUT_H,ACCEL_YOUT_L,ACCEL_YOUT_H,ACCEL_ZOUT_L,ACCEL_ZOUT_H.
// This method CANNOT BE USED FOR READING COMMON SUCESSIVE REGISTERS!
// HAVING A LOOK AT MPU9150 REGISTER MAP WOULD ILLUSTRATE MORE.
int I2CClass::readRegisters16(uint8_t slaveAddress, uint8_t registerAddress, uint16_t* data, uint8_t len)
{
	uint8_t buf[MAX_BYTES_IN_A_TRANSCATION], i = 0;
	int err = 0;

	err += this->readRegisters8(slaveAddress, registerAddress, buf, len*2);
	for(i = 0; i < len; i++)
	{
		data[i] = (uint16_t)buf[i*2] << 8 | (uint16_t)buf[i*2+1];
	}
	return err;
}


/** Read a single bit from an 8-bit device register.
 * @param slaveAddress I2C slave device address
 * @param registerAddress Register regAddr to read from
 * @param bitNum Bit position to read (0-7)
 * @param data Container for single bit value
 * @return Status of read operation, 0 on sucess, -1 on failure
 */
int I2CClass::readBit8(uint8_t slaveAddress, uint8_t registerAddress, uint8_t bitNum, uint8_t* data)
{
	uint8_t buf;
	int err = 0;

	err += this->readRegisters8(slaveAddress, registerAddress, &buf, 1);
	*data = (buf & (1 << bitNum)) >> bitNum;
	return err;
}


/** Read multiple bits from an 8-bit device register.
 * @param slaveAddress I2C slave device address
 * @param registerAddress Register regAddr to read from
 * @param MSBLoc a.k.a. bitStart First bit position to read (0-7)
 * @param length Number of bits to read (not more than 8)
 * @param data Container for single bit value
 * @return Status of read operation, 0 on sucess, -1 on failure
 */
int I2CClass::readbits8(uint8_t slaveAddress, uint8_t registerAddress, uint8_t MSBLoc, uint8_t len, uint8_t* data)
{
	// 01101001 read byte
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    //    010   masked
    //   -> 010 shifted
    uint8_t buf, mask;
    int 	err = 0;

	err += this->readRegisters8(slaveAddress, registerAddress, &buf, 1);
	mask = ((1 << len) - 1) << (MSBLoc - len + 1);
	buf &= mask;
	*data =buf >> (MSBLoc - len + 1);
    return err;
}

// The array is little Endian
int I2CClass::writeRegisters8(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* buf, uint8_t len)
{
	uint8_t offset;
	int 	err = 0;

	if(len == 1)
	{
		err += this->writeI2CAByte(slaveAddress, registerAddress, *buf);
		return err;
	}else
		{
			for(offset=0; offset<len-1; offset++)
			{
				err += this->writeI2CAByte(slaveAddress, registerAddress + offset, buf[offset]);
			}
			return err;
		}

}


// N.B. IT WOULD NOT WORK UNLESS A READ OF THIS REGISTER IS VALID!!!
// SO FAR, IT SEEMS A READ TO A REGISTER MOST OF TIME IS INVALID IN A R/W REGISTER.
// THIS MEANS IF A R/W REGISTER IS WRITTEN INTO 0xFF, REAEDING IT STILL RETURNS 0x00.
/** write a single bit in an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitNum Bit position to write (0-7)
 * @param value New bit value to write
 * @return Status of operation (true = success)
 */
int I2CClass::writeBit8(uint8_t slaveAddress, uint8_t registerAddress, uint8_t bitNum, uint8_t data)
{
    uint8_t buf;
    int		err;
    err += this->readRegisters8(slaveAddress, registerAddress, &buf, 1);
    buf = (data != 0) ? (buf | (1 << bitNum)) : (buf & ~(1 << bitNum));
    err += writeRegisters8(slaveAddress, registerAddress, &buf, 1);
    return err;
}

