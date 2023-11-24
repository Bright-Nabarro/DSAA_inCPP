#include "caculate.h"
#include <stack>
#include <sstream>
#include <cmath>
using namespace std;

namespace my_stl2
{

void stkTo2Double(stack<double>& stk, double& x1, double& x2)
{
	x1 = stk.top();
	stk.pop();
	x2 = stk.top();
	stk.pop();
}

double caculate(vector<pair<opers_num, math_opers>>& exprs)
{
	stack<double> exprStk;
	for(const auto& x: exprs)
	{
		if(x.first == opers_num::operand)
		{
			exprStk.push(stod(x.second));
		}
		else if(x.first == opers_num::operator_erp)
		{
			double x1, x2;
			switch(operatorTable[x.second])
			{
			case 0:
				stkTo2Double(exprStk, x1, x2);
				exprStk.push(pow(x1, x2));
				break;
			case 1:
				stkTo2Double(exprStk, x1, x2);
				exprStk.push(x1*x2);
				break;
			case 2:
				stkTo2Double(exprStk, x1, x2);
				exprStk.push(x2/x1);
				break;
			case 3:
				stkTo2Double(exprStk, x1, x2);
				exprStk.push(x1+x2);
				break;
			case 4:
				stkTo2Double(exprStk, x1, x2);
				exprStk.push(x2-x1);
				break;
			}
		}
		else
		{
			ostringstream buf;
			buf << "x.first: " << static_cast<int>(x.first) 
				<< " omission in to_postfix function";
			throw domain_error(buf.str());
		}
	}
	if(exprStk.size() != 1)
		throw logic_error("loss number or original expression invalid\
in to_postfix function");
	return exprStk.top();
}

double caculate(const string& ownExpression, errorCon& ec)
{
	auto expr = to_postfix(ownExpression, ec);
	if(!ec)
		return {};
	return caculate(expr);
}

}	//namespace my_stl2
