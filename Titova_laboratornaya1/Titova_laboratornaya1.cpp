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
        << "15. Connect pipes" << endl
        << "16. Disconnect pipes" << endl
        << "17. Sort the network" << endl
        << "18. View the network" << endl
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
    return (x.find(id) != x.end());
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
void EditPipe(unordered_map<int, CPipe>& MapPipe, const int& id)
{
    if (MapPipe[id].CS_entrance == -1)
    {
        MapPipe[id].repair = !(MapPipe[id].repair);
    }
    else
    {
        cout << "This pipe is in the network, you can't use it" << endl;
    }
}
void EditCS(unordered_map<int, CStation>& MapCS)
{
    cout << "Please, enter a station's ID for editing: ";
    int id;
    id = check_cond(MapCS.size());
    if (CheckID(MapCS, id))
    {
        if (MapCS[id].start == 0 && MapCS[id].stop == 0)
        {
            string solution;
            cout << "Please, enter 'start' if you want to add a working workshop and 'stop' if you want to stop a working workshop: ";
            cin >> solution;
            if (solution == "start" && check_cond(MapCS[id].workshops))
            {
                MapCS[id].working++;
            }
            if (solution == "stop" && check_cond(MapCS[id].working))
            {
                MapCS[id].working--;
            }
            cerr << solution << endl;
        }
        else
        {
            cout << "This CS is in the network, you can't use it";
        }
    }
    else
    {
        cout << "Pipe with such ID was not found" << endl;
    }
}
void DeletePipe(unordered_map<int, CPipe>& MapPipe, const int& id)
{
    if (MapPipe[id].CS_entrance == -1)
    {
        MapPipe.erase(id);
    }
    else
    {
        cout << "This pipe is in the network, you can't use it" << endl;
    }
}
void DeleteCS(unordered_map<int, CStation>& MapCS)
{
    cout << "Please, enter a station's ID for deleting: ";
    int id;
    id = check_cond(MapCS.size());
    if (CheckID(MapCS, id))
    {
        if (MapCS[id].start == 0 && MapCS[id].stop == 0)
        {
            MapCS.erase(id);
        }
        else
        {
            cout << "This CS is in the network, you can't use it";
        }
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
    for (auto& i: MapPipe) 
    {
        if (f(i.second, param))
        {
            res.insert(i.first);
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
    for (auto& i : MapCS) 
    {
        if (f(i.second, param))
        {
            res.insert(i.first);
        }
    }
    if (!(size(res))) 
    {
        cout << "Station not found" << endl;
    }
    return res;
}
void PackMenu()
{
    cout << "1. Find pipes by name" << endl;
    cout << "2. Find pipes by repair" << endl;
}
void PrintFoundPipes(const int& id, unordered_map<int, CPipe>& MapPipe)
{
    cout << MapPipe[id];
}
unordered_set<int> PackEdit(unordered_map<int, CPipe>& MapPipe)
{
    unordered_set<int> PID{};
    PackMenu();
    switch (checkmenu())
    {
    case 1:
    {
        string name;
        cout << "Input pipe name for searching: ";
        GetLine(cin, name);
        for (int id : FindPipesByFilter(MapPipe, CheckByName, name))
        {
            PrintFoundPipes(id, MapPipe);
            PID.insert(id);
        }
        break;
    }
    case 2:
    {
        bool flag;
        cout << "Input pipe in repair or not: ";
        flag = check_bool(0, 1);
        for (int id : FindPipesByFilter(MapPipe, CheckByRepair, flag))
        {
            PrintFoundPipes(id, MapPipe);
            PID.insert(id);
        }
        break;
    }
    }
    return PID;
}

void EditMenu()
{
    cout << "1. Select pipes by ID" << endl
        << "2. Edit all found pipes" << endl
        << "3. Delete all found pipes" << endl
        << "4. Show all pipes" << endl
        << "0. Return to main menu" << endl;
}

unordered_map<int, CPipe>& ClearP(unordered_map<int, CPipe>& MapPipe)
{
    MapPipe.clear();
    return MapPipe;
}
unordered_map<int, CStation>& ClearCS(unordered_map<int, CStation>& CStation)
{
    CStation.clear();
    return CStation;
}

int Get_PipeID(unordered_map<int, CPipe>& MapPipe)
{
    int d;
    int pID = 0;
    cout << "Enter a diameter of the pipe: ";
    d = check_diameter();
    for (auto& [id, p]: MapPipe)
    {
        if (d == p.diametr && p.repair == false && p.CS_entrance == -1) 
        {
            pID = p.GetPipeID();
            break;
        }
    }
    if (!pID) 
    {
        cout << "Pipe not found. You can create a new one:" << endl;
        CPipe p;
        cout << "Please, enter the name of the pipe: ";
        GetLine(cin, p.name);
        cout << "Please, enter pipe length: ";
        p.length = check_cond(1000);
        p.diametr = d;
        p.repair = false;
        MapPipe.insert({ p.GetPipeID(), p});
        pID = p.GetPipeID();
    }
    return pID;
}

int GetCSID_Entrance(unordered_map<int, CStation>& MapCS)
{
    int entrance;
    cout << "Enter an CS ID of the entrance: ";
    entrance = check_cond(MapCS.size());
    return entrance;
}

int GetCSID_Exit(unordered_map<int, CStation>& MapCS)
{
    int exit;
    cout << "Enter an CS ID of the exit: ";
    exit = check_cond(MapCS.size());
    return exit;
}

int main()
{
    redirect_output_wrapper cerr_out(cerr);
    ofstream logfile("log.txt");
    if (logfile)
        cerr_out.redirect(logfile);
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
            MapPipe.insert({ p.GetPipeID(), p });
            cout << p;
            break;
        }
        case 2:
        {
            CStation station;
            cin >> station;
            MapCS.insert({ station.GetCSID(), station });
            cout << station;
            break;
        }
        case 3:
        {
            cout << "Pipes information: " << endl;
            for (auto& i: MapPipe)
            {
                cout << i.second << endl;
            }
            cout << "Compressor stations information: " << endl;
            for (auto& i : MapCS)
            {
                cout << i.second << endl;
            }
            break;
        }
        case 4:
        {
            cout << "Enter ID of the pipes for editing: " << endl;
            int id;
            id = check_cond(CPipe::MaxID);
            if (CheckID(MapPipe, id))
            {
                EditPipe(MapPipe, id);
            }
            else
            {
                cout << "Pipe with such ID was not found";
            }
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
                for (auto& i : MapPipe) 
                {
                    SavePipe(fout, i.second);
                }
                fout << MapCS.size() << endl;
                for (auto& i : MapCS) 
                {
                    SaveCS(fout, i.second);
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
                MapPipe = ClearP(MapPipe);
                MapCS = ClearCS(MapCS);
                int count_p;
                fin >> count_p;
                while (count_p--) 
                {
                    CPipe p = LoadPipe(fin);
                    MapPipe.insert({p.GetPipeID(), p});
                    p.MaxID = p.GetPipeID();

                }
                int count_s;
                fin >> count_s;
                while (count_s--) 
                {
                    CStation station = LoadCS(fin);
                    MapCS.insert({station.GetCSID(), station});
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
                cout << MapPipe[id];
            }
            break;
        }
        case 9:
        {
            cout << "Input pipe in repair or not: ";
            bool flag = check_bool(0, 1);
            for (int id: FindPipesByFilter(MapPipe, CheckByRepair, flag)) 
            {
                cout << MapPipe[id];
            }
            break;
        }
        case 10:
        {
            cout << "Please, enter a pipe's ID for deleting: ";
            int id;
            id = check_cond(CPipe::MaxID);
            if (CheckID(MapPipe, id))
            {
                DeletePipe(MapPipe, id);
            }
            else
            {
                cout << "Pipe with such ID was not found";
            }
            break;
        }
        case 11:
        {
            unordered_set<int> PID = PackEdit(MapPipe);
            bool flag = true;
            while (flag)
            {
                EditMenu();
                switch (checkmenu())
                {
                case 1:
                {
                    PID.clear();
                    bool flag = true;
                    while (flag)
                    {
                        cout << "Input ID of pipe or enter '0' to exit: ";
                        int id;
                        id = check_cond(CPipe::MaxID, 0);
                        if (id)
                        {
                            if (CheckID(MapPipe, id))
                            {
                                PrintFoundPipes(id, MapPipe);
                                PID.insert(id);
                            }
                            else
                            {
                                cout << "No pipe with such ID" << endl;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    break;
                }
                case 2:
                {
                    for (const int& id : PID)
                    {
                        EditPipe(MapPipe, id);
                    }
                    break;
                }
                case 3:
                {
                    for (const int& id : PID)
                    {
                        DeletePipe(MapPipe, id);
                    }
                    break;
                }
                case 4:
                {
                    for (auto& i : MapPipe)
                    {
                        cout << i.second << endl;
                    }
                    break;
                }
                case 0:
                {
                    flag = false;
                    break;
                }
                }
            }
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
        case 15:
        {
            int pID = Get_PipeID(MapPipe);
            int entrance = GetCSID_Entrance(MapCS);
            int exit = GetCSID_Exit(MapCS);
            if (CheckID(MapCS, entrance) && CheckID(MapCS, exit) && entrance != exit && MapCS[entrance].working < MapCS[entrance].workshops && MapCS[exit].working < MapCS[exit].workshops)
            {
                MapCS[entrance].working++;
                MapCS[exit].working++;
                MapCS[entrance].start++;
                MapCS[exit].stop++;
                MapPipe[pID].CS_entrance = entrance;
                MapPipe[pID].CS_exit = exit;
            }
            break;
        }
        case 16:
        {
            cout << "Enter a pipeline's ID for diconnection: ";
            int pID = check_cond(CPipe::MaxID, 0);
            if (CheckID(MapPipe, pID) && MapPipe[pID].CS_entrance != -1)
            {
                MapCS[MapPipe[pID].CS_entrance].start--;
                MapCS[MapPipe[pID].CS_exit].stop--;
                MapPipe[pID].CS_entrance = -1;
                MapPipe[pID].CS_exit = -1;
            }
            break;
        }
        case 17:
        {
            break;
        }
        case 18:
        {
            for (auto& [id, p]: MapPipe)
            {
                if (p.CS_entrance != -1)
                {
                    cout << p << endl;
                }
            }
            for (auto& [id, station] : MapCS)
            {
                if (station.start > 0 || station.stop > 0)
                {
                    cout << station << endl;
                }
            }
            break;
        }
        case 0:
        {
            return 0;
            break;
        }
        default:
        {
            cout << "Wrong action! Please, try again." << endl;
        }
        }
    }
    return 0;
}