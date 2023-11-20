#include "balance_symbols.h"

namespace bs{
std::map<std::string_view, std::map<std::string,std::string>> 
	languages{
		{"Pascal",{{"end","first"},{")","("}, {"]","[",}, {"}","{"}}},
		{"C++",{{"*/", "/*"}, {")","("}, {"]","[",}, {"}","{"}}}
	};

balance_msg isBalanced(std::string_view ownStr, std::string_view lge)
{
	if(languages.find(lge) == languages.end())
		throw std::invalid_argument
			("the key: "+ std::string(lge) + " can not find");

	int lines = 1;
	std::stack<std::string> strStack;
	auto& barcket = languages[lge];
	for(size_t i = 0; i < ownStr.length(); i++)
	{
		if(ownStr[i] == '\n')
			lines++;
		for(const auto& x: barcket)
		{
			if(ownStr.substr(i,x.second.length()) == x.second)
			{
				strStack.push(x.second);
				//main loop has i++, so -1 in this
				i += x.second.length() -1;
				break;
			}
			if(ownStr.substr(i, x.first.length()) == x.first)
			{
				if(strStack.empty() || strStack.top() != x.second)
				{
					std::ostringstream ossm;
					ossm << "error at line: " << lines;
					return {false,x.second,"post",ossm.str()};
				}
					
				strStack.pop();
			}
		}
	}
	if(strStack.empty())
		return {true};
		
	std::ostringstream ossm;
	ossm << "error at line: " << lines;
	return {false,strStack.top(),"pre", ossm.str()};
}

}	//namespace bs
