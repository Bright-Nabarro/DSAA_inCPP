#include <random>
#include <cassert>
#include <iostream>
#include <functional>
#include <array>
#include <vector>
#include "cubic_probing.h"
#include "next_prime.h"
using namespace std;

template<size_t N>
void test(function<pair<bool, size_t>(int, vector<optional<int>>&)> hash_method,
		  const array<int, N>& arr, size_t hashTableSize)
{
	vector<optional<int>> hashTable(hashTableSize);
	size_t fail {0}, totalCollision {0};
	for(int x: arr)
	{
		auto ret = hash_method(x, hashTable);
		if(!ret.first)		//hash faild
			++fail;
		totalCollision += ret.second;
	}
	cout << "fail:\t\t" << fail << endl;
	cout << "total collision:\t" << totalCollision << endl;
}

int main()
{
	random_device rd;
	mt19937 gen{ rd() };
	uniform_int_distribution<int> dist {1, 1'999'999};
	array<int, 500'000> arr;
	for(auto& x: arr)
		x = dist(gen);

	const size_t hashTableSize {next_prime(1'000'000)};

	cout << "quadratic:\n";
	test(quadratic_probing, arr, hashTableSize);
	cout << "cubic:\n";
	test(cubic_probing, arr, hashTableSize);
	//vector<optional<int>> table(13);
	//auto ret = cubic_probing(1, table);
	//assert(ret.second == 0);
	//ret = cubic_probing(1, table);
	//assert(ret.second == 1);

}