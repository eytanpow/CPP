//------------------------------ main.cpp ------------------------------
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <set>
#include "StaticSingleton.hpp"
#include "UnsafeSingleton.hpp"
#include "Producer_Consumer.hpp"
#include "Single_Element_in_a_Sorted_Array.hpp"
#include "reverseInt.hpp"

using namespace std;

void printAddressLoop1()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        cout << StaticSingleton::getInstance() << endl;
    }
}

void callSingleton(UnsafeSingleton **out)
{
    *out = UnsafeSingleton::getInstance();
}

void printAddressLoop2()
{
    const int THREAD_COUNT = 100;
    vector<thread> threads;
    vector<UnsafeSingleton *> ptrs(THREAD_COUNT, nullptr);

    // Start all threads
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        threads.emplace_back(callSingleton, &ptrs[i]);
    }

    // Join all threads
    for (auto &t : threads)
    {
        t.join();
    }

    // Collect all unique instance pointers
    set<UnsafeSingleton *> unique_ptrs(ptrs.begin(), ptrs.end());

    // Print the addresses
    // cout << "All singleton addresses seen by threads:\n";
    // for (auto ptr : unique_ptrs)
    // {
    //     cout << ptr << endl;
    // }

    if (unique_ptrs.size() > 1)
    {
        cout << "PROOF: Not thread safe! " << unique_ptrs.size() << " different instances created.\n";
    }
    else
    {
        //     cout << "All threads saw the same singleton instance.\n";
    }
}

void runStaticSingleton()
{
    thread t1(printAddressLoop1);
    thread t2(printAddressLoop1);
    t1.join(); // program never leaves these joins – press Ctrl-C to stop
    t2.join();
}

void runUnSafeSingleton()
{
    vector<thread> arr;
    for (int i = 0; i < 100; ++i)
    {
        arr.emplace_back(printAddressLoop2);
    }

    // Wait for all threads to finish
    for (auto &t : arr)
    {
        t.join();
    }
}

void producerConsumer()
{
    ProducerConsumer c;
    c.run();
}

void runSingleAlgo()
{
    SingleElement a;
    vector<int> v = {1, 2, 2, 3, 3};
    cout << a.singleNonDuplicate(v) << endl;
}

int main()
{
    // runUnSafeSingleton();
    // producerConsumer();
    // runSingleAlgo();
    reveseInt a;
    cout << a.reverse(pow(-2, 31)) << endl;
    cout << a.reverse(pow(2, 31) - 1) << endl;
}
