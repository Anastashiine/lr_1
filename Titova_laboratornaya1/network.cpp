#include "network.h"
#include "utils.h"
#include <queue>
#include <iostream>
#include <fstream>
using namespace std;

unordered_map <int, CPipe>
network::Get_Pipe()
{
    return MapPipe;
}
unordered_map <int, CStation>
network::Get_CS()
{
    return MapCS;
}
int network::Get_PipeID()
{
    int d;
    int pID = 0;
    cout << "Enter a diameter of the pipe: ";
    d = check_diameter();
    for (auto& [id, p] : MapPipe)
    {
        if (d == p.get_diameter() && p.repair == false && p.add_pipe_entrance() == -1)
        {
            pID = p.GetPipeID();
            break;
        }
    }
    if (!pID)
    {
        cout << "Pipe not found. You can create a new one:" << endl;
        CPipe p = CPipe::AddPipe(d);
        MapPipe.insert({ p.GetPipeID(), p });
        pID = p.GetPipeID();
    }
    return pID;
}
void network::Add_Pipe(const CPipe& p)
{
    MapPipe.insert({ p.GetPipeID(), p });
}
void network::Add_CS(const CStation& station)
{
    MapCS.insert({ station.GetCSID(), station });
}
void network::view_all_objects()
{
    for (auto& i : MapPipe)
    {
        cout << i.second << endl;
    }
    for (auto& i : MapCS)
    {
        cout << i.second << endl;
    }
}
void network::Save_Data()
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
            if (i.second.name != "")
            {
                fout << i.second;
            }
        }
        fout << MapCS.size() << endl;
        for (auto& i : MapCS)
        {
            if (i.second.name != "")
            {
                fout << i.second;
            }
        }
        fout.close();
    }
}
void network::ClearPipe()
{
    MapPipe.clear();
}
void network::ClearCS()
{
    MapCS.clear();
}

void network::Load_Data()
{
    ifstream fin;
    fin.open(FName(), ios::in);
    if (fin.is_open())
    {
        ClearPipe();
        ClearCS();
        int count_p;
        fin >> count_p;
        while (count_p--)
        {
            CPipe p;
            fin >> p;
            MapPipe.insert({ p.GetPipeID(), p });
            p.SetMaxID();

        }
        int count_s;
        fin >> count_s;
        while (count_s--)
        {
            CStation station;
            fin >> station;
            MapCS.insert({ station.GetCSID(), station });
            station.SetMaxID();
        }
        fin.close();
    }
}
void network::EditPipe(int ID)
{
    int id = ID;
    if (ID = 0)
    {
        cout << "Enter ID of the pipes for editing: " << endl;
        id = check_id();
    }
    if (CheckID(MapPipe, id))
    {
        if (MapPipe[id].add_pipe_entrance() == -1)
        {
            MapPipe[id].repair = !(MapPipe[id].repair);
        }
        else
        {
            cout << "This pipe is in the network, you can't use it" << endl;
        }
    }
    else
    {
        cout << "Pipe with such ID was not found";
    }

}
void network::EditCS()
{
    cout << "Please, enter a station's ID for editing: ";
    int id;
    id = check_id();
    if (CheckID(MapCS, id))
    {
        if (MapCS[id].get_start() == 0 && MapCS[id].get_stop() == 0)
        {
            string solution;
            cout << "Please, enter 'start' if you want to add a working workshop and 'stop' if you want to stop a working workshop: ";
            cin >> solution;
            if (solution == "start")
            {
                MapCS[id].start_wk();
            }
            if (solution == "stop")
            {
                MapCS[id].stop_wk();
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
        cout << "Station with such ID was not found" << endl;
    }
}
void network::DeletePipe(int ID)
{
    int id = ID;
    if (ID = 0)
    {
        cout << "Please, enter a pipe's ID for deleting: ";
        id = check_id();
    }
    if (CheckID(MapPipe, id))
    {
        if (MapPipe[id].add_pipe_entrance() == -1)
        {
            MapPipe.erase(id);
        }
        else
        {
            cout << "This pipe is in the network, you can't use it" << endl;
        }
    }
    else
    {
        cout << "Pipe with such ID was not found";
    }
}
void network::DeleteCS()
{
    cout << "Please, enter a station's ID for deleting: ";
    int id;
    id = check_cond(MapCS.size());
    if (CheckID(MapCS, id))
    {
        if (MapCS[id].get_start() == 0 && MapCS[id].get_stop() == 0)
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
void network::Connect()
{
    int pID = Get_PipeID();
    cout << "Enter CS ID of the entrance: ";
    int entrance = check_id();
    cout << "Enter CS ID of the exit: ";
    int exit = check_id();
    if (CheckID(MapCS, entrance) && CheckID(MapCS, exit) && entrance != exit)
    {
        MapCS[entrance].start_wk();
        MapCS[exit].start_wk();
        MapCS[entrance].increase_start();
        MapCS[exit].increase_stop();
        MapPipe[pID].add_cs_entrance(entrance);
        MapPipe[pID].add_cs_exit(exit);
    }
}
void network::Disconnect()
{
    cout << "Enter a pipeline's ID for diconnection: ";
    int pID = check_id();
    if (CheckID(MapPipe, pID) && MapPipe[pID].add_pipe_entrance() != -1)
    {
        MapCS[MapPipe[pID].add_pipe_entrance()].dicrease_strat();
        MapCS[MapPipe[pID].add_pipe_exit()].dicrease_stop();
        MapPipe[pID].add_cs_entrance();
        MapPipe[pID].add_cs_exit();
    }
}
void network::View_network()
{
    for (auto& [id, p] : MapPipe)
    {
        if (p.add_pipe_entrance() != -1)
        {
            cout << p << endl;
        }
    }
    for (auto& [id, station] : MapCS)
    {
        if (station.get_start() > 0 || station.get_stop() > 0)
        {
            cout << station << endl;
        }
    }
}
vector<vector<int>>
network::Add_Rebra()
{
    vector <vector<int>> r;
    for (auto& [id, p] : MapPipe)
    {
        if (p.add_pipe_entrance() != -1)
        {
            r.push_back({ p.add_pipe_entrance(), p.add_pipe_exit() });
        }
    }
    return r;
}
unordered_map<int, int>
network::Add_Vershina()
{
    unordered_map<int, int> stepen;
    for (auto& [id, station] : MapCS)
    {
        if (station.get_start() > 0 || station.get_stop() > 0)
        {
            stepen.insert({ id, station.get_start() });
        }
    }
    return stepen;
}
void network::TopologicalSort()
{
    auto r = Add_Rebra();
    auto stepen = Add_Vershina();
    int vershiny = stepen.size();
    vector<int> result;
    queue<int> q;
    for (auto& [id, st] : stepen)
    {
        if (st == 0)
        {
            q.push(id);
        }
    }
    while (!q.empty())
    {
        int vershina = q.front();
        q.pop();
        result.insert(result.begin(), vershina);
        for (auto& pair : r)
        {
            if (pair[1] == vershina)
            {
                stepen[pair[0]]--;
                if (stepen[pair[0]] == 0)
                {
                    q.push(pair[0]);
                }
            }
        }
    }
    if (result.size() != vershiny)
    {
        cout << "Can't do topological sort. Network has a cycle" << endl;
    }
    else
    {
        for (int vershina : result)
        {
            cout << MapCS[vershina] << endl;
        }
    }
}