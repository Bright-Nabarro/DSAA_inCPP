#include "list.h"
#include <algorithm>
#include <iterator>
#include <iostream>
#include <random>
#include <ctime>
#include <vector>

int main()
{
	my_adt::list<int> li;
	std::mt19937 gen(time(0));
	std::uniform_int_distribution<int> distrib(1,100);

	for(int i = 0; i < 10; i++)
		li.push_back(distrib(gen));

	std::copy(li.begin(), li.end(),
		   	std::ostream_iterator<int>(std::cout," "));
	std::cout << std::endl;
	
	std::vector<int>vs (li.begin(), li.end());
	std::sort(vs.begin(), vs.end());
}
