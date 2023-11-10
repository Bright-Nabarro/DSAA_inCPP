#include "../list/list.h"
#include <iostream>

int main()
{
	my_stl2::list<int> li1{1,2,3,4,5,6,7};
	my_stl2::list<int> li2{111,222,333,444};
	auto itr = li1.begin();
	++++++itr;
	li1.splice(itr, li2);
	for(int x: li1)
		std::cout << x << " ";
	std::cout << std::endl;
}
