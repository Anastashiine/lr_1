#pragma once
#include <iostream>
#include <string>
#include <fstream>
class CPipe
{
    int id;
public:
    static int MaxID;
    std::string name;
    double length;
    int diametr;
    bool repair;

friend std::ostream& operator << (std::ostream& out, const CPipe& p);
friend std::istream& operator >> (std::istream& in, CPipe& p);
};