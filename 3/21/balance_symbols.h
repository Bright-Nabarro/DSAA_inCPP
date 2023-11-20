#pragma once
#include <map>
#include <string>
#include <string_view>
#include <utility>
#include <stack>
#include <stdexcept>
#include <sstream>

namespace bs
{
extern std::map<std::string_view, std::map<std::string,std::string>> 
	languagesBack;

struct balance_msg
{
	bool balanced;
	std::string errorSymbol;
	std::string location;
	std::string error_msg;
	balance_msg(bool isB, std::string sym="", std::string loctn="",
			std::string msg=""): balanced{isB}, location{sym},
			error_msg(msg){}
	explicit operator bool (){ return balanced; }
};

balance_msg isBalanced(std::string_view own, std::string_view lge = "C++");

}	//bs
