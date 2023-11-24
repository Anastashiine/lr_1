#pragma once
#include <iostream>
#include <string>
#include <fstream>
class CStation
{
    int id;
public:
    static int MaxID;
    std::string name;
    int workshops;
    int working;
    double performance;
    CStation();
    int GetCSID() const;

friend std::ostream& operator << (std::ostream& out, const CStation& station);
friend std::istream& operator >> (std::istream& in, CStation& station);
friend std::ifstream& operator >> (std::ifstream& fin, CStation& station);
friend std::ofstream& operator << (std::ofstream& fout, const CStation& station);
};