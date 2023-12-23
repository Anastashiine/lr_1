#pragma once
#include "utils.h"
#include "CPipe.h"
#include "CStation.h"
#include <unordered_map>
class CPipe;
class CStation;

class network
{
	std::unordered_map <int, CPipe> MapPipe;
	std::unordered_map <int, CStation> MapCS;
public:
	int Get_PipeID();
	void Add_Pipe(const CPipe& p);
	void Add_CS(const CStation& station);
	void view_all_objects();
	void Load_Data();
	void Save_Data();
	void ClearPipe();
	void ClearCS();
	void EditPipe(int ID);
	void EditCS();
	void DeletePipe(int ID);
	void DeleteCS();
	void Connect();
	void Disconnect();
	void View_network();
	std::unordered_map <int, CPipe> Get_Pipe();
	std::unordered_map <int, CStation> Get_CS();
	std::vector<std::vector<int>> Add_Rebra();
	std::unordered_map<int, int> Add_Vershina();
	void TopologicalSort();
};