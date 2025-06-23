#include "find_issues.hpp"

int main()
{
    Derived d1(5, 'x');
    Derived d2(3, 'w');

    Base *b1 = &d1;

    b1->foo();
    b1->bar();

    Base *b2 = &d2;

    *b2 = *b1;

    b2->foo();

    d2.bar();

    return 0;
}

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