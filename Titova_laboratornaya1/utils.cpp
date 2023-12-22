#include "utils.h"
#include <unordered_set>
using namespace std;
int check_diameter()
{
	int d;
	const int diameters[] = { 500, 700, 1000, 1400 };
	while ((cin >> d).fail() || find(begin(diameters), end(diameters), d) == end(diameters))
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Select pipe diameter: 500, 700, 1000 or 1400: ";
	}
	cerr << d << endl;
	return d;
}
int check_id()
{
	int id;
	while ((cin >> id).fail())
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Enter an integer: ";
	}
	cerr << id << endl;
	return id;
}
string FName()
{
	string fname;
	cout << "Enter a file name: ";
	GetLine(cin, fname);
	return fname;
}