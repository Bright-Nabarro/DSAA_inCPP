#include "../vector/vector.h"
#include <iostream>

int main()
{
	using namespace my_stl2;
	vector<int> v;
	for(int i = 0; i < 5; i++)
		v.push_back(i);
	try{
		v.at(6);
	}catch(std::exception& e){
		std::cout << e.what() << std::endl;
	}
}
