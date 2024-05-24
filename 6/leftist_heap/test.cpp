#include <cassert>
#include <iostream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <ranges>
#include <random>
#include "leftist_heap.hpp"
using namespace std;

using IntHeap = leftist_heap<int, less<int>>;

void test_ini()
{
	IntHeap h1;
}

void test_push()
{
	IntHeap h1;
	assert(h1.empty());
	auto v1 = views::iota(1, 50);
	ranges::for_each(v1, [&](int n){ h1.push(n); });
	assert(!h1.empty());
	//h1.print(cout);
	//h1.print_npl(cout);

	IntHeap h2;
	auto v2 = views::iota(1, 20) | views::reverse;
	ranges::for_each(v2, [&](int n){
			h2.push(n);
		}
	);
	//h2.print(cout);
	//h2.print_npl(cout);
	
	IntHeap h3;
	static random_device rd;
	static mt19937 gen {rd()};
	static uniform_int_distribution<int> dist{1, 100000};
	auto v3 = views::transform(views::iota(1, 100), [&](int){return dist(gen);});
	ranges::for_each(v3, [&](int n){ return h3.push(n); });
	//h3.print(cout);
	//cout << "\n\n\n";
	//h3.print_npl(cout);
}

void test_pop()
{
	IntHeap h1;
	h1.push(1);
	assert(h1.top() == 1);
	h1.pop();
	assert(h1.empty());

	IntHeap h2;
	auto v2 = views::iota(1, 50);
	auto insert2 = [&](int n) {
		h2.push(n);
		assert(h2.top() == 1);
	};
	auto remove2 = [&](int n) {
		h2.pop();
		assert(h2.empty() || h2.top() == n+1);
	};
	ranges::for_each(v2, insert2);
	ranges::for_each(v2, remove2);

	IntHeap h3;
	priority_queue<int, vector<int>, greater<int>> q3;
	auto v3 = views::iota(1, 1000);
	static random_device rd;
	static mt19937 gen {rd()};
	static uniform_int_distribution<int> dist{1, 100000};

	auto insert3 = [&](int n) {
		int value = dist(gen);
		h3.push(value);
		q3.push(value);
	};
	auto remove3 = [&](int n) {
		assert(h3.top() == q3.top());
		h3.pop();
		q3.pop();
		assert(h3.empty() == q3.empty());
		if (h3.empty())
			return;
		assert(h3.top() == q3.top());

	};
	ranges::for_each(v3, insert3);
	ranges::for_each(v3, remove3);
}

void test_merge()
{
	IntHeap h1;
	IntHeap h2;
	h1.push(2);
	h2.push(1);
	h1.merge(h2);
	assert(h2.empty());
	assert(h1.top() == 1);

	IntHeap h3;
	IntHeap h4;
	auto dist = views::iota(1, 100);
	vector<int> numbers{dist.begin(), dist.end()};

	static random_device rd;
	static mt19937 gen {rd()};

	ranges::shuffle(numbers, gen);
	
	size_t counter {0};
	ranges::for_each(views::iota(1, 20), [&](int n){
			h3.push(numbers[counter++]);
			h4.push(numbers[counter++]);
		}
	);

	h3.merge(h4);
	//h3.print(cout);
	//cout << "\n\n\n";
	//h3.print_npl(cout);
}

void test_clone()
{
	ostringstream ossm1, ossm2;
	IntHeap h1;
	ranges::for_each(views::iota(1, 20), [&](int n) {
			h1.push(n);
		}
	);
	IntHeap h2{h1};
	h1.print(ossm1);
	h2.print(ossm2);
	assert(ossm1.str() == ossm2.str());

	ossm1.clear();
	ossm2.clear();
	static random_device rd;
	static mt19937 gen {rd()};
	auto v = views::iota(1, 100);
	vector<int> arr {v.begin(), v.end()};
	ranges::shuffle(arr, gen);

	IntHeap h3;
	ranges::for_each(arr, [&](int n) { h3.push(n); });
	h3.print(ossm1);
	IntHeap h4;
	h4 = h3;
	h4.print(ossm2);
	assert(ossm1.str() == ossm2.str());
}

int main()
{
	test_ini();
	test_push();
	test_pop();
	test_merge();
	test_clone();
	cout << "o((>ω< ))o\n";
}
