#include "../vector/vector.h"
#include <iostream>

int main()
{
	using namespace my_stl2;
	vector<int> vi{0,1,2,3,4,5,6,7,8,9};

	vi.erase(vi.begin()+4);
	for(int x: vi)
		std::cout << x << " ";
	std::cout << std::endl;

	vi.insert(vi.begin()+3,4);
	for(int x: vi)
		std::cout << x << " ";
	std::cout << std::endl;

	vi.erase(vi.begin()+1,vi.begin()+8);
	for(int x: vi)
		std::cout << x << " ";
	std::cout << std::endl;

	vi.erase(vi.begin());
	for(int x: vi)
		std::cout << x << " ";
	std::cout << std::endl;
}
