#include "weight_graph.hpp"
#include "weight_graph_mst.hpp"
using namespace std;

template<typename Func, typename... Funcs>
void basic_test_func(Func func, Funcs... funcs)
{
	if constexpr (sizeof...(funcs) > 0)
	{
		func(false);
		basic_test_func(funcs...);
	}
	else
	{
		func(true);
	}
}

void test_initial(bool display)
{
	weight_graph<int> g1;
	g1.add_vec(1);
	g1.add_vec(2);
	g1.add_edge(1, 2, 114514);
	if (display)
		g1.display_dot();
}

void test_display(bool display)
{
	weight_graph<int> g1;
	g1.add_vec(1);
	g1.add_edge(1, 1, 0);
	if (display)
		g1.display_dot();

	weight_graph<string> g2;
	const string& nj { "NanJing"s };
	const string& cc { "ChangChun"s };
	g2.add_vec(nj);
	g2.add_edge(nj, nj, 3);
	g2.add_vec(cc);
	g2.add_edge(cc, nj, 12);
	g2.display_dot();

	weight_graph<int> g3;
	g3.add_vec(1);
	g3.add_vec(2);
	g3.add_vec(3);
	
	g3.add_edge(1, 2, 0);
	g3.add_edge(2, 3, 0);
	
	g3.display_dot();

	weight_graph<int> g4;
	for(int i {0}; i < 10; i++)
	{
		g4.add_vec(i);
	}
	for(int i {0}; i < 9; i++)
	{
		g4.add_edge(i, i+1, 0);
	}
	g4.add_edge(0, 9, 0);
	g4.display_dot();

	weight_graph<int> g5;
	for(int i {1}; i <= 5; i++)
	{
		g5.add_vec(i);
	}
	for(int i {1}; i < 5; i++)
	{
		g5.add_edge(i, i+1, 0);
	}
	g5.add_edge(1, 5, 0);
	g5.add_edge(2, 5, 1);
	g5.add_edge(5, 3, 2);
	g5.add_edge(3, 1, 3);
	g5.add_edge(1, 4, 4);
	g5.add_edge(4, 2, 5);
	g5.display_dot();
}

void test_initial_mst(bool)
{
	weight_graph_mst<int> g1;
}

int main()
{
	basic_test_func(
		test_initial
		, test_display
		//, test_initial_mst
	);
}
