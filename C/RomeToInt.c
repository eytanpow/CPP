#include <stdio.h>
#include <stdlib.h>

char *intToRoman(int num)
{
    char arr[91] = {0};
    int total_count = 0;

    while (num > 1000)
    {
        arr['M']++;
        num -= 1000;
        total_count++;
    }

    while (num > 500)
    {
        arr['D']++;
        num -= 500;
        total_count++;
    }

    while (num > 100)
    {
        arr['C']++;
        num -= 100;
        total_count++;
    }

    while (num > 50)
    {
        arr['L']++;
        num -= 50;
        total_count++;
    }

    while (num > 10)
    {
        arr['X']++;
        num -= 10;
        total_count++;
    }

    char *ans = (char *)malloc((total_count + 1) * sizeof(char));

    for (int i = 0; i < total_count; i++)
    {
        while (arr['M'] > 0)
        {
            ans[i] = 'M';
            i++;
            arr['M']--;
        }
    }
    ans[total_count] = '\0';
    return ans;
}