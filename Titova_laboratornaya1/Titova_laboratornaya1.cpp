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
template <typename type>
bool CheckID(const unordered_map<int, type>& x, const int& id) 
{
    return (x.contains(id));
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
void EditPipe(unordered_map<int, CPipe>& MapPipe, const int& id)
{
    MapPipe[id].repair = !(MapPipe[id].repair);
}
void EditCS(unordered_map<int, CStation>& MapCS)
{
    cout << "Please, enter a station's ID for editing: ";
    int id;
    id = check_cond(MapCS.size());
    if (CheckID(MapCS, id))
    {
        string solution;
        cout << "Please, enter "start" if you want to add a working workshop and "stop" if you want to stop a working workshop: ";
        cin >> solution;
        if (solution == "start" && check_cond(MapCS[id].workshops))
        {
            MapCS[id].working++;
        }
        if (solution == "stop" && check_cond(MapCS[id].working))
        {
            MapCS[id].working--;
        }
        else
        {
            cout << "Station with such ID was not found";
        }
    }
}
void DeletePipe(unordered_map<int, CPipe>& MapPipe, const int& id)
{
    MapPipe.erase(id);
}
void DeleteCS(unordered_map<int, CStation>& MapCS)
{
    cout << "Please, enter a station's ID for deleting: ";
    int id;
    id = check_cond(MapCS.size());
    if (CheckID(MapCS, id))
    {
        MapCS.erase(id);
    }
    else
    {
        cout << "Station with such ID was not found";
    }
}
template <typename type>
using PipeFilter = bool(*)(const CPipe& MapPipe, type param);
bool CheckByName(const CPipe& MapPipe, string param) {
    return (MapPipe.name.find(param) != string::npos);
}
bool CheckByRepair(const CPipe& MapPipe, bool param) {
    return (MapPipe.repair == param);
}
template <typename type>
unordered_set<int> FindPipesByFilter(const unordered_map<int, CPipe>& MapPipe, PipeFilter<type> f, type param) 
{
    unordered_set<int> res;
    for (auto& [id, p]: MapPipe) 
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
using CSFilter = bool(*)(const CStation& MapCS, type param);
bool CheckByName(const CStation& MapCS, string param)
{
    return (MapCS.name.find(param) != string::npos);
}
bool CheckByUnworkingWorkshops(const CStation& MapCS, double param) 
{
    return (double((MapCS.workshops - MapCS.working) * 100) / MapCS.workshops) >= param;
}
template <typename type>
unordered_set<int> FindCSByFilter(const unordered_map<int, CStation>& MapCS, CSFilter<type> f, type param)
{
    unordered_set<int> res;
    for (auto& [id, station] : MapCS) 
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
    unordered_map <int, CPipe> MapPipe;
    unordered_map <int, CStation> MapCS;
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