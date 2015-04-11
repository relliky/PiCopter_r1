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
// include <cstddef> to support "new" operator to dynamically allocate memory
#include <cstddef>

typedef enum {StandaloneCopterMode, RPiControlledCopterMode} copterMode_t;

class ArbitratorClass
{
public:
	ArbitratorClass();
	virtual ~ArbitratorClass();
	void setStandaloneCopterMode();
	void setRPiControlledCopterMode();
	void start();
	void setDtInStandaloneCopterMode(float dt_set);


private:
	copterMode_t copterMode;
	RPiControlledCopterClass*	RPiControlledCopter;
	StandaloneCopterClass*		StandaloneCopter;
	float  dt;

};


#endif /* ARBITRATORCLASS_H_ */
