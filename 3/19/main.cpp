#include "list_simple.h"
#include <iostream>

int main()
{
	my_stl2::list<int> li1;
	li1.append(1);
	li1.append(2);
	std::cout << li1.get(0) << std::endl;
	std::cout << li1.get(1) << std::endl;
}