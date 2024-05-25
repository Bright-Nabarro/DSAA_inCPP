#include <cassert>
#include <vector>
#include <functional>
#include <algorithm>
#include <ranges>
#include <iostream>
#include <random>
#include "sort.hpp"
using namespace std;

random_device rd;
mt19937 gen{rd()};

void print(span<int> arr)
{
	for(int x : arr)
		cout << x << " ";
	cout << endl;
}

void test_basic(function<void(std::span<int>)> sort_alg)
{
	vector<int> arr1 { 1, 2, 3, 4, 5 };
	const auto arrC1 { arr1 };
	sort_alg(arr1);
	assert(arr1 == arrC1);
	
	vector<int> arr2;
	ranges::copy(views::iota(1, 100), back_inserter(arr2));
	const auto arrC2 { arr2 };
	sort_alg(arr2);
	assert(arr2 == arrC2);
	
	vector<int> arr3;
	ranges::copy(views::iota(1, 100) | views::reverse, back_inserter(arr3));
	auto arrC3 { arr3 };
	sort_alg(arr3);
	sort(arrC3.begin(), arrC3.end());
	assert(arrC3 == arr3);

	uniform_int_distribution<int> dist{1, 100};
	vector<int> arr4;
	ranges::for_each(views::iota(1, 1001), [&](int) { arr4.push_back(dist(gen)); });
	sort_alg(arr4);
	assert(is_sorted(arr4.cbegin(), arr4.cend()));
}

int main()
{
	//insertion sort test
	test_basic(insertion_sort<int>);
}
