#pragma once

class UnsafeSingleton
{

public:
    UnsafeSingleton(const UnsafeSingleton &other) = delete;
    UnsafeSingleton &operator=(const UnsafeSingleton &other) = delete;

    // if you return a pointer you should make the destructor pirvate
    //  if not anyone can call delete
    static UnsafeSingleton *getInstance()
    {
        if (nullptr == m_ptr)
        {
            m_ptr = new UnsafeSingleton();
        }
        return m_ptr;
    }

private:
    UnsafeSingleton() {}
    ~UnsafeSingleton() {};

    static UnsafeSingleton *m_ptr;
};

UnsafeSingleton *UnsafeSingleton::m_ptr = nullptr;
