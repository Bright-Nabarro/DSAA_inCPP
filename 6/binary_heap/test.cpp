#include <iostream>
#include <cassert>
#include <random>
#include <limits>
#include <queue>
#include <numeric>
#include <vector>
#include <ranges>
#include "binary_heap.hpp"

using namespace std;

template<typename Ty>
class Bh : public binary_heap<Ty, std::less<Ty> >
{
public:
	using binary_heap<Ty, std::less<Ty>>::binary_heap;
	[[nodiscard]] constexpr
	const Ty& min()  const noexcept
	{ return binary_heap<Ty,  std::less<Ty>>::priority(); }
};

void test_ini()
{
	Bh<int> b;
}

void test_insert()
{
	Bh<int> b1;
	assert(b1.empty());
	for (int i = 1; i <= 50; i++)
	{
		assert(b1.size() == i-1);
		b1.insert(i);
		assert(b1.size() == i);
		assert(b1.min() == 1);
	}
	
	assert(b1.min() == 1);

	Bh<int> b2;
	for (int i = 50; i > 0; i--)
	{
		b2.insert(i);
		assert(b2.size() == 51-i);
		assert(b2.min() == i);
	}

	assert(b2.min() == 1);

	int min3 = numeric_limits<int>::max();
	Bh<int> b3;
	static random_device rd;
	static mt19937 gen;
	gen.seed(rd());
	static uniform_int_distribution<int> dist{1, 1000};
	for(int i = 0; i < 500; i++)
	{
		int value = dist(gen);
		if (value < min3)
			min3 = value;
		b3.insert(value);
	}
	assert(b3.min() == min3);
	assert(b3.size() == 500);
}

void test_remove()
{
	Bh<int> b1;
	for(int i = 0; i < 50; i++)
	{
		b1.insert(i);
	}

	for(int i = 0; i < 50; i++)
	{
		assert(b1.min() == i);
		b1.delete_priority();
		assert(b1.size() == 49-i);
	}
	
	Bh<int> b2;
	priority_queue<int, vector<int>, greater<int>> q2;
	static random_device rd;
	static mt19937 gen;
	gen.seed(rd());
	static uniform_int_distribution<int> dist1{1, 100};

	for(int i = 0; i < 1000; i++)
	{
		int value {dist1(gen)};
		q2.push(value);
		b2.insert(value);
	}
	for(int i = 0; i < 1000; i++)
	{
		//assert(b2.min() == q2.top());
		b2.delete_priority();
		q2.pop();
		assert(b2.size() == 999-i);
	}

	Bh<int> b3;
	priority_queue<int, vector<int>, greater<int>> q3;
	static uniform_int_distribution<int> dist2{1, 10'000'000};
	for(int i = 0; i < 1'000; i++)
	{
		int value {dist2(gen)};
		q3.push(value);
		b3.insert(value);
	}
	
	for(int i = 0; i < 1'000; i++)
	{	
		assert(b3.min() == q3.top());
		b3.delete_priority();
		q3.pop();
		assert(b3.size() == 999-i);
	}
}

void test_build()
{
	Bh<int> b1 {{8}};
	assert(b1.min() == 8);
	Bh<int> b2 {{2,1}};
	assert(b2.min() == 1);
	
	vector<int> vec3(100);
	iota(vec3.rbegin(), vec3.rend(), 1);
	Bh<int> b3 {vec3};
	assert(b3.min() == 1);

	static random_device rd;
	static mt19937 gen;
	gen.seed(rd());
	static uniform_int_distribution<int> dist1{1, 10000};
	vector<int> vec4(1000);
	auto random_view = views::iota(0, static_cast<int>(vec4.size()))
					 | views::transform([&](int) { return dist1(gen); });
	ranges::copy(random_view, vec4.begin());
	Bh<int> b4{vec4};
	assert(b4.min() == ranges::min(vec4));
}

void test_all()
{
	static random_device rd;
	static mt19937 gen;
	gen.seed(rd());
	static uniform_int_distribution<int> dist1{1, 10000};
	priority_queue<int, vector<int>, greater<int>> q;
	Bh<int> b;
	auto random_view = views::iota(0, 1000)
					 | views::transform([&](int) { return dist1(gen); });
	ranges::for_each(random_view, [&](int n){ q.push(n); b.insert(n); });
	auto ass = [&](int) {
		assert(q.top() == b.min());
		q.pop();
		b.delete_priority();
	};
	ranges::for_each(views::iota(0, 1000), ass);
}

int main()
{
	test_ini();
	test_insert();
	test_remove();
	test_build();
	test_all();

	cout << "o((>ω< ))o\n";
}

