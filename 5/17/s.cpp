#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

bool renumberLine(long F, long D, ifstream& in, ofstream& out)
{
	string line;
	long counter;
	long lineNumber;
	for(counter = 0; in >> lineNumber; counter++)
	{
		if(lineNumber == F)
			break;
		in.ignore(numeric_limits<std::streamsize>::max(), '\n');
	}
	if(in.eof())
		return false;		//cannot patten F with line number
	
	in.seekg(0, ios::beg);	//move read file pointer to the begin
	
	long begin { F - D*counter };
	for(lineNumber = begin; in.good(); lineNumber += D)
	{
		in.ignore(numeric_limits<std::streamsize>::max(), ' ');
		getline(in, line);
		out << lineNumber << '\t' << line << '\n';
	}
	return true;
}

int main()
{
	ifstream in{"row.bas", ios::in};
	ofstream out{"trun.bas", ios::out | ios::trunc};
	cout << boolalpha << renumberLine(40, 20, in, out) << '\n';
}