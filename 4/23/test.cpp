#include "avl_tree.h"
using namespace std;

int main()
{
	AvlTree<int> t1;
	check_property(t1);
	AvlTree<int> t2;
	for(int i = 0; i < 600; i++)
		t2.insert(i);
	check_property(t2);
	AvlTree<int> t3;
	for(int i = 250, j = 251; i > 0 && j < 500; i--, j++)
	{
		t3.insert(i);
		t3.insert(j);
	}
	check_property(t3);
}