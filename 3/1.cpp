#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <random>
#include <vector>

void printLots(const std::list<int>& L, const std::list<int>& P)
{
	std::vector<int> vec_L(L.size());
	std::copy(L.cbegin(), L.cend(), vec_L.begin());
	auto P2L = [&vec_L](const int n) { std::cout << vec_L[n] << " "; };

	std::for_each(P.cbegin(), P.cend(), P2L);
}

int main()
{
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_int_distribution<int> ud(0, 9);

	std::list<int> L, P;
	auto ran_num = [&gen, &ud] { return ud(gen); };
	std::generate_n(std::back_inserter(L), 10, ran_num);
	std::generate_n(std::back_inserter(P), 10, ran_num);

	std::cout << "D: ";
	for (int i = 0; i < 10; i++)
		std::cout << i << " ";
	std::cout << std::endl;

	std::cout << "L: ";
	std::copy(L.cbegin(), L.cend(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::cout << "P: ";
	std::copy(P.cbegin(), P.cend(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl << std::endl;

	std::cout << "O: ";
	printLots(L, P);
	std::cout << std::endl;
}