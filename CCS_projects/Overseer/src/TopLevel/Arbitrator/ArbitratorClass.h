/*
 * ArbitratorClass.h
 *
 *  Created on: 10 Mar 2015
 *      Author: Tai
 */

#ifndef ARBITRATORCLASS_H_
#define ARBITRATORCLASS_H_

#include "../RPiControlledCopter/RPiControlledCopter.h"
#include "../StandaloneCopter/StandaloneCopter.h"

class ArbitratorClass
{
public:
	ArbitratorClass();
	virtual ~ArbitratorClass();

	RPiControlledCopterClass	RPiControlledCopter;
	StandaloneCopterWrapper		StandaloneCopter;
};


#endif /* ARBITRATORCLASS_H_ */
