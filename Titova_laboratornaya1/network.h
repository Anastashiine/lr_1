#pragma once
#include "utils.h"
#include "CPipe.h"
#include "CStation.h"
#include <unordered_map>
class network
{
public:
	int Get_PipeID(unordered_map<int, CPipe>& MapPipe);
	vector<int> TopologicalSort(vector<vector<int>>& r, unordered_map<int, int>& stepen);
};