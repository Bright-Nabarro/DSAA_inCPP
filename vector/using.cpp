#include "vector.h"
#include <iostream>

int main()
{
	using namespace my_stl2;
	vector<int> vi{0,1,2,3,4,5,6,7,8,9};

	for(auto x: vi)
		std::cout << x << " ";
	std::cout << std::endl;
}
