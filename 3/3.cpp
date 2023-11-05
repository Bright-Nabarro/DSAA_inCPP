#include "../list/list.h"
#include "../algorithm/algorithm.h"
#include <iostream>

int main()
{
	using namespace my_stl2;
	list<int> li;
	for(int i = 0; i < 10; i++)
		li.push_back(i);

	auto ptr = find(li.begin(), li.end(), 5);
	std::cout << *ptr << std::endl;
}
