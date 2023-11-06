#include "../list/list.h"
#include "../algorithm/algorithm.h"
#include <iostream>

int main()
{
	using namespace my_stl2;
	list<int> L1{1, 3, 5, 7, 9};
	list<int> L2{2, 3, 5, 7, 11};
	to_uniqueset(L1); to_uniqueset(L2);
	auto merged_L = set_union(L1, L2);
	for(int x: merged_L)
		std::cout << x << " ";
	std::cout << std::endl;
}
