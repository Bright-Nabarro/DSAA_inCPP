#include "../../list/list.h"
#include <iostream>

int main()
{
	using namespace my_stl2;
	int N, M;
	std::cout << "M: ";
	std::cin >> M;
	std::cout << "N: ";
	std::cin >> N;

	//if M>=N remove extra traversal
	M = M%N;
	list<int> L;
	for (int i = 1; i <= N; i++)
		L.push_back(i);
	int Mi = 0;
	auto ptr = L.begin();
	while (L.size() > 1)
	{
		if (Mi == M)
		{
			ptr = L.erase(ptr);
			if (ptr == L.end())
				ptr = L.begin();
			Mi = 0;
			continue;
		}
		Mi++;
		ptr++;
		if (ptr == L.end())
			ptr = L.begin();
	}
	std::cout << *ptr << std::endl;
}
