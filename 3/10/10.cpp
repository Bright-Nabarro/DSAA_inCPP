#include "../../vector/vector_stringent.h"
#include <iostream>

int main()
{
	using namespace my_stl2;
	vector<int> vi{0, 1, 2, 4, 5, 6, 7, 8, 9};
	for (int x : vi)
		std::cout << x << " ";
	std::cout << std::endl;
	vi.insert(vi.begin(), 3);
	for (int x : vi)
		std::cout << x << " ";
	std::cout << std::endl;
	try
	{
		vi.erase(vi.end());
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}