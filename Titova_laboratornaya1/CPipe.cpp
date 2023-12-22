#include "CPipe.h"
#include "utils.h"
using namespace std;

int CPipe::MaxID = 0;
void CPipe::ResetMaxID()
{
    MaxID = 0;
}

void CPipe::SetMaxID() const
{
    MaxID = id;
}
CPipe::CPipe()
{
    id = ++MaxID;
    name = "Unknown";
    length = 0.1;
    diametr = 500;
    repair = false;
    CS_entrance = -1;
    CS_exit = -1;
}
int CPipe::GetPipeID() const
{
    return id;
}
CPipe CPipe::AddPipe(int d)
{
    CPipe p;
    cout << "Type a pipeline name: ";
    GetLine(cin, p.name);
    cout << "Enter a length: ";
    p.length = check_cond(1000);
    if (d > 0)
        p.diametr = d;
    else
    {
        cout << "Enter a d: ";
        p.diametr = check_diameter();
    }
    p.repair = false;
    return p;
}
void CPipe:: add_cs_entrance(int id)
{
    CS_entrance = id;
}

void CPipe::add_cs_exit(int id)
{
    CS_exit = id;
}
int CPipe::get_diameter() const
{
    return diametr;
}

double CPipe::get_length() const
{
    return length;
}

int CPipe::add_pipe_entrance() const
{
    return CS_entrance;
}

int CPipe::add_pipe_exit() const
{
    return CS_exit;
}

istream& operator >> (istream& in, CPipe& p)
{
    cout << "Please, enter the name of the pipe: ";
    GetLine(in, p.name);
    cout << "Please, enter pipe length: ";
    p.length = check_cond(10000);
    cout << "Please, enter pipe diameter: ";
    p.diametr = check_diameter();
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
            << "Repair: " << p.repair << endl
            << "Input CS ID: " << p.CS_entrance << endl
            << "Output CS ID: " << p.CS_exit << endl;
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
    fin >> p.CS_entrance;
    fin >> p.CS_exit;
    return fin;
}

std::ofstream& operator<<(std::ofstream& fout, const CPipe& p)
{
    fout << p.id << endl
        << p.name << endl
        << p.length << endl
        << p.diametr << endl
        << p.repair << endl
        << p.CS_entrance << endl
        << p.CS_exit << endl;
    return fout;
}
