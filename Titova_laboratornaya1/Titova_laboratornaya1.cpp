#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "CPipe.h"
#include "CStation.h"
#include "utils.h"
#include <unordered_set>
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
        << "8. Find pipes by name" << endl
        << "9. Find a pipe in repair " << endl
        << "10. Delete a pipe" << endl
        << "11. Pack editing of pipes" << endl
        << "12. Find compressor stations by name" << endl
        << "13. Find a compressor station by percent of not working workshops" << endl
        << "14. Delete a compressor station" << endl
        << "0. Exit" << endl;
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
bool getrepair()
{
    bool rep;
    while (!(cin >> rep))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Wrong action! Please, try again." << endl;
    }
    return rep;
}
string GetLine()
{
    string fname;
    getline(cin >> ws, fname);
    return fname;
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
        p.repair=getrepair();
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
template <typename type>
using PipeFilter = bool(*)(const CPipe& p, type param);
bool CheckByName(const CPipe& pipe, string param) {
    return (p.name.find(param) != string::npos);
}
bool CheckByRepair(const CPipe& pipe, bool param) {
    return (p.repair == param);
}
template <typename type>
unordered_set<int> FindPipesByFilter(const unordered_map<int, CPipe>& pipes, PipeFilter<type> f, type param) 
{
    unordered_set<int> res;
    for (auto& [id, p]: pipes) 
    {
        if (f(p, param)) 
        {
            res.insert(id);
        }
    }
    if (!(size(res))) 
    {
        cout << "Pipe not found" << endl;
    }
    return res;
}
template <typename type>
using CSFilter = bool(*)(const CStation& station, type param);
bool CheckByName(const CStation& station, string param) {
    return (station.name.find(param) != string::npos);
}
bool CheckByUnworkingWorkshops(const CStation& station, double param) {
    return (double((station.workshops - station.working) * 100) / station.workshops) >= param;
}
template <typename type>
unordered_set<int> FindCSByFilter(const unordered_map<int, CStation>& stations, CSFilter<type> f, type param) {
    unordered_set<int> res;
    for (auto& [id, station] : stations) 
    {
        if (f(station, param)) 
        {
            res.insert(id);
        }
    }
    if (!(size(res))) 
    {
        cout << "Stations not found" << endl;
    }
    return res;
}
int main()
{
    unordered_map <int, Pipe> MapPipe;
    unordered_map <int, CS> MapCS;
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
            cin >> station;
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