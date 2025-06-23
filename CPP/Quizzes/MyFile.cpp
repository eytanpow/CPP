
/*

	quiz 4 question 2.
	How to make cpp class be dynamically allocated only.


*/

#include "MyFile.hpp"

int main()
{

	MyFile my("/abcd");
	DerivedTest *t = new DerivedTest();
	(void)t;

	(void)my;

	return 0;
}