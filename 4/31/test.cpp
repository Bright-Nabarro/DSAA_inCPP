#include <random>
#include <vector>
#include <numeric>
#include <algorithm>
#include "binary_search_tree.h"
using namespace std;

int main()
{
	random_device rd;
	mt19937 gen{rd()};
	vector<int> vi(30);
	iota(begin(vi), end(vi), 1);
	shuffle(begin(vi), end(vi), gen);

	typedef typename BinarySearchTree<int>::BinaryNode intTree;
	BinarySearchTree<int> t1;
	for(auto& x: vi)
	{
		t1.insert(x);
	}

	t1.print_tree(cout);
	cout << "==========================\n===========================\n";
	cout << t1.size() << endl;
	cout << "nodes: " << number_of_nodes<int>(t1.get_root()) << endl;
	cout << "leaves: " << number_of_leaves<int>(t1.get_root()) << endl;
	cout << "full nodes: " << number_of_full_nodes<int>(t1.get_root()) << endl;
}