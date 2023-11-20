#include <fstream>
#include <iostream>
#include <format>                                
#include <sstream>
#include <format>
#include "balance_symbols.h"
using namespace std;

// -f=file path
// -l=language

void set_main_arg(int argc, const string& lge, string& filePath)
{
	for(int i = 1; i < argc; i++)
	{
	}
}

int main(int argc, char*argv[])
{
	string lge{};
	string filePath{};
	if(argc > 1)
	{
		for(int i = 1; i < argc; i++)
		{
			if(argv[i][0] == '-' && argv[i][1] == 'f' 
					&& argv[i][2] == '=')
			{
				filePath = argv[i];
				filePath.erase(0,3);
			}
			else if(argv[i][0] == '-' && argv[i][1] == 'l' 
					&& argv[i][2] == '=')
			{
				lge = argv[i];
				lge.erase(0,3);
			}
		}
		if(lge == "")
			lge = "C++";
	}
	else
	{
		lge = "C++";
	}

	if(filePath == "")
	{
		cout << "check file: ";
		cin >> filePath;
	}
	ifstream inFile(filePath);
	while(!inFile.is_open())
	{
		cout << filePath << " can not open\n";
		cout << "check file: ";
		cin >> filePath;
		inFile.open(filePath);
	}
	
	ostringstream ossm;
	ossm << inFile.rdbuf();
	auto Bd = bs::isBalanced(ossm.str(), lge);
	if(Bd)
	{
		return 0;
	}
	else
	{
		cout << format("{}: {} cannot pattern\n{}\n"
				, Bd.location, Bd.errorSymbol, Bd.error_msg);
		return 1;
	}
}
