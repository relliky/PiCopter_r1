/*
 * DebugFunction.cpp
 *
 *  Created on: 11 Feb 2015
 *      Author: Tai
 *
 *  Comments: The file itself cannot be called Debug.cpp, otherwise the compiler would not find the symbol for any method within this class.
 */



#include "DebugFunction.h"

#ifndef DEBUGOPTIONS_H_
	#include "DebugOptions.h"
#endif /*DEBUGOPTIONS_H_ */


DebugFunctionClass::DebugFunctionClass()
{
	// TODO Auto-generated constructor stub

}

DebugFunctionClass::~DebugFunctionClass()
{
	// TODO Auto-generated destructor stub
}


void DebugFunctionClass::RunTests(void)
{
	#ifdef DEBUG_RUN_I2C_BASIC_TEST
			I2CTestClass I2CTest;

			#ifdef DEBUG_PRINTF_VIA_JTAG
					printf("\n1. Start I2C Basic Tests.\n\n");
			#endif

			I2CTest.runBasicReadTest();

			#ifdef DEBUG_PRINTF_VIA_JTAG
					printf("  1) I2C Basic Read Tests Pass.\n\n");
			#endif

			I2CTest.runBasicWriteTest();

			#ifdef DEBUG_PRINTF_VIA_JTAG
					printf("  2) I2C Basic Write Tests Pass.\n\n");
			#endif
	#endif

	#ifdef DEBUG_RUN_PRINTF_TEST
			PrintfTestClass PrintfTest;
			printf("2. Start Printf Tests.\n\n");
			PrintfTest.VariableStringTest();
			PrintfTest.ConstStringTest_LastMethodIsNotCout();
			PrintfTest.ConstStringTest_LastMethodIsCout();
	#endif

}
