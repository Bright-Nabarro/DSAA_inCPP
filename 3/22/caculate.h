#pragma once
#include <vector>
#include <utility>
#include <string>
#include "../23/to_post.h"

namespace my_stl2
{

double caculate(const std::string& ownExpression, errorCon& ec);
double caculate(std::vector<std::pair<opers_num,math_opers>>& exprs);

}	//namespace my_stl2
