/*
 * SPIWrapper.h
 *
 *  Created on: 2 Sep 2014
 *      Author: matt
 */

#ifndef SPIWRAPPER_H_
#define SPIWRAPPER_H_

#include "SPI.h"
#include "SPICommands.h"
#include <cstring>

class SPIWrapper
{
public:
	SPIWrapper();
	virtual ~SPIWrapper();
	
	void sendMessage(uint8_t command, uint32_t* parameters = NULL, uint32_t numberOfParams = 0);
	void getData(uint8_t command, uint32_t* buf, uint32_t numberOfParams);
	
private:
	SPIClass SPI;
};

#endif /* SPIWRAPPER_H_ */