#include "vector.h"
#include <iostream>

int main()
{
	using namespace my_adt;
	vector<int> v(6);
	for (auto& x : v)
		x = 114514;
	for (auto x : v)
		std::cout << x << " ";
	puts("\n");
}