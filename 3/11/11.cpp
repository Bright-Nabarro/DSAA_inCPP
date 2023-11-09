#include "simple_single_list.h"
#include <random>
#include <ctime>

int main()
{
	std::default_random_engine gen(time(0));
	std::uniform_int_distribution<int> ud(0, 20);
	single_list<int> sli;
	for(int i = 0; i < 10; i++)
		sli.insert(ud(gen));
	sli.print();
}
