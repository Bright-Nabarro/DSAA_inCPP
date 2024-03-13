#include "list.h"
#include <algorithm>
#include <iterator>
#include <iostream>
#include <random>
#include <ctime>
#include <vector>

int main()
{
	std::vector<int> v{1,2,3,4,5,6,7,8,9,0};
	my_stl2::list<int> l(v.begin(), v.end());
	for(auto x: l)
		std::cout << x << " ";
	std::cout << std::endl;
}
