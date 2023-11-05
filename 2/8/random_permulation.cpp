#include "../../test_alg.h"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>

std::vector<int> algorithm1(const int N)
{
	std::vector<int> random_permulation(N);
	for (int outer_count = 0; outer_count < N;)
	{
		int each_ran_num = rand() % N + 1;
		bool in_vector = false;
		for (int inner_count = 0; inner_count < outer_count; inner_count++)
			if (random_permulation[inner_count] == each_ran_num)
				in_vector = true;
		if (!in_vector)
		{
			random_permulation[outer_count] = each_ran_num;
			outer_count++;
		}
	}
	return random_permulation;
}

std::vector<int> algorithm2(const int N)
{
	std::vector<int> random_permulation(N);
	bool used[N];
	for (int i = 0; i < N; i++)
		used[i] = false;

	for (int i = 0; i < N;)
	{
		int ran_num = rand() % N + 1;
		if (!used[ran_num - 1])
		{
			used[ran_num - 1] = true;
			random_permulation[i] = ran_num;
			i++;
		}
	}
	return random_permulation;
}

std::vector<int> algorithm3(const int N)
{
	std::vector<int> random_permulation(N);
	int i = 1;
	for (auto& x : random_permulation)
		x = i++;
	for (i = 1; i < N; i++)
	{
		std::swap(random_permulation[i], random_permulation[random() % N]);
	}
	return random_permulation;
}

int main(int argc, char* argv[])
{
	using func_type = std::vector<int>(int);
	srand(time(0));
	std::vector<int> amount_of_alg1{250, 500, 1000, 2000},
		amount_of_alg2{25000, 50000, 100000, 200000, 400000, 800000},
		amount_of_alg3{100000,	200000,	 400000, 800000,
					   1600000, 3200000, 6400000};
	my_alg_test<func_type> test1(algorithm1, amount_of_alg1);
	my_alg_test<func_type> test2(algorithm2, amount_of_alg2);
	my_alg_test<func_type> test3(algorithm3, amount_of_alg3);
	test1.test_alg();
	test1.output_minus();
	std::cout << std::endl;
	test2.test_alg();
	test2.output_minus();
	std::cout << std::endl;
	test3.test_alg();
	test3.output_minus();
}
