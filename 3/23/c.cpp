#include "to_post.h"
#include <iostream>
#include <stack>
#include <stdexcept>
#include <sstream>
#include <cassert>

using namespace std;
using namespace my_stl2;

// The implementation is closely resembles the process of evaluating
// a postfix expression. By adding parenthsis to each sub-expression.
// We ensure the order of operations is preserved
string to_infix(const std::vector<std::pair<opers_num,math_opers>>& expr)
{
	stack<math_opers> stk;
	math_opers x1, x2, merge;
	for(const auto& x: expr)
	{
		if(x.first == opers_num::operand)
		{
			stk.push(x.second);
		}
		else if(x.first == opers_num::operator_erp)
		{
			assert(stk.size() >= 2);
			x2 = stk.top();
			stk.pop();
			x1 = stk.top();
			stk.pop();
			merge = "(" + x2 + x.second + x1 + ")";
			stk.push(merge);
		}
		else 
		{
			ostringstream ossm;
			ossm << "to_postfix have invalid oper:"
				 << static_cast<int>(x.first) << " " << x.second;
			throw logic_error(ossm.str());
		}
	}
	assert(stk.size() == 1);
	return stk.top();
}

int main()
{
	string expr;
	errorCon ec;
	getline(cin, expr);
	auto result {to_postfix(expr, ec)};
	for(const auto& x: result)
		cout << x.second;
	cout << endl;

	if(ec)
		cout << to_infix(result) << endl;
	else
		cout << ec.msg << endl;
}
