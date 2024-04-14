#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include "binary_search_tree.h"
using namespace std;

template<typename Ty>
void shuffle(vector<Ty>& vec)
{
	static random_device rd;
	static mt19937 gen(rd());
	size_t scale = vec.size();
	for(size_t i = scale; static_cast<long>(i) > 0; i--)
	{
		uniform_int_distribution<size_t> dist{0, scale};
		swap(vec[i], vec[dist(gen)]);	
	}
}

int main()
{
	BinarySearchTree<long> tree;
	vector<long> vec(30);
	iota(begin(vec), end(vec), 1);
	shuffle(vec);
	for(auto x: vec)
		tree.insert(x);
	
	tree.print_range(10, 20, cout);
	cout << '\n';
}