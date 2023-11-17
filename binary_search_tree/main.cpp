#include "binary_search_tree.h"

int main()
{
	mystl2::BinarySearchTree<int> t;
	for(int i = 0; i < 9; i++)
		t.insert(i);
	t.print_tree();
}
