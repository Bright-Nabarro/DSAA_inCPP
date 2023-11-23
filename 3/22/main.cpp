#include "to_post.h"
#include <iostream>

using namespace std;
int main()
{
	string expr;
	getline(cin, expr);
	my_stl2::error_code ec = 0;
	auto result = my_stl2::to_postfix(expr, ec);
	for(const auto& x: result)
	{
		cout << x << " ";
	}
	cout << endl;
}
