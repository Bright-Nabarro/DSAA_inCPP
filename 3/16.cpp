#include "../list/list.h"
#include <iostream>

int main()
{
	my_stl2::list<int> li{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	auto itr = li.rbegin();
	while(itr != li.rend())
		std::cout << *itr++ << " ";
	auto citr = li.crbegin();
	while(itr != li.crend())
		std::cout << *citr++ << " ";
	std::cout << std::endl;
}
