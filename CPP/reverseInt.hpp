#pragma once

#include <iostream>
#include "math.h"

using namespace std;

class reveseInt
{
public:
    int reverse(int x)
    {
        int num = 0;
        int max = pow(2, 31) - 1;
        int min = pow(-2, 31);
        while (x != 0)
        {
            int digit = x % 10;
            if (num > max / 10 ||
                num < min / 10)
            {
                return 0;
            }

            num = num * 10 + digit;
            //  cout << "num is " << num << endl;
            x /= 10;
            //  cout << "x is " << x << endl;
        }

        return num;
    }
};