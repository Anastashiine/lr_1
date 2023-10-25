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
int getrepair()
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
int check()
{
    int x;
    while ((cin >> x).fail() || x <= 0)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Please, try again: ";
    }
    return x;
}
int checkcond(int max)
{
    int x;
    while ((cin >> x).fail() || x < 0 || x > max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Please, try again: ";
    }
    return x;
}
Pipe AddPipe()
{
    Pipe p;
    cout << "Please, enter the name of the pipe: ";
    p.name = GetLine();
    cout << "Please, enter pipe length: ";
    p.length = check();
    cout << "Please, enter pipe diameter: ";
    p.diametr = check();
    cout << "Please, enter '1', if the pipe is under repair, otherwise enter '0': ";
    p.repair = getrepair();
    return p;
}
CS AddCS()
{
    CS station;
    cout << "Please, enter the name of the compressor station: ";
    station.name = GetLine();
    cout << "Please, enter the number of workshops: ";
    station.workshops = check();
    cout << "Please, enter the number of workshops in working: ";
    station.working = checkcond(station.workshops);
    cout << "Please, enter performance indicator (0 - 100): ";
    station.performance = checkcond(100);
    return station;
}
void OutputPipe(const Pipe& p)
{
    if (p.name != "")
    {
        cout << "Name: " << p.name << endl
            << "Length: " << p.length << endl
            << "Diametr: " << p.diametr << endl
            << "Repair: " << p.repair << endl;
    }
    else
    {
        cout << "Add pipe!" << endl;
    }
}
void OutputCS(const CS& station)
{
    if (station.name != "")
    {
        cout << "Name: " << station.name << endl
            << "Number of workshops: " << station.workshops << endl
            << "Workshops in working: " << station.working << endl
            << "Performance indicator: " << station.performance << endl;
    }
    else
    {
        cout << "Add compressor station!" << endl;
    }
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
        station.working = checkcond(station.workshops);
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
            p = AddPipe();
            OutputPipe(p);
            break;
        }
        case 2:
        {
            station = AddCS();
            OutputCS(station);
            break;
        }
        case 3:
        {
            cout << "Pipe information: " << endl;
            OutputPipe(p);
            cout << "Compressor station information: " << endl;
            OutputCS(station);
            break;
        }
        case 4:
        {
            EditPipe(p);
            OutputPipe(p);
            break;
        }
        case 5:
        {
            EditCS(station);
            OutputCS(station);
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
            OutputPipe(p);
            OutputCS(station);
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