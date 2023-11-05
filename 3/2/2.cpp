#include "list.h"
#include "single_list_for_2.h"
#include <algorithm>
#include <forward_list>
#include <iostream>
#include <iterator>
#include <random>
#include <iomanip>

int main()
{
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_int_distribution<int> ud(10, 40);

	myds::single_list<int> l1;
	auto ran_num = [&gen, &ud] { return ud(gen); };
	std::generate_n(std::back_inserter(l1), 10, ran_num);
	my_adt::list<int> l2;
	std::generate_n(std::back_inserter(l2), 10, ran_num);

	for(int i = 0; i < 10; i++)
		std::cout << std::setw(2) << std::left << i << " ";
	std::cout << std::endl;


	std::copy(l1.begin(), l1.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
	l1.swap_adjacent(5);
	std::copy(l1.begin(), l1.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::copy(l2.begin(), l2.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}
