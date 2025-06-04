#pragma once


#include <iostream>
#include <vector>
#include <list>
#include <algorithm> // for std::make_heap, std::pop_heap, etc.


    using namespace  std;

template <typename T>
void print_single(T&& arg)
{
    std::cout << std::forward<T>(arg);
}

template <typename... Args>
void print(Args&&... args)
{
    (std::cout << ... << args) << std::endl;
}

