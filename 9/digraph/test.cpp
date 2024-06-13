#include <string>
#include "graph.hpp"
using namespace std;

void test_top_sort()
{
	digraph<string> snt;
	string c11 { "C++" }, c12 { "JAVA" };
	string c21 { "python" }, c22 { "离散" };
	string c31 { "计组" }, c32 { "数据库" };
	string c41 { "操作系统" }, c42 { "设计模式" };
	
	snt.add_vec(c11);
	snt.add_vec(c12);
	snt.add_vec(c21);
	snt.add_vec(c22);
	snt.add_vec(c31);
	snt.add_vec(c32);
	snt.add_vec(c41);
	snt.add_vec(c42);

	snt.add_edge(c11, c21);
	snt.add_edge(c11, c22);
	snt.add_edge(c12, c21);
	snt.add_edge(c12, c22);

	snt.add_edge(c21, c22);
	snt.add_edge(c22, c31);
	snt.add_edge(c22, c32);

	snt.add_edge(c32, c31);
	snt.add_edge(c31, c41);

	snt.add_edge(c31, c42);

	snt.add_edge(c42, c41);

	snt.display_dot();
	
	auto ret { snt.top_sort() };
	for(const auto& x : ret)
		print("{} ", x);
	println("");

}

void test_dfs()
{
	digraph<int> g;
	for(int vec = 1; vec <= 7; vec++)
		g.add_vec(vec);
	g.add_edge(1, 2);
	g.add_edge(1, 4);
	g.add_edge(2, 4);
	g.add_edge(2, 5);
	g.add_edge(4, 3);
	g.add_edge(4, 5);
	g.add_edge(4, 6);
	g.add_edge(4, 7);
	g.add_edge(5, 7);
	g.add_edge(7, 6);
	g.add_edge(3, 6);
	g.add_edge(3, 1);
	g.display_dot();
}

void test_basic_top_sort()
{
	digraph<int> g;
	for (int vec { 1 }; vec <= 5; ++vec)
		g.add_vec(vec);
	for (int i {1}; i < 5; i++)
		g.add_edge(i, i+1);

	g.display_dot();
	g.display_degree();

	auto ret { g.top_sort() };
	ranges::for_each(ret, [](const auto& x){ print("{} ", x); });
	println("");
}

void test_basic_bfs()
{
	digraph<int> g;
	for (int vec { 1 }; vec <= 5; ++vec)
		g.add_vec(vec);
	for (int i {1}; i < 5; i++)
		g.add_edge(i, i+1);
	
	auto ret { g.bfs(1, 5) };
	ranges::for_each(ret, [](const auto& x){ print("{} ", x); });
	println("");

}

int main()
{
	test_basic_bfs();
}

