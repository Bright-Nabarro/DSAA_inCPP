#include "to_post.h"
#include <iostream>

using namespace std;
int main()
{
	string expr;
	getline(cin, expr);
	my_stl2::error_code ec = 0;
	auto result = my_stl2::split_math_expression(expr, ec);
	if(ec == 0)
	{
		for(const auto& x: result)
		{
			cout << x.first << ": "<< x.second << "    ";
		}
		cout << endl;
	}
	else
	{
		cout << "error" << endl;
	}
}
