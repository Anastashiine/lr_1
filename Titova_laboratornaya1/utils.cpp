#include "utils.h"
#include <unordered_set>
using namespace std;
int check_diameter()
{
	int d;
	unordered_set<int> diameter = { 500, 700, 1000, 1400 };
	while ((cin >> d).fail() || !(diameter.contains(d))) 
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Select pipe diameter: 500, 700, 1000 or 1400: ";
	}
	cerr << d << endl;
	return d;
}