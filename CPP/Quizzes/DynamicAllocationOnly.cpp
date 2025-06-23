
/*

	quiz 4 question 2.
	How to make cpp class be dynamically allocated only.


*/

#include "DynamicAllocationOnly.hpp"

String4::String4(const char *str)
{
	m_str = new char[strlen(str) + 1];

	memcpy(m_str, str, strlen(str) + 1);
}

void String4::Destroy()
{
	delete this;
}

int main()
{

	String4 *sPtr = new String4("hello");
	(void)sPtr;
	sPtr->Destroy();

	const char *ch = "bye-bye";
	const bool b = false;
	const bool helper = static_cast<const bool>(ch);

	if (b == helper)
	{
		std::cout << "whai whai" << std::endl;
	}

	return 0;
}