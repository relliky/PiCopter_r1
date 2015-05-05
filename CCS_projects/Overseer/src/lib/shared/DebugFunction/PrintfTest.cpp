/*
 * PrintfTest.cpp
 *
 *  Created on: 10 Feb 2015
 *      Author: Tai
 */

#include "PrintfTest.h"

PrintfTestClass::PrintfTestClass()
{
	// TODO Auto-generated constructor stub

}

PrintfTestClass::~PrintfTestClass()
{
	// TODO Auto-generated destructor stub
}

void PrintfTestClass::VariableStringTest(void)
{
	uint32_t i;
	float 	 f;
	printf("  1) Start VariableStringTest. \n");
	printf("     integer tests.\n");
	for(i=0; i<2; i++)
	{
		printf("     printf: i is %d\n", i);
		std::cout << "     cout: i is " << i << "\n";
		std::cerr << "     cerr: i is " << i << "\n";
	}

	printf("     floats tests.\n");
	for(f=0.5; f<2; f++)
	{
		printf("     printf: i is %f\n", f);
		std::cout << "     cout: i is " << f << "\n";
		std::cerr << "     cerr: i is " << f << "\n";
	}

	std::cout << "\n";
}

void PrintfTestClass::ConstStringTest_LastMethodIsNotCout(void)
{
	printf("  2) Start ConstStringTest_LastMethodIsNotCout Test.\n");
	std::cout << "     Hello, << sign and cout.\n" ;
	std::cerr << "     Hello, cerr.\n" ; //printing in red but very slow!!
	printf("     Trying to printf info between two cerr.\n");
	std::cout << "     Trying to forward info to cout between two cerr.\n" ;
	std::cerr << "     2nd cerr.\n" ; // Still got printed out.
	std::cout << "     Hello, message after 2nd cerr\n" ; //
	std::cerr << "     3nd cerr.\n" ; // Still got printed out.
	std::cout << "     Hello, cout after last cerr\n" ; // getting printed out. If there is cout as the last function, it would not print out. But it gets printed out if any function after this is invoked.
	printf("     printf info after last cerr\n\n");
}

void PrintfTestClass::ConstStringTest_LastMethodIsCout(void)
{
	std::cout << "  3) Start ConstStringTest_LastMethodIsCout Test.\n";
	std::cout << "  There is a cout to print after next cerr, but it would not get printed out. \n";
	std::cerr << "  last cerr.\n" ; // Still got printed out.
	std::cout << "  WARNING: This line (cout) should not get printed out unless there is anything getting printed out after this line. \n\n" ; // NOT getting printed out. If there is cout as the last function, it would not print out. But it gets printed out if any function after this is invoked.
}

//REASONS: The reason why last message sometimes didn't get printed out is that the strings in the buffer sometimes didn't get flushed.
//         As long as another function has been called, the printf/std::cout will flush the buffer and print it out to the terminal.  ---Tai 24/02/2015
