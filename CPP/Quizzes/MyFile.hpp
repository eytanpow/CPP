
/*

	quiz 4 question 2.
	How to make cpp class be dynamically allocated only.


*/

#pragma once

#include "string.hpp"

class MyFile
{
public:
	MyFile(const hrdxxx::HrdString filename)
	{
		std::cout << "ctor1" << std::endl;
		(void)filename;
	}
	// MyFile(const bool some_flag = false)
	// {
	// 	std::cout << "ctor2" << std::endl;
	// 	(void)some_flag;
	// };
};

class TestClass
{
public:
	virtual ~TestClass() = 0;
};
// inline TestClass::~TestClass(){}

class DerivedTest : public TestClass
{
};
