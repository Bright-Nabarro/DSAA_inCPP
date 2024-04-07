#include "avl_tree.h"
#include <iostream>
using namespace std;

int main()
{
	AvlTree<int, less<int>, false> intTree;
	intTree.insert(2);
	intTree.insert(1);
	intTree.insert(4);
	intTree.insert(5);
	intTree.insert(9);
	intTree.insert(3);
	intTree.insert(6);
	intTree.insert(7);
	intTree.print_tree(cout);
}