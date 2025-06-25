#include <string>
#include <unordered_map>
#include <iostream>

class Solution
{
public:
    int lengthOfLongestSubstring(std::string s)
    {
        int size = s.length();
        if(size == 0)
        {
            return 0;
        }
        int start = 0, end = 1;
        int length = 1;
        int currentLength = 1;
        std::unordered_map<char, int> map;
        map[s[start]] = start;


        while (end < size)
        {
            if (map.find(s[end]) == map.end())
            {
                map[s[end]] = end;
                end++;
                currentLength++;
            }
            else
            {
                map.erase(s[start]);
                if (currentLength > length)
                {
                    length = currentLength;
                }
                start++;
                currentLength = end - start;
            }
        }

        if (currentLength > length)
        {
            length = currentLength;
        }

        return length;
    }
};

int main()
{

    std::string s = "aaab";
    Solution myS;
    std::cout << myS.lengthOfLongestSubstring(s) << std::endl;

    return 0;
}