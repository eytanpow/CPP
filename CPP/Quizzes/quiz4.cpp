
#include "quiz4.hpp"

using namespace hrdxxx;

String4 *String4::Create(const char *str)
{

	return new String4(str);
}

String4::String4(const char *str)
{
	m_str = new char[strlen(str) + 1];
}

String4::String4(const String4 &str)
{

	this->m_str = new char[strlen(str.m_str) + 1];
}

int main()
{
	using namespace std;
	String4 *s1 = String4::Create("hello");
	// String4 s2("not allowed");
	String4 *s3 = new String4(*s1);

	//	String4 *s5 = new String4("fff"); also not allowed because the constructor
	// of this type is provate
	(void)s3;
	//	(void)s5;
	std::cout << "almost finished" << endl;
	delete s1;

	return 0;
}