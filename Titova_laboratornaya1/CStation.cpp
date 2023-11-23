#include "CStation.h"
#include "utils.h"
using namespace std;
int CStation::MaxID = 0;
istream& operator >> (istream& in, CStation& station)
{
    cout << "Please, enter the name of the compressor station: ";
    station.name = GetLine();
    cout << "Please, enter the number of workshops: ";
    station.workshops = check_cond(1000);
    cout << "Please, enter the number of workshops in working: ";
    station.working = check_cond(station.workshops);
    cout << "Please, enter performance indicator (0 - 100): ";
    station.performance = check_cond(100);
    return in;
}
ostream& operator << (ostream& out, const CStation& station)
{
    if (station.name != "")
    {
        out << "ID: " << station.id << endl
            << "Name: " << station.name << endl
            << "Number of workshops: " << station.workshops << endl
            << "Workshops in working: " << station.working << endl
            << "Performance indicator: " << station.performance << endl;
    }
    else
    {
        out << "Add compressor station!" << endl;
    }
    return out;
}
