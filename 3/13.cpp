#include "../list/list.h"
#include <iostream>

int main()
{
	using namespace my_stl2;
	list<int> li{1,2,3,4,5,6,7,8,9};
	for(auto itr = --li.cend(); itr != --li.cbegin(); itr--)
		std::cout << *itr << " ";
	std::cout << std::endl;
}
