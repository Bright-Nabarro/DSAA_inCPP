#include "../list/list_stringent.h"
#include <iostream>

int main()
{
	my_stl2::list<int> li{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	auto itr = li.begin();
// cannot check this problem
//	try{
//		itr--;
//		li.erase(itr);
//	} catch(std::exception& e) {
//		std::cout << e.what() << std::endl;
//	}
	try{
		----itr;
	} catch(std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
