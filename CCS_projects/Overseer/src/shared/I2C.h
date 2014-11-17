/*
 * I2C.h
 *
 *  Created on: 16 Nov 2014
 *      Author: Tai
 */

#ifndef I2C_H_
#define I2C_H_

#define PART_TM4C123AH6PM //Needed to make pin_map include properly, isnt used in examples

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

class I2CClass {
public:
	I2CClass(std::string device);
	virtual ~I2CClass();
	int readRegisters8(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* buf, uint8_t len);
	int readRegisters16(uint8_t slaveAddress, uint8_t registerAddress, uint16_t* data, uint8_t len);
	int readBit8(uint8_t slaveAddress, uint8_t registerAddress, uint8_t bitNum, uint8_t* data);
	int readbits8(uint8_t slaveAddress, uint8_t registerAddress, uint8_t MSBLoc, uint8_t len, uint8_t* data);
	int writeRegisters8(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* buf, uint8_t len);
	int writeBit8(uint8_t slaveAddress, uint8_t registerAddress, uint8_t bitNum, uint8_t data);
	int writeBits8(uint8_t slaveAddress, uint8_t registerAddress, uint8_t MSBLoc, uint8_t len, uint8_t data);

private:
	int openI2C();
//	int setSlaveAddress(uint8_t address);

//	int file;
//    std::string filename;
};

#endif /* I2C_H_ */
