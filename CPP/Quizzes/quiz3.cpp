

#include "quiz3.hpp"

using namespace hrdxxx;

void bar(String3_1 s)
{
	(void)s;
}


void fifi()
{
	bar("good luck hrd39");
}


int main()
{

	String3_1 s1("HI");

	const String3_1 s2 = s1;

	s1 = s2;

	if(s2[0] == 'H')
	{
		std::cout<<"ok"<<std::endl;
	}

	s2[0] = 'J';

	std::cout<< s2 << std::endl;





	return 0;
}

