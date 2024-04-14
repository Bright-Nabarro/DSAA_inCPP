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
	vector<int> vi(30);
	iota(begin(vi), end(vi), 1);
	shuffle(begin(vi), end(vi), gen);

	using IntTree = BinarySearchTree<int>;
	IntTree t1;
	for(int x: vi)
		t1.insert(x);
	t1.print_tree(cout);
	cout << boolalpha << ordered<IntTree>(t1.get_root()) << endl;
}