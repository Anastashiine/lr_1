#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void PrintMenu()
{
    cout << "1. Add pipe" << endl
        << "2. Add compressor station" << endl
        << "3. View all objects" << endl
        << "4. Edit pipe" << endl
        << "5. Edit compressor station" << endl
        << "6. Save to file" << endl
        << "7. Load from file" << endl
        << "0. Exit" << endl;
}
struct Pipe
{
    string name;
    double length;
    double diametr;
    bool repair;
};
struct CS
{
    string name;
    int workshops;
    int working;
    double performance;
};
bool getrepair()
{
    bool rep;
    while (!(cin >> rep))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Wrong action! Please, try again." << '\n';
    }
    return rep;
}
string GetLine()
{
    string fname;
    getline(cin >> ws, fname);
    return fname;
}
template <typename T>
T check_cond(T max)
{
    T x;
    while ((cin >> x).fail() || x < 0 || x = 0 || x > max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Please, try again: ";
    }
    return x;
}
istream& operator >> (istream& in, Pipe& p)
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
ostream& operator << (ostream& out, const Pipe& p)
{
    if (p.name != "")
    {
        out << "Name: " << p.name << endl
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
istream& operator >> (istream& in, CS& station)
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
ostream& operator << (ostream& out, const CS& station)
{
    if (station.name != "")
    {
        out << "Name: " << station.name << endl
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
void SavePipe(const Pipe& p)
{
    ofstream fout;
    fout.open("Information.txt", ios::out);
    if (fout.is_open())
    {
        fout << "Information about pipe:" << endl
            << p.name << endl
            << p.length << endl
            << p.diametr << endl
            << p.repair << endl;
        fout.close();
    }
}
void SaveCS(const CS& station)
{
    ofstream fout;
    fout.open("Information.txt", ios::app);
    if (fout.is_open())
    {
        fout << "Information about CS:" << endl
            << station.name << endl
            << station.workshops << endl
            << station.working << endl
            << station.performance << endl;
        fout.close();
    }
}
void SaveInf(const Pipe& p, const CS& station)
{
    if ((p.name == "") && (station.name == ""))
        cout << "Add information" << endl;
    else
    {
        if (p.name != "")
            SavePipe(p);
        if (station.name != "")
            SaveCS(station);
    }
}
Pipe LoadPipe()
{
    Pipe p;
    ifstream fin;
    fin.open("Information.txt", ios::in);
    if (fin.is_open())
    {
        string st;
        while (getline(fin >> ws, st))
        {
            if (st == "Information about pipe:")
            {
                getline(fin, p.name);
                fin >> p.length;
                fin >> p.diametr;
                fin >> p.repair;
            }
        }
        fin.close();
    }
    return p;
}
CS LoadCS()
{
    CS station;
    ifstream fin;
    fin.open("Information.txt", ios::in);
    if (fin.is_open())
    {
        string st;
        while (getline(fin >> ws, st))
        {
            if (st == "Information about CS:")
            {
                getline(fin, station.name);
                fin >> station.workshops;
                fin >> station.working;
                fin >> station.performance;
            }
        }
        fin.close();
    }
    return station;
}
void EditPipe(Pipe& p)
{
    if (p.name != "")
    {
        cout << "Please, enter '1', if the pipe is under repair, otherwise enter '0': " << endl;
        p.repair = getrepair();
    }
}
void EditCS(CS& station)
{
    if (station.name != "")
    {
        cout << "Please, enter the number of working workshops: ";
        station.working = check_cond(station.workshops);
    }
}
int checkmenu()
{
    int i;
    while (!(cin >> i))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Wrong action! Please, try again." << endl;
    }
    return i;
}
int main()
{
    CS station;
    Pipe p;
    while (1)
    {
        PrintMenu();
        switch (checkmenu())
        {
        case 1:
        {
            cin >> p;
            cout << p;
            break;
        }
        case 2:
        {
            cin >> station;;
            cout << station;
            break;
        }
        case 3:
        {
            cout << "Pipe information: " << endl;
            cout << p;
            cout << "Compressor station information: " << endl;
            cout << station;
            break;
        }
        case 4:
        {
            EditPipe(p);
            cout << p;
            break;
        }
        case 5:
        {
            EditCS(station);
            cout << station;
            break;
        }
        case 6:
        {
            SaveInf(p, station);
            break;
        }
        case 7:
        {
            p = LoadPipe();
            station = LoadCS();
            cout << p;
            cout << station;
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
        {
            cout << "Wrong action! Please, try again." << endl;
        }
        }
    }
    return 0;
}