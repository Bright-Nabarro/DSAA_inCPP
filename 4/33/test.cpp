#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <numeric>
#include "binary_search_tree.h"
using namespace std;

int main()
{
	random_device rd;
	mt19937 gen{rd()};
	vector<int> vi(20);
	iota(begin(vi), end(vi), 1);
	shuffle(begin(vi), end(vi), gen);

	BinarySearchTree<int> t1;
	for(int x: vi)
		t1.insert(x);
	t1.print_tree(cout);
	t1.remove_all_leaves();
	cout << "========\n===========\n---------------\n===========\n===========\n";
	t1.print_tree(cout);
}