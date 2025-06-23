#include <iostream>

using namespace std;

class Base
{
public:
    Base(int i) : m_i(i), m_iptr(&m_i) {}

    virtual void foo() { cout << *(m_iptr) << endl; }

    virtual void bar() { cout << m_i << endl; }

protected:
    virtual ~Base() = 0;

private:
    int m_i;
    int *m_iptr;
};

inline Base::~Base() {};

class Derived : public Base
{
public:
    Derived(int i, char c) : Base(i), m_c(c), m_c2(c) {}
    void bar()
    {
        foo();
        Base::foo();
    }

private:
    void foo() { cout << m_c << endl; }
    char m_c, m_c2;
};

class OtherDerived : public Base
{
};

/*
    1. on line 12 what is the meaning of = 0;
    2. why is it possible, despite line 12, to instansiate variables d1 and d2
        on line 38 and 39;
    3. explain why line 19 is necessary; [inline Base::~Base{};]
    4. what are the implications of protected destructor;
    5. is there a destructor for? if so is it public or protected?
    6. on line 24, which is called firsr m_c(c), Base(i), or m_c2(c)?
    7. on line 42 the call foo() incokes the method of which line? Why?
    8. write a copy constructor dor class Derived.
    9. on line 32 what methods does the commpiler generate for class OtherDerived?
        implement them.
    10. why does class OtherDerived not compile?
    11. what does the program print?


*/