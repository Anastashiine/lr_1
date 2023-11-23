#pragma once
#include <iostream>
template <typename T>
T check_cond(T max)
{
    T x;
    while ((std::cin >> x).fail() || x <= 0 || x > max)
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Please, try again: ";
    }
    return x;
}
