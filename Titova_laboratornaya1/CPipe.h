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
    CPipe();
    int GetPipeID() const;
    int CS_entrance;
    int CS_exit;

friend std::ostream& operator << (std::ostream& out, const CPipe& p);
friend std::istream& operator >> (std::istream& in, CPipe& p);
friend std::ifstream& operator >> (std::ifstream& fin, CPipe& p);
friend std::ofstream& operator << (std::ofstream& fout, const CPipe&p);
};