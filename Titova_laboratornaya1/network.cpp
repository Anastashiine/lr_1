#include "network.h"
#include "utils.h"
#include "CPipe.h"
#include "Cstation.h"
#include <queue>
using namespace std;

int network:: Get_PipeID(unordered_map<int, CPipe>& MapPipe)
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
        CPipe p = CPipe:: AddPipe(d);
        MapPipe.insert({ p.GetPipeID(), p });
        pID = p.GetPipeID();
    }
    return pID;
}
vector<int> network::TopologicalSort(vector<vector<int>>& r, unordered_map<int, int>& stepen)
{
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
        result.resize(0);
    }
    return result;
}