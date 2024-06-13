#include <vector>
#include <print>
#include "graph.hpp"
using namespace std;

//using Figure 9.81 ( unweight )

int main()
{
	const auto s { "s"s };
	const auto t { "t"s };
	const auto A { "A"s };
	const auto B { "B"s };
	const auto C { "C"s };
	const auto D { "D"s };
	const auto E { "E"s };
	const auto F { "F"s };
	const auto G { "G"s };
	const auto H { "H"s };
	const auto I { "I"s };

	vector<string> vecs { s, t, A, B, C, D, E, F, G, H, I };
	digraph<string> g;

	for ( const auto& vec : vecs )
	{
		g.add_vec(vec);
	}
	g.add_edge(s, A);
	g.add_edge(s, G);
	g.add_edge(s, D);

	g.add_edge(A, E);
	g.add_edge(A, B);

	g.add_edge(B, C);

	g.add_edge(C, t);

	g.add_edge(D, A);
	g.add_edge(D, E);

	g.add_edge(E, C);
	g.add_edge(E, F);
	g.add_edge(E, I);

	g.add_edge(F, t);
	g.add_edge(F, C);

	g.add_edge(G, D);
	g.add_edge(G, E);
	g.add_edge(G, H);

	g.add_edge(H, E);
	g.add_edge(H, I);

	g.add_edge(I, F);
	g.add_edge(I, t);

	println("indegree");
	println("----");
	g.display_degree(stdout);
	println("----");
	println("graph");
	g.display_dot(stdout);
	println("----");
	println("topsort");
	auto ret { g.top_sort() };
	print("{} ", *ret.begin());
	for (size_t i {1}; i < ret.size(); i++)
		print("-> {} ", ret[i]);
	println("");
}
