#include <cassert>
#include <vector>
#include <functional>
#include <algorithm>
#include "sort.hpp"

using namespace std;

void test_basic(function<void(std::span<int>)> sort_alg)
{
	vector<int> arr1 { 1, 2, 3 };
	const auto arrC1 { arr1 };
	sort_alg(arr1);
	assert(arrC1 == arr1);
}

int main()
{
	//insertion sort test
	test_basic(insertion_sort<int>);
}
