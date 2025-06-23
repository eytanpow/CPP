
#pragma once

#include "cstring"
#include <string>
#include <iostream>

namespace hrdxxx
{
	class String3_1
	{
	public:
		String3_1(const char *str)
		{
			m_str = new char[strlen(str) + 1];
			memcpy(m_str, str, strlen(str) + 1);
		}

		~String3_1()
		{
			delete[] m_str;
		};

		String3_1(const String3_1 &other)
		{
			m_str = new char[strlen(other.m_str) + 1];
			memcpy(m_str, other.m_str, strlen(other.m_str) + 1);
		}

		String3_1 &operator=(const String3_1 &other)
		{
			if (this != &other)
			{
				char *tempStr = strlen(other.m_str) ? new char[strlen(other.m_str) + 1] : nullptr;

				if (tempStr != nullptr)
				{
					memcpy(tempStr, other.m_str, strlen(other.m_str) + 1);
					delete[] this->m_str;
					this->m_str = tempStr;
				}
				else
				{
					std::cout << "Huston we  have a problem" << std::endl;
				}
			}

			return *this;
		}

		char &operator[](ssize_t index) const
		{
			std::cout << "no change" << std::endl;
			return m_str[index];
		}

		// char &operator[](ssize_t index)
		// {
		// 	std::cout << "char to change" << std::endl;
		// 	return m_str[index];
		// }

		friend std::ostream &operator<<(std::ostream &os, const String3_1 &str)
		{
			os << str.m_str << std::endl;
			return os;
		}

	private:
		char *m_str;
	};

}