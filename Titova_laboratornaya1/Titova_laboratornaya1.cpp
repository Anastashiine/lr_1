#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "CPipe.h"
#include "CStation.h"
#include "utils.h"
#include <unordered_set>
#include <queue>
#include "network.h"
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
    param = ((MapCS.get_wk() - MapCS.get_working()) * 100) / MapCS.get_wk();
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
void FindAllStationsByName(network& net)
{
    string name;
    cout << "Enter station name for searching: ";
    GetLine(cin, name);
    for (int id : FindCSByFilter(net.Get_CS(), CheckByName, name))
    {
        cout << net.Get_CS()[id];
    }
}

void FindAllStationsByBusyWorkshops(network& net)
{
    cout << "Enter percent of unworking stations for searching: ";
    double percent = check_cond(100);
    for (int id : FindCSByFilter(net.Get_CS(), CheckByUnworkingWorkshops, percent))
    {
        cout << net.Get_CS()[id];
    }
}
void PackMenu()
{
    cout << "1. Find pipes by name" << endl;
    cout << "2. Find pipes by repair" << endl;
}
unordered_set<int> PackEdit(network& net)
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
        for (int id : FindPipesByFilter(net.Get_Pipe(), CheckByName, name))
        {
            cout << net.Get_Pipe()[id];
            PID.insert(id);
        }
        break;
    }
    case 2:
    {
        bool flag;
        cout << "Input pipe in repair or not: ";
        flag = check_bool(0, 1);
        for (int id : FindPipesByFilter(net.Get_Pipe(), CheckByRepair, flag))
        {
            cout << net.Get_Pipe()[id];
            PID.insert(id);
        }
        break;
    }
    }
    return PID;
}
unordered_set<int> SelectPipesID(network& net)
{
    unordered_set<int> PID{};
    while (1)
    {
        cout << "Input ID of pipeline or 0 to complete: ";
        int id;
        id = check_id();
        if (id)
        {
            if (CheckID(net.Get_Pipe(), id))
            {
                cout << net.Get_Pipe()[id];
                PID.insert(id);
            }
            else
            {
                cout << "No pipeline with such ID" << endl;
            }
        }
        else
        {
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

int main()
{
    redirect_output_wrapper cerr_out(cerr);
    ofstream logfile("log.txt");
    if (logfile)
        cerr_out.redirect(logfile);
    network net;
    while (1)
    {
        PrintMenu();
        switch (checkmenu())
        {
        case 1:
        {
            CPipe p;
            cin >> p;
            net.Add_Pipe(p);
            break;
        }
        case 2:
        {
            CStation station;
            cin >> station;
            net.Add_CS(station);
            break;
        }
        case 3:
        {
            net.view_all_objects();
            break;
        }
        case 4:
        {
            net.EditPipe(0);
            break;
        }
        case 5:
        {
            net.EditCS();
            break;
        }
        case 6:
        {
            net.Save_Data();
            break;
        }
        case 7:
        {
            net.Load_Data();
            break;
        }
        /*case 8:
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
        }*/
        case 10:
        {
            net.DeletePipe(0);
            break;
        }
        case 11:
        {
            unordered_set<int> PID = PackEdit(net);
            bool flag = true;
            while (flag)
            {
                EditMenu();
                switch (checkmenu())
                {
                case 1:
                {
                    PID = SelectPipesID(net);
                    break;
                }
                case 2:
                {
                    for (const int& id : PID)
                    {
                        net.EditPipe(id);
                    }
                    break;
                }
                case 3:
                {
                    for (const int& id : PID)
                    {
                        net.DeletePipe(id);
                    }
                    break;
                }
                case 4:
                {
                    for (auto& [id, p] : net.Get_Pipe())
                    {
                        cout << p << endl;
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
            FindAllStationsByName(net);
            break;
        }
        case 13:
        {
            FindAllStationsByBusyWorkshops(net);
            break;
        }
        case 14:
        {
            net.DeleteCS();
            break;
        }
        case 15:
        {
            net.Connect();
            break;
        }
        case 16:
        {
            net.Disconnect();
            break;
        }
        case 17:
        {
            net.TopologicalSort();
            break;
        }
        case 18:
        {
            net.View_network();
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
//https://www.guru99.com/topological-sort-algorithm.html