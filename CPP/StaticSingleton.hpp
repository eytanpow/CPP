#pragma once

class StaticSingleton
{

public:
    StaticSingleton(const StaticSingleton &other) = delete;
    StaticSingleton &operator=(const StaticSingleton &other) = delete;

    // if you return a pointer you should make the destructor pirvate
    //  if not anyone can call delete
    static StaticSingleton *getInstance()
    {
        static StaticSingleton instance;
        return &instance;
    }

private:
    StaticSingleton() {}
    ~StaticSingleton() {};
};
