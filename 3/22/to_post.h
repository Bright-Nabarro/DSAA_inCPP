#pragma once

#include <string>
#include <vector>

namespace my_stl2{

using math_opers = std::string;
using precedence = int;
using error_code = size_t;

std::vector<math_opers> to_postfix(const std::string& infix, error_code ec);

std::vector<std::pair<int,math_opers>>
	split_math_expression(std::string infix, error_code& ec);
}	//namespace my_stl2
