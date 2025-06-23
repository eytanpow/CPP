
#pragma once

#include "cstring"
#include <string>
#include <iostream>

namespace hrdxxx
{
	class HrdString
	{
	public:
		HrdString(const HrdString &str) // copy constructor
		{
			this->m_str = new char[strlen(str.m_str) + 1];
		}
		~HrdString()
		{
			delete[] m_str;
		};
		HrdString(const std::string &ch)
		{
			m_str = new char[strlen(ch.c_str()) + 1];
		}

		HrdString(const char *ch)
		{
			m_str = new char[strlen(ch) + 1];
		}

	private:
		char *m_str;
	};

}