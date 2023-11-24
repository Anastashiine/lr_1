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
string FName() 
{
    string fname;
    cout << "Enter a file name: ";
    GetLine(cin, fname);
    return fname;
}
void SavePipe(ofstream& fout, const CPipe& p)
{
    if (p.name != "")
    {
        fout << p;
    }
}
void SaveCS(ofstream& fout, const CStation& station)
{
    if (station.name != "")
    {
        fout << station;
    }
}
/*void SaveInf(const Pipe& p, const CS& station)
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
}*/
CPipe LoadPipe(ifstream& fin)
{
    CPipe p;
    fin >> p;
    return p;
}
CStation LoadCS(ifstream& fin)
{
    CStation station;
    fin >> station;
    return station;
}
void EditPipe(unordered_map<int, CPipe>& MapPipe)
{
    cout << "Enter ID of the pipes for editing: " << endl;
    int id;
    id = check_cond(MapPipe.size());
    if (CheckID(MapPipe, id))
    {
        MapPipe[id].repair = !(MapPipe[id].repair);
    }
    else
    {
        cout << "Pipe with such ID was not found";
    }
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
void DeletePipe(unordered_map<int, CPipe>& MapPipe)
{
    cout << "Please, enter a pipe's ID for deleting: ";
    int id;
    id = check_cond(MapPipe.size());
    if (CheckID(MapPipe, id))
    {
        MapPipe.erase(id);
    }
    else
    {
        cout << "Pipe with such ID was not found";
    }
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
bool CheckByName(const CPipe& MapPipe, string param) 
{
    return (MapPipe.name.find(param) != string::npos);
}
bool CheckByRepair(const CPipe& MapPipe, bool param) 
{
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
    param = ((MapCS.workshops - MapCS.working) * 100) / MapCS.workshops;
    return param;
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
        cout << "Station not found" << endl;
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
            CPipe p;
            cin >> p;
            cout << p;
            break;
        }
        case 2:
        {
            CStation station;
            cin >> station;
            cout << station;
            break;
        }
        case 3:
        {
            cout << "Pipes information: " << endl;
            for (auto& [id, p] : MapPipe)
            {
                cout << p << endl;
            }
            cout << "Compressor stations information: " << endl;
            for (auto& [id, station] : MapCS)
            {
                cout << station << endl;
            }
            break;
        }
        case 4:
        {
            EditPipe(MapPipe);
            break;
        }
        case 5:
        {
            EditCS(MapCS);
            break;
        }
        case 6:
        {
            ofstream fout;
            string  fname;
            cout << "Enter a file name: ";
            GetLine(cin, fname);
            fout.open(fname, ios::out);
            if (fout.is_open()) 
            {
                fout << MapPipe.size() << endl;
                for (auto& [id, p] : MapPipe) 
                {
                    SavePipe(fout, p);
                }
                fout << MapCS.size() << endl;
                for (auto& [id, station] : MapCS) 
                {
                    SaveCS(fout, station);
                }
                fout.close();
            }
            break;
        }
        case 7:
        {
            ifstream fin;
            fin.open(FName(), ios::in);
            if (fin.is_open()) 
            {
                int count_p;
                fin >> count_p;
                while (count_p--) 
                {
                    CPipe p = LoadPipe(fin);
                    MapPipe.insert(pair{p.GetPipeID(), p});
                    p.MaxID = p.GetPipeID();

                }
                int count_s;
                fin >> count_s;
                while (count_s--) 
                {
                    CStation station = LoadCS(fin);
                    MapCS.insert(pair{station.GetCSID(), station});
                    station.MaxID = station.GetCSID();
                }
                fin.close();
            }
            break;
        }
        case 8:
        {
            string name;
            cout << "Input name of the pipe: ";
            GetLine(cin, name);
            for (int id: FindPipesByFilter(MapPipe, CheckByName, name)) 
            {
                cout << "ID: " << id;
                cout << MapPipe[id];
            }
            break;
        }
        case 9:
        {
            cout << "Input pipe in repair or not: ";
            bool flag = check_cond(false, true);
            for (int id: FindPipesByFilter(MapPipe, CheckByRepair, flag)) 
            {
                cout << MapPipe[id];
            }
            break;
        }
        case 10:
        {
            DeletePipe(MapPipe);
            break;
        }
        case 11:
        {
            break;
        }
        case 12:
        {
            string name;
            cout << "Input name of the station: ";
            GetLine(cin, name);
            for (int id: FindCSByFilter(MapCS, CheckByName, name))
            {
                cout << MapCS[id];
            }
            break;
        }
        case 13:
        {
            cout << "Input percent of unworking stations: ";
            double per = check_cond(100.0);
            for (int id: FindCSByFilter(MapCS, CheckByUnworkingWorkshops, per))
            {
                cout << MapCS[id];
            }
            break;
        }
        case 14:
        {
            DeleteCS(MapCS);
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