#include <cassert>
#include <iostream>
#include <ranges>
#include <algorithm>
#include <queue>
#include <random>
#include <print>
#include "binomial_queue.hpp"
using namespace std;

static random_device rd;
static mt19937 gen { rd() };

void test_ini()
{
	binomial_queue<int> bq;
}

void test_push()
{
	binomial_queue<int> bq1;
	assert(bq1.empty());
	ranges::for_each(views::iota(1, 101) | views::reverse,
					 [&](int n) {
				bq1.push(n);
				assert(bq1.top() == n);
			}
		);
	//bq1.print(cout);
	assert(bq1.top() == 1);
	assert(bq1.size() == 100);
	uniform_int_distribution<int> dist {1, 10000};
	priority_queue<int, vector<int>, ::std::greater<int>> pq2;
	binomial_queue<int> bq2;
	auto randomGen = views::iota(1, 1000) | views::transform([&](int) { return dist(gen); });
	auto opr2 = [&](int n) {
		pq2.push(n);
		bq2.push(n);
		assert(pq2.top() == bq2.top());
	};
	ranges::for_each(randomGen, opr2);
}

void test_pop()
{
	binomial_queue<int> bq1;
	bq1.push(2);
	bq1.push(1);
	bq1.pop();
	assert(bq1.top() == 2);
	bq1.pop();
	assert(bq1.empty());
	
	binomial_queue<int> bq2;
	ranges::for_each(views::iota(1, 109), [&](int n){ bq2.push(n); });
	auto opr2 = [&](int n) {
		assert(bq2.top() == n);
		bq2.pop();
		assert (bq2.top() == n+1);
	};
	ranges::for_each(views::iota(1, 108), opr2);

	binomial_queue<int> bq3;
	priority_queue<int, vector<int>, greater<int>> pq3;
	uniform_int_distribution<int> dist{1, 10001};
	ranges::for_each(views::iota(1, 1001), [&](int) {
				int num { dist(gen) };
				bq3.push(num);
				pq3.push(num);
			}
		);
	ranges::for_each(views::iota(1, 1000), [&](int) {
				assert(bq3.top() == pq3.top());
				bq3.pop();
				pq3.pop();
				assert(bq3.top() == pq3.top());
			}
		);
	assert(bq3.size() == 1);
	bq3.pop();
	assert(bq3.empty());
}

void test_merge()
{
	binomial_queue<int> bq1, bq2;
	uniform_int_distribution<int> dist{1, 100'000};
	ranges::for_each(views::iota(1, 10001), [&](int)
			{
				bq1.push(dist(gen));
				bq2.push(dist(gen));
			}
		);
	const int minNum { min(bq1.top(), bq2.top()) };
	bq1.merge(bq2);
	assert(bq2.empty());
	assert(bq1.top() == minNum);

	//other merge operations tested in push and pop;
}

void test_clone()
{
	binomial_queue<int> bq1, bq2;
	uniform_int_distribution<int> dist{1, 10000};
	ranges::for_each(views::iota(1, 1000), [&](int) { bq1.push(dist(gen)); });
	bq2 = bq1;
	assert(bq2.top() == bq1.top());
	ranges::for_each(views::iota(1, 999), [&](int) {
				bq1.pop();
				bq2.pop();
				assert(bq1.top() == bq2.top());
			}
		);
	bq1.pop();
	bq2.pop();
	assert(bq1.empty());
	assert(bq2.empty());
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
