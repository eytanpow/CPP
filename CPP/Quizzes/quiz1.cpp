#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class B
{
public:
    B(const char *str)
    {
        m_str = new char(strlen(str) + 1);
        strcpy(m_str, str);
    }

    ~B()
    {
        std::cout << "destructor is called" << std::endl;
        delete[] m_str;
        m_str = 0;
    }

    B(const B& other)
    {
        AllocNCopy(other.m_str);

    }

    char *m_str;

    private:
    void AllocNCopy(const char *str)
    {
        char* temp = new char(strlen(str) + 1);

        memcpy(temp,str,strlen(str) + 1);

        m_str = temp;

    }
};

class A
{
public:
    A(B &b) : m_b(b) // fixed from original question
    {
        m_b = b;
    }

private:
    B &m_b;
};

void foo(B b)
{
    cout << b.m_str << endl;
}

int main()
{
    B b1("hi");
    foo(b1);

    vector<int> vec;

    vec.push_back(3);

    int &ref = vec[0];

    cout << ref << endl;

    for (int i = 0; i < 20; i++)
    {
        vec.push_back(i);
    }

    cout << ref << endl;

    return (0);
}