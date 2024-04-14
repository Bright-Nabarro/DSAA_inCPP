#include <iostream>
#include "avl_tree.h"
using namespace std;

int main()
{
	AvlTree<int> tree;
	for(int i = 0; i < 20; i++)
	{
		tree.insert(i);
	}
	tree.draw(cout);
}