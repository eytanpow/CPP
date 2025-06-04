
#include "utils.hpp"

void ConnectRopesWithHeap(std::vector<int> vec)
{
    std::make_heap(vec.begin(), vec.end(), std::greater<int>()); // MIN-HEAP
    for (int i : vec)
    {
        print(i);
    }
    print("finisshe printing vec");

    int f, s;
    while (vec.size() > 1)
    {
        f = vec.front();
        vec.erase(vec.begin());

        s = vec.front();
        vec.erase(vec.begin());

        print("sum ", f, " and ", s);

        if (vec.empty() == false)
        {
            vec.push_back(f + s);
        }
        else
        {
            break;
        }

        // Push result back in
        std::make_heap(vec.begin(), vec.end(), std::greater<int>());
    }
    print("final sum is ", (f + s));
}
