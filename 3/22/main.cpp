#include "caculate.h"
#include <iostream>
#include <string>

using namespace std;
using namespace my_stl2;

int main()
{
	string expr;
	cout << "lin17's caculator\nsupport:\n";
	for(const auto& x: opPrecedence)
		cout << "[\" " << x.first << " \"] ";
	cout << "operators" << endl;

	while(getline(cin, expr))
	{
		if(expr.empty())
			continue;
		if(expr == "quit" || expr == "q")
			break;

		errorCon ec;
		double result = caculate(expr, ec);
		if(!ec)
		{
			cout << ec.msg << endl;
			continue;
		}
		cout << result << endl;
	}
}
