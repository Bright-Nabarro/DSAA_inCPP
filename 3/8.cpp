#include "vector.h"
#include <iostream>

int main()
{
	using namespace my_stl2;
	vector<int> vi{0,1,2,3,4,5,6,7,8,9};

	vi.erase(4);
	for(int x: vi)
		std::cout << x << " ";
	std::cout << std::endl;

	vi.insert(3,4);
	for(int x: vi)
		std::cout << x << " ";
	std::cout << std::endl;

	vi.erase(1,8);
	for(int x: vi)
		std::cout << x << " ";
	std::cout << std::endl;

	vi.erase(static_cast<size_t>(0));
	for(int x: vi)
		std::cout << x << " ";
	std::cout << std::endl;
}
