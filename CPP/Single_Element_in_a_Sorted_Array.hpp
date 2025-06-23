
#pragma once

#include <vector>
#include <thread>
#include <iostream>

using namespace std;



class SingleElement
{

public:
    int singleNonDuplicate(vector<int> &nums)
    {
        int start = 0, end = nums.size() - 1;
        int middle = (start + end) / 2;

        if (nums.size() == 1)
        {
            return nums[0];
        }
        while (start != end)
        {
            middle = (start + end) / 2;
            if (nums[middle] != nums[middle + 1] &&
                nums[middle] != nums[middle - 1])
            {
                return nums[middle];
            }

            if (nums[middle] == nums[middle + 1])
            {
                if ((middle + 1) % 2 == 0)
                {
                    end = middle;
                }
                else
                {
                    start = middle;
                }
            }
            if (nums[middle] == nums[middle - 1])
            {
                if ((middle) % 2 == 0)
                {
                    end = middle;
                }
                else
                {
                    start = middle + 1;
                }
            }
        }

        return nums[start];
    }
};

/*
    if the array is  perfect only pairs of numbers (array is sorted)
    the first in the pair will start at even index
    1. go to the middle if it is even -> it should be the first in the  pair if
       not make it even.
       2. after middle is even check if it is first in the pair.
            2.1 if it is the first in the pair so the array is broken 
                after midle +2
            2.2 otherwise the array was broken before or in the middle
                adjust the end to b the middle

*/

/*******************GPT SOLUTION ****************************************/
/*
class SingleElement
{
public:
    int singleNonDuplicate(vector<int> &nums)
    {
        int start = 0;
        int end = nums.size() - 1;

        while (start < end)
        {
            int middle = (start + end ) / 2;

            // Ensure we always point to the first in the pair
            if (middle % 2 == 1)
            {
                --middle;
            }

            if (nums[middle] == nums[middle + 1])
            {
                // The unique element is after this pair
                start = middle + 2;
            }
            else
            {
                // The unique element is at or before this index
                end = middle;
            }
        }

        return nums[start];
    }
};


*/