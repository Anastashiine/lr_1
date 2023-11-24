#pragma once
#include <iostream>
#define GetLine(in, st) getline(in>>std::ws, st); cout << st << endl;
#define LoadLine(in, st) getline(in>>std::ws, st); 
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
