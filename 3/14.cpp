#include "../vector/vector_stringent.h"
#include <iostream>

int main()
{
	my_stl2::vector<int> vi{0,1,2,3,4,5,6,7};
	auto itr = vi.begin();
	std::cout << *(itr+3) << std::endl;
}
