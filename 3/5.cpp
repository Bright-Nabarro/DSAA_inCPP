#include <iostream>
#include "../list/list.h"
#include "../algorithm/algorithm.h"

int main()
{
	using namespace my_stl2;
	list<int> l1 {1,2,3}, l2 {2,3,4};
	to_uniqueset(l1);
	to_uniqueset(l2);
	list<int> result = set_intersect(l1, l2);
	for(int x: result)
		std::cout << x << " ";
	std::cout << std::endl;
}
