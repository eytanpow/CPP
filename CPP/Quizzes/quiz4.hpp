
#pragma once

#include "cstring"
#include <string>
#include <iostream>

namespace hrdxxx
{
	class String4
	{
	public:
		static String4 *Create(const char *str);
		String4(const String4 &str);
		~String4() {};

	private:
		char *m_str;
		String4(const char *ch);
	};

}