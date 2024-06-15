#include <iostream>
#include <cassert>
#include <random>
#include <limits>
#include <queue>
#include <numeric>
#include <vector>
#include <ranges>
#include <print>

#define DEBUG
#include "binary_heap.hpp"
#undef DEBUG

using namespace std;

template<typename Ty>
class Bh : public binary_heap<Ty, std::less<Ty> >
{
public:
	using binary_heap<Ty, std::less<Ty>>::binary_heap;
	[[nodiscard]] constexpr
	const Ty& min()  const noexcept
	{ return binary_heap<Ty,  std::less<Ty>>::top(); }
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
		b1.push(i);
		assert(b1.size() == i);
		assert(b1.min() == 1);
	}
	
	assert(b1.min() == 1);

	Bh<int> b2;
	for (int i = 50; i > 0; i--)
	{
		b2.push(i);
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
		b3.push(value);
	}
	assert(b3.min() == min3);
	assert(b3.size() == 500);
}

void test_re_scale(size_t n)
{
	binary_heap<int, less<int>> b;
	for(int i = 0; i < n; i++)
		b.push(i);
	for(int i = 0; i < n; i++)
	{
		assert(b.top() == i);
		b.pop();
		assert(b.size() == n-1-i);
	}
}

void test_remove_basic()
{
	for(size_t i = 0; i < 10000; i++)
		test_re_scale(i);
}

void test_remove()
{
	Bh<int> b;
	b.push(1);
	b.push(2);
	b.push(3);
	b.pop();
	if (b.top() != 2)
		b.print(cout);
	b.pop();
	if (b.top() != 3)
		b.print(cout);
	Bh<int> b1; for(int i = 0; i < 10; i++)
	{
		b1.push(i);
	}

	for(int i = 0; i < 10; i++)
	{
		assert(b1.min() == i);
		b1.pop();
		assert(b1.size() == 9-i);
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
		b2.push(value);
	}
	for(int i = 0; i < 1000; i++)
	{
		assert(b2.min() == q2.top());
		b2.pop();
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
		b3.push(value);
	}
	
	for(int i = 0; i < 1'000; i++)
	{	
		if (b3.min() != q3.top())
			print("{}\t{}\n", b3.min(), q3.top());
		b3.pop();
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
	ranges::for_each(random_view, [&](int n){ q.push(n); b.push(n); });
	auto ass = [&](int) {
		assert(q.top() == b.min());
		q.pop();
		b.pop();
	};
	ranges::for_each(views::iota(0, 1000), ass);
}

void test_temp()
{
	vector<int> vec { 1, 2, 3, 4, 5 };
	binary_heap<int, std::less<int>> bh { vec };
	if (bh.top() != 1)
		bh.print(cout);
}


// new test
struct s1
{
	int a;
	int b;

	[[nodiscard]]
	auto operator<=> (const s1& rhs) const
	{
		return a + b <=> rhs.a + rhs.b;
	}
	[[nodiscard]]
	bool operator== (const s1& rhs) const
	{
		return a + b == rhs.a + rhs.b;
	}
};


void test_emplace(bool needDisplay = false)
{
	binary_heap<s1> b1;
	b1.emplace(1, 1);
	b1.emplace(2, 1);

	while(!b1.empty())
	{
		if (needDisplay)
			println("a: {}, b: {}", b1.top().a, b1.top().b);
		b1.pop();
	}

	binary_heap<s1> b2;
	priority_queue<s1, vector<s1>, greater<s1>> q2;
	static mt19937 gen { random_device{}() };
	uniform_int_distribution dist { 1, 100 };

	for(size_t i = 0; i < 1000; i++)
	{
		int a { dist(gen) };
		int b { dist(gen) };

		b2.emplace(a, b);
		q2.emplace(a, b);
	}
	while(!q2.empty())
	{
		assert(q2.size() == b2.size());
		assert(b2.top() == q2.top());
		q2.pop();
		b2.pop();
	}
}

struct s2
{
	int a;
	bool b;
};

void test_cpr_ini(bool needDisplay = false)
{
	auto cpr = [](const s2& lhs, const s2& rhs) { 
		if (lhs.b == rhs.b)
			return lhs.a < rhs.b;
		return lhs.a < rhs.a;
	};
	
	binary_heap<s2, decltype(cpr)> h1{ cpr };
	h1.emplace(1, true);
	h1.emplace(2, false);

	while (!h1.empty())
	{
		if (needDisplay)
			println("{} {}", h1.top().a, h1.top().b);
		h1.pop();
	}
}

void test_find(bool needDisplay = false)
{
	
}

void test_erase(bool needDisplay = false)
{
}

int main()
{
	test_ini();
	test_insert();
	//test_remove_basic();
	for(int i = 0; i < 100; i++)
		test_remove();
	test_build();
	test_all();
	test_temp();

	//new method
	test_emplace();
	test_cpr_ini();
	test_find(true);
	test_erase();

	cout << "o((>ω< ))o\n";
}

