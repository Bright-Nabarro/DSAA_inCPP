#include <format>
#include "avl_tree.h"
using namespace std;

int main()
{
	AvlTree<int> tree;
	for(int i = 0; i < 100; i += 5)
		tree.insert(i);
	auto vec { tree.generate_point() };
	for(auto x: vec)
	{
		auto[point, ele] {x};
		cout << format("({}, {})\t[{}]\n", point.first, point.second, ele);
	}
	//tree.print_tree(cout);
}