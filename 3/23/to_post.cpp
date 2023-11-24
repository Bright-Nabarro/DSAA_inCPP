#include "to_post.h"
#include <stdexcept>
#include <vector>
#include <utility>
#include <stack>
#include <cctype>
#include <algorithm>
#include <cassert>

namespace my_stl2{
using namespace std;

map<math_opers, precedence> opPrecedence{
	{"(",0}, {")",0},{"^", 1},
	{"*", 2}, {"/", 2},
	{"+",3}, {"-",3}
};

map<math_opers,size_t> operatorTable{
	{"^", 0}, {"*", 1}, {"/", 2},
	{"+", 3}, {"-", 4}
};

precedence search_prece(const math_opers& op)
{
	if(opPrecedence.find(op) == opPrecedence.end())
		throw invalid_argument("cannot find op and errorCon is normal");

	return opPrecedence[op];
}


//=============error check function==================
bool checkInOp(const math_opers& op, errorCon& ec)
{
	if(opPrecedence.find(op) == opPrecedence.end())
	{
		ec.code = 1;
		ec.msg = "operators: " + op + " not legel";
		return false;
	}
	return true;
}

bool checkDecPoint(const string& infix, const int pos, errorCon& ec)
{
	if(pos == 0 || pos == infix.length() -1 ||
			!isdigit(infix[pos-1]) || !isdigit(infix[pos+1]))
	{
		ec.code = 1;
		ec.msg = "decimal point '.' not legel";
		return false;
	}
	return true;
}

//====================================================

inline void pushOprand(const string& infix, const int pos,  int& digitPos,
	   vector<pair<opers_num, math_opers>>& results, errorCon& ec)
{
	results.push_back({opers_num::operand, infix.substr(digitPos, pos-digitPos)});
	digitPos = -1;
}

bool pushOperator(const string& infix, const int pos,  int& opePos,
	   vector<pair<opers_num, math_opers>>& results, errorCon& ec)
{
	math_opers theOperator = infix.substr(opePos, pos-opePos);
	if(!checkInOp(theOperator, ec)) 
		return false;

	results.push_back({opers_num::operator_erp, theOperator});
	opePos = -1;
	return true;
}

bool pushParenthsis(const string& infix, const int pos, int& opePos, int& digitPos,
	   vector<pair<opers_num, math_opers>>& results, errorCon& ec)
{
	if(opePos != -1)
	{
		assert(digitPos == -1);
		if(!pushOperator(infix, pos, opePos, results, ec))
			return false;

		if(infix[pos] == '(')
			results.push_back({opers_num::operator_erp, "("});
		else
		{
			ec.code = 1;
			ec.msg = "operator next to the right parenthsis";
			return false;
		}
		opePos = -1;
	}
	else if(digitPos != -1)
	{
		//add a multiply
		assert(opePos == -1);
		pushOprand(infix, pos, digitPos, results, ec);
		if(infix[pos] == '(')
		{
			results.push_back({opers_num::operator_erp, "*"});
			results.push_back({opers_num::operator_erp, "("});
		}
		else
			results.push_back({opers_num::right_parenthsis, ")"});
	}
	else
	{
		assert(infix[pos-1] == '(' || infix[pos-1] == ')' || pos == 0 );
		if(infix[pos] == '(')
		{
			if(infix[pos-1] == ')')
				results.push_back({opers_num::operator_erp, "*"});
			results.push_back({opers_num::operator_erp, "("});
		}
		else
			results.push_back({opers_num::right_parenthsis, ")"});
	}
	return true;
}

vector<pair<opers_num,math_opers>> split_math_expression
	(string infix, errorCon& ec)
{
	infix.erase(remove(infix.begin(), infix.end(), ' '), infix.end());
	vector<pair<opers_num, math_opers>> results;
	//pre...pos = -1 when prePos donot recognized
	int digitPos = -1, opePos = -1, pos;
	for(pos = 0; pos < infix.length(); pos++)
	{
		if(isdigit(infix[pos]))
		{
			if(digitPos == -1)
				digitPos = pos;

			if(opePos != -1 && !pushOperator(infix, pos, opePos, results, ec))
				return{};
		}
		else if(infix[pos] == '.' && !checkDecPoint(infix, pos, ec))
				return{};

		else if((infix[pos] == '(' || infix[pos] == ')'))
		{
			if(!pushParenthsis(infix,pos,opePos,digitPos,results,ec))
				return{};
		}
		else
		{
			if(opePos == -1)
				opePos = pos;
			
			if(digitPos != -1)
				pushOprand(infix, pos, digitPos, results, ec);
		}
	}

	if(opePos != -1)
	{
		ec.code = 1;
		ec.msg = "last operator not digit";
		return {};
	}
	assert(digitPos != -1 || infix[infix.length()-1] == ')');

	//==================need check=============================//
	if(digitPos != -1)
		pushOprand(infix, infix.length(), digitPos, results, ec);
	//==================need check=============================//

	return results;
}

void pop_until(precedence n, stack<pair<opers_num,math_opers>>& stk, 
		vector<pair<opers_num,math_opers>>& output)
{
	while(!stk.empty() && search_prece(stk.top().second) <= n && stk.top().second != "(")
	{
		output.push_back(stk.top());
		stk.pop();
	}
}

vector<pair<opers_num,math_opers>> to_postfix(const string& infix, errorCon& ec)
{
	auto expression = split_math_expression(infix, ec);
	if(!ec)
		return {};
	vector<pair<opers_num, math_opers>> result;
	stack<pair<opers_num, math_opers>> stkOperators;		//just pushed for operators
	for(const auto& x: expression)
	{
		switch (x.first)
		{
		case opers_num::operand:
			result.push_back(x);
			break;
		case opers_num::operator_erp:
			pop_until(search_prece(x.second), stkOperators, result);
			stkOperators.push(x);
			break;
		case opers_num::right_parenthsis:
			while(!stkOperators.empty() && stkOperators.top().second != "(")
			{
				result.push_back(stkOperators.top());
				stkOperators.pop();
			}
			if(stkOperators.empty())
			{
				ec.code = 1;
				ec.msg = "right parenthsis cannot balanced";
				return {};
			}
			stkOperators.pop();
			break;
		default:
			throw domain_error("function check return invalid postfix (x.first)");
		}
	}
	while(!stkOperators.empty())
	{
		auto x = stkOperators.top();
		if(x.second == "(")
		{
			ec.code = 1;
			ec.msg = "left parenthsis cannot balanced";
			return {};
		}
		result.push_back(x);
		stkOperators.pop();
	}
	return result;
}

}	//namespace my_stl2;
