#include "to_post.h"
#include <stdexcept>
#include <map>
#include <vector>
#include <utility>
#include <stack>
#include <cctype>
#include <algorithm>
#include <cassert>

namespace my_stl2{
using namespace std;

map<math_opers, precedence> opPrecedence{
	{"(",0}, {")",0}, {"*", 1}, {"/",1},
	{"+",2}, {"-",2}
};

precedence search_prece(const math_opers& op)
{
	if(opPrecedence.find(op) == opPrecedence.end())
		throw invalid_argument("cannot find op and error_code is normal");

	return opPrecedence[op];
}

vector<pair<int,math_opers>> split_math_expression
	(string infix, error_code& ec)
{
	//if opers is operand : 0
	//operators except ")" : 1
	//")" : 2
	infix.erase(remove(infix.begin(), infix.end(), ' '), infix.end());
	vector<pair<int, math_opers>> results;
	//pre...pos = -1 when prePos donot recognized
	int preDigitPos = -1, preOpePos = -1, pos;
	for(pos = 0; pos < infix.length(); pos++)
	{
		if(isdigit(infix[pos]))
		{
			if(preDigitPos == -1)
				preDigitPos = pos;

			if(preOpePos == -1) continue;
			else
			{
				math_opers theOperator = infix.substr(preOpePos, pos-preOpePos);
				int reco;
				if(opPrecedence.find(theOperator) == opPrecedence.end())
				{
					//invalid operator
					ec = 1;
					return {};
				}
				else
					reco = 1;
				results.push_back({reco, theOperator});
				
				preOpePos = -1;
			}
		}
		else if(infix[pos] == '.')
		{
			if(pos == 0 || pos == infix.length() -1 ||
				!isdigit(infix[pos-1]) || !isdigit(infix[pos+1]))
			{
				//invalid operator '.'
				ec = 1;
				return {};
			}
			continue;
		}
		else if(infix[pos] == '(' || infix[pos] == ')')
		{
			if(preOpePos != -1)
			{
				assert(preDigitPos == -1);
				math_opers theOperator = infix.substr(preOpePos, pos-preOpePos);
				int reco;
				if(opPrecedence.find(theOperator) == opPrecedence.end())
				{
					//invalid operator
					ec = 1;
					return {};
				}
				results.push_back({reco, theOperator});
				if(infix[pos] == '(')
					results.push_back({1, "("});
				else
				{
					//operator next to the right parenthsis
					ec = 1;
					return {};
				}
				preOpePos = -1;
			}
			else if(preDigitPos != -1)
			{
				//add a multiply
				assert(preOpePos == -1);
				math_opers operand = infix.substr(preDigitPos, pos-preDigitPos);
				int reco = 0;
				results.push_back({reco, operand});
				if(infix[pos] == '(')
				{
					results.push_back({1, "*"});
					results.push_back({1, "("});
				}
				else
					results.push_back({2, ")"});
				preDigitPos = -1;
			}
			else
			{
				assert(infix[pos-1] == '(' || infix[pos-1] == ')');
				if(infix[pos] == '(')
				{
					if(infix[pos-1] == ')')
						results.push_back({1, "*"});
					results.push_back({1, "("});
				}
				else
					results.push_back({2, ")"});
			}
		}
		else
		{
			if(preOpePos == -1)
				preOpePos = pos;
			
			if(preDigitPos == -1) continue;
			else
			{
				math_opers operand = infix.substr(preDigitPos, pos-preDigitPos);
				int reco = 0;
				results.push_back({reco, operand});
				preDigitPos = -1;
			}
		}
	}
	if(preOpePos != -1)
	{
		//last subexpression not digit
		ec = 1;
		return {};
	}
	assert(preDigitPos != -1 || infix[infix.length()-1] == ')');

	if(preDigitPos != -1)
	{
		math_opers operand = infix.substr(preDigitPos, infix.length());
		int reco = 0;
		results.push_back({reco, operand});
	}
	return results;
}

void pop_until(precedence n, stack<math_opers>& stk, vector<math_opers>& output)
{
	while(!stk.empty() && search_prece(stk.top()) <= n && stk.top() != "(")
	{
		output.push_back(stk.top());
		stk.pop();
	}
}

vector<math_opers> to_postfix(const string& infix, error_code ec)
{
	auto expression = split_math_expression(infix, ec);
	if(ec)
		return {};
	vector<math_opers> result;
	stack<math_opers> stkOperators;		//just pushed for operators
	for(const auto& x: expression)
	{
		switch (x.first)
		{
		case 0:		//operand
			result.push_back(x.second);
			break;
		case 1:		//operator
			pop_until(search_prece(x.second), stkOperators, result);
			stkOperators.push(x.second);
			break;
		case 2:
			while(!stkOperators.empty() && stkOperators.top() != "(")
			{
				result.push_back(stkOperators.top());
				stkOperators.pop();
			}
			if(stkOperators.empty())
			{
				//parenthsis cannot balanced
				ec = 1;
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
		result.push_back(stkOperators.top());
		stkOperators.pop();
	}
	return result;
}

}	//namespace my_stl2;
