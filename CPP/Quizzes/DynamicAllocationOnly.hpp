
/*

	quiz 4 question 2.
	How to make cpp class be dynamically allocated only.


*/

#pragma once

#include "cstring"
#include <string>
#include <iostream>

class String4
{
public:
	String4(const char *ch);
	void Destroy();
	~String4() { delete[] m_str; };

private:
	char *m_str;
};
