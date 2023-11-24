#pragma once

#include <string>
#include <vector>
#include <map>

namespace my_stl2{

using math_opers = std::string;
using precedence = int;
extern std::map<math_opers, precedence> opPrecedence;
extern std::map<math_opers,size_t> operatorTable;

enum class opers_num{
	operand = 0,
	operator_erp = 1,
	right_parenthsis = 2
};

struct errorCon
{
	std::string msg;
	size_t code;
	explicit operator bool () { return code == 0;}
	errorCon() { code = 0; }
};

std::vector<std::pair<opers_num,math_opers>> to_postfix(const std::string& infix, errorCon& ec);

std::vector<std::pair<opers_num, math_opers>>
	split_math_expression(std::string infix, errorCon& ec);
}	//namespace my_stl2
