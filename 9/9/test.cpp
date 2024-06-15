#include "positive_wg.hpp"
using namespace std;

void print_2d(const auto& v)
{
	for(const auto& line : v)
	{
		for(const auto& x : line)
		{
			print(" -> {}", x);
		}
		println("");
	}
}

void test_initial()
{
	positive_wg<int> g;
	g.add_vec(1);
	auto ret {g.dijkstra(1)};
}

void test_dijkstra(bool display = false)
{
	positive_wg<int> g1;
	g1.add_vec(1);
	g1.add_vec(2);
	g1.add_edge(1, 2, 1);
	auto ret1 { g1.dijkstra(1) };
	if (display)
	{
		print_2d(ret1);
	}
	g1.add_vec(3);
	g1.add_edge(2, 3, 1);
	g1.add_edge(1, 3, 10);
	auto ret2 { g1.dijkstra(1) };
	if (display)
	{
	}
}

int main()
{
	test_initial();
	test_dijkstra(true);
}
