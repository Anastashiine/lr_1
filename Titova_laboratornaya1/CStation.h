#pragma once
#include <iostream>
#include <string>
#include <fstream>
class CStation
{
    int id;
    static int MaxID;
    int workshops;
    int working;
    int start;
    int stop;
public:
    std::string name;
    double performance;
    CStation();
    int GetCSID() const;
    static void ResetMaxID();
    void SetMaxID() const;
    void start_wk();
    void stop_wk();
    void increase_start();
    void increase_stop();
    void dicrease_strat();
    void dicrease_stop();
    int get_wk() const;
    int get_working() const;
    int get_start() const;
    int get_stop() const;

friend std::ostream& operator << (std::ostream& out, const CStation& station);
friend std::istream& operator >> (std::istream& in, CStation& station);
friend std::ifstream& operator >> (std::ifstream& fin, CStation& station);
friend std::ofstream& operator << (std::ofstream& fout, const CStation& station);
};