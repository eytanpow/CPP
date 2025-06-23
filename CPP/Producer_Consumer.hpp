
#pragma once

#include <mutex>
#include <thread>
#include <iostream>

using namespace std;

class ProducerConsumer

{

public:
    mutex counterLock;
    mutex resourceLock;
    thread readerThread[5], writerThread;

    int counter = 0;
    static int shared_value;

    void run(chrono::seconds duration = chrono::seconds(10))
    {
        const auto deadline = chrono::steady_clock::now() + duration;

        /* launch writer first (it may block on resourceLock) */
        writerThread = thread(&ProducerConsumer::writerFunction, this, deadline);

        /* launch 5 reader threads */
        for (int i = 0; i < 5; ++i)
        {
            readerThread[i] = thread(&ProducerConsumer::ReaderFunc, this, deadline);
        }

        /* wait for all threads to finish */
        writerThread.join();
        for (int i = 0; i < 5; ++i)
        {
            readerThread[i].join();
        }
    }

private:
    void ReaderFunc(chrono::steady_clock::time_point deadline)
    {
        while (chrono::steady_clock::now() < deadline)
        {
            counterLock.lock();
            if (++counter == 1)
            {
                resourceLock.lock();
            }
            counterLock.unlock();

            cout << "[R] shared value is " << shared_value << endl;
            if (--counter == 0)
            {
                resourceLock.unlock();
            }
            counterLock.unlock();
            this_thread::sleep_for(chrono::milliseconds(650));
        }
    }

    void writerFunction(chrono::steady_clock::time_point deadline)
    {
        while (chrono::steady_clock::now() < deadline)
        {
            resourceLock.lock();
            cout << "[W] shared value is  " << shared_value << endl;
            ++shared_value;
            resourceLock.unlock();
            this_thread::sleep_for(chrono::milliseconds(450));
        }
    }
};

int ProducerConsumer::shared_value = 0;
