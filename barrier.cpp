#include "utils.hpp"
#include <iostream>
#include <semaphore.h>
#include <thread>
#include <mutex>
#include <condition_variable>

list<int> myList = {10, 20, 30};
int list_size = 5;
int counter = 0;
constexpr int numConsumers = 10;
int arr[numConsumers] = {0};
std::mutex mLock;
condition_variable cv;
sem_t sem;

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


void Produce()
{
    while (1)
    {

        mLock.lock();
        for(int i = 0; i < numConsumers; i++)
        {
            arr[i] = i;
        }

    std::unique_lock<std::mutex> lock(mLock);
          cv.wait(lock, []{ 
          int value;);
          return value <= 0; });
    
        
    }
}

int producerConsumer()
{
    // thread t1(removeFromList_SpinLock);
    // thread t2(addToList_SpinLock);

    sem_init(&sem,0,numConsumers);
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