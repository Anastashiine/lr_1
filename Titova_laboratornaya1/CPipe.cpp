#include "CPipe.h"
#include "utils.h"
using namespace std;

int CPipe::MaxID = 0;
CPipe::CPipe()
{
    id = ++MaxID;
    name = "Unknown";
    length = 0.1;
    diametr = 50;
    repair = false;
}
int CPipe::GetPipeID() const
{
    return id;
}
istream& operator >> (istream& in, CPipe& p)
{
    cout << "Please, enter the name of the pipe: ";
    GetLine(in, p.name);
    cout << "Please, enter pipe length: ";
    p.length = check_cond(10000);
    cout << "Please, enter pipe diameter: ";
    p.diametr = check_cond(2000);
    cout << "Please, enter '1', if the pipe is under repair, otherwise enter '0': ";
    p.repair = check_bool(0, 1);
    return in;
}
ostream& operator << (ostream& out, const CPipe& p)
{
    if (p.name != "")
    {
        out << "ID: " << p.id << endl
            << "Name: " << p.name << endl
            << "Length: " << p.length << endl
            << "Diametr: " << p.diametr << endl
            << "Repair: " << p.repair << endl;
    }
    else
    {
        out << "Add pipe!" << endl;
    }
    return out;
}
std::ifstream& operator>>(std::ifstream& fin, CPipe& p)
{
    fin >> p.id;
    LoadLine(fin, p.name);
    fin >> p.length;
    fin >> p.diametr;
    fin >> p.repair;
    return fin;
}

std::ofstream& operator<<(std::ofstream& fout, const CPipe& p)
{
    fout << p.id << endl
        << p.name << endl
        << p.length << endl
        << p.diametr << endl
        << p.repair << endl;
    return fout;
}
