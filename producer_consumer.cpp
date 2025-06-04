#include "utils.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

list<int> myList = {10, 20, 30};
int list_size = 5;
int counter = 0;
int spin_lock = 1;
std::mutex mLock;

void addToList_SpinLock()
{
    while (1)
    {
        while (spin_lock)
        {
            if (myList.size() > 5)
            {
                break;
            }

            myList.push_front(counter);
            print("pushed ", counter, "\n");
            this_thread::sleep_for(chrono::milliseconds(250));

            counter++;
        }
        spin_lock = 0;
    }
}

void removeFromList_SpinLock()
{
    while (1)
    {
        while (myList.size() != 0)
        {
            mLock.lock();
            int val = myList.front();
            myList.pop_front();
            print("removed ", val, "\n");
            //   this_thread::sleep_for(chrono::milliseconds(250));            }
            mLock.unlock();
        }
    }
}

void addToList_Mutex()
{

    while (1)
    {
        mLock.lock();
        while (myList.size() < 5)
        {

            myList.push_front(counter);
            print("pushed ", counter, "\n");
            ++counter;
            //  this_thread::sleep_for(chrono::milliseconds(250));
        }
        mLock.unlock();
    }
}

void removeFromList_Mutex()
{
    while (1)
    {

        while (myList.size() != 0)
        {
            // mLock.lock();
            int val = myList.front();
            myList.pop_front();
            print("removed ", val, "\n");
            //   this_thread::sleep_for(chrono::milliseconds(250));
            // mLock.unlock();
        }
    }
}

int producerConsumer()
{
    // thread t1(removeFromList_SpinLock);
    // thread t2(addToList_SpinLock);

    thread t1(removeFromList_Mutex);
    thread t2(addToList_Mutex);
    thread t3(addToList_Mutex);
    thread t4(addToList_Mutex);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}