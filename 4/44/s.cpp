#include <string>
#include "tree.h"
using namespace std;

int main()
{
	Tree<string> t{"/"};	//root index
	//	"/dsaa"
	auto* dsaa = t.insert_nextLevel("DSAA", t.get_root());
	// "/dsaa/.vscode"
	t.insert_nextLevel(".vscode", dsaa);
	// "/dsaa/1"
	t.insert_sibling("1", dsaa);
	// "/dsaa/2"
	t.insert_sibling("2", dsaa);
	// "/dsaa/3"
	t.insert_sibling("3", dsaa);
	// "/dsaa/4"
	auto* fdr4 = t.insert_sibling("4", dsaa);
	// "/dsaa/4/39"
	auto* _4_39 = t.insert_nextLevel("39", fdr4);
	// "/dass/4/44"
	auto* _4_44 = t.insert_nextLevel("44", fdr4);
	t.insert_nextLevel("s.cpp", _4_44);
	t.insert_nextLevel("tree.h", _4_44);
	auto* _4_39_s = t.insert_nextLevel("s.cpp", _4_39);
	t.insert_sibling("a.out", _4_39_s);
	t.insert_sibling("avl_tree.h", _4_39_s);
	t.print_tree(cout);
}