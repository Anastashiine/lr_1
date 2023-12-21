#include "CStation.h"
#include "utils.h"
using namespace std;
int CStation::MaxID = 0;
CStation::CStation()
{
    id = ++MaxID;
    name = "Unknown";
    workshops = 1;
    working = 0;
    performance = 0;
    start = 0;
    stop = 0;
}
int CStation::GetCSID() const
{
    return id;
}
istream& operator >> (istream& in, CStation& station)
{
    cout << "Please, enter the name of the compressor station: ";
    GetLine(in, station.name);
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
            << "Performance indicator: " << station.performance << endl
            << "Start CS:" <<station.start << endl
            << "End CS:" << station.stop << endl;
    }
    else
    {
        out << "Add compressor station!" << endl;
    }
    return out;
}
std::ifstream& operator >> (std::ifstream& fin, CStation& station)
{
    fin >> station.id;
    LoadLine(fin, station.name);
    fin >> station.workshops;
    fin >> station.working;
    fin >> station.performance;
    fin >> station.start;
    fin >> station.stop;
    return fin;
}

std::ofstream& operator << (std::ofstream& fout, const CStation& station)
{
    fout << station.id << endl
        << station.name << endl
        << station.workshops << endl
        << station.working << endl
        << station.performance << endl
        << station.start << endl
        << station.stop << endl;
    return fout;
}
