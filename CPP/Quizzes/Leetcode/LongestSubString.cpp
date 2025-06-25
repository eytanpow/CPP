#include <string>
#include <unordered_map>
#include <iostream>

// Intuition
// <!need somehow to save what letters already passed on>
// + substring is kind of two pointers

// # Approach
// <!-- two -->

// # Complexity
// - Time complexity:
// <!O(n)>

// - Space complexity:
//  <-- $$O(1) -->


class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        int size = s.length();
        int start = 0, end = 0;
        int length = 0;
        int currentLength = 0;
        std::unordered_map<char, int> map;

        while (end < size)
        {
            char c = s[end];
            if (map.find(c) == map.end() || map[c] < start)
            {
                map[c] = end;
                end++;
                currentLength++;
            }
            else
            {
                // map.erase(s[start]);
                start = map[c] + 1;
                map[c] = end;

                if (currentLength > length)
                {
                    length = currentLength;
                }
                end++;
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
```

int main()
{

    std::string s = "aaaabc";
    Solution myS;
    std::cout << myS.lengthOfLongestSubstring(s) << std::endl;

    return 0;
}