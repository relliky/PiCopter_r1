/*
 * I2C.h
 *
 *  Created on: 7 Aug 2014
 *      Author: matt
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdbool.h>
#include <stdint.h>

#include "inc/hw_memmap.h"
#include "inc/hw_i2c.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#define PART_TM4C123AH6PM //Needed to make pin_map include properly, isnt used in examples
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"

class I2CClass {
public:
	I2CClass();
	virtual ~I2CClass();
	void 	initI2C0();
	uint8_t readI2C0(uint8_t slave_addr, uint8_t reg);
	void 	writeI2C0(uint8_t slave_addr, uint8_t reg, uint8_t data);
};

#endif /* I2C_H_ */
