
/*
    fixed size buffer allow reader and writer work in parallel
    only one reader and writer each time
*/
#pragma once

#include <mutex>   //std::mutex
#include <cstddef> //size_t
#include <condition_variable>

namespace hrdxxx
{
    class CSem
    {
    public:
        CSem(size_t size) : counter(size), capacity(size) {};
        CSem(const CSem &other) = delete;
        CSem &operator=(const CSem &other) = delete;

        void acquire()
        {
            std::unique_lock lock(m);
            cv.wait(lock, [this]
                    { return counter > 0; });
            counter--;
        }

        void release()
        {
            std::unique_lock lock(m);
            if (counter == capacity)
            {
                return;
            }
            counter++;
            lock.unlock();
            cv.notify_all();
        }

    private:
        size_t counter;
        size_t capacity;
        std::mutex m;
        std::condition_variable cv;
    };

}