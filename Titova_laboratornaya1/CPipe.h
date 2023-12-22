#pragma once
#include <iostream>
#include <string>
#include <fstream>
class CPipe
{
    int id;
    static int MaxID;
    double length;
    int diametr;
    int CS_entrance;
    int CS_exit;
public:
    std::string name;
    bool repair;
    CPipe();
    int GetPipeID() const;
    static void ResetMaxID();
    void SetMaxID() const;
    static CPipe AddPipe(int d = 0);
    void add_cs_entrance(int id = -1);
    void add_cs_exit(int id = -1);
    int get_diameter() const;
    double get_length() const;
    int add_pipe_entrance() const;
    int add_pipe_exit() const;

friend std::ostream& operator << (std::ostream& out, const CPipe& p);
friend std::istream& operator >> (std::istream& in, CPipe& p);
friend std::ifstream& operator >> (std::ifstream& fin, CPipe& p);
friend std::ofstream& operator << (std::ofstream& fout, const CPipe&p);
};