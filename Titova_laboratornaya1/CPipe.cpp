#include "CPipe.h"
#include "utils.h"
using namespace std;

int CPipe::MaxID = 0;
istream& operator >> (istream& in, CPipe& p)
{
    cout << "Please, enter the name of the pipe: ";
    p.name = GetLine();
    cout << "Please, enter pipe length: ";
    p.length = check_cond(10000);
    cout << "Please, enter pipe diameter: ";
    p.diametr = check_cond(2000);
    cout << "Please, enter '1', if the pipe is under repair, otherwise enter '0': ";
    p.repair = getrepair();
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
