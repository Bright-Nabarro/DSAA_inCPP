#include "avl_tree.h"
using namespace std;

int main()
{

	AvlTree<int> t1;
	for(int i = 0, j = 100; i <= j; i++, j--)
	{
		t1.insert(i);
		t1.insert(j);
	}
	t1.print_tree(cout);
	for(int i = 0; i < 100; i++)
	{
		assert(t1.contains(i));
	}
}