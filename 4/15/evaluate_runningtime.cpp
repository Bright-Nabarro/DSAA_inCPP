#include <iostream>
#include <chrono>
#include <random>
#include <numeric>
#include <algorithm>
#include "avl_tree.h"
#include "bc_tree.h"
using namespace std;
using IntTreeA = AvlTree<long, less<long>, false>;
using IntTreeB = B_RemoveTree<long, less<long>, false>;
using IntTreeC = C_RemoveTree<long, less<long>, false>;

auto check_cost(const auto& seq, auto scale, auto& tree)
{
	for(auto x: seq)
		tree.insert(x);
	const long limit = seq.size()/2;

	auto begin = chrono::high_resolution_clock::now();

	for(int i = 0; i < limit; i++)
		tree.erase(seq[i]);

	auto end = chrono::high_resolution_clock::now();

	auto result = end - begin;
	return result;
}

int main()
{
	random_device rd;
	mt19937 gen(rd());
	const pair<long, long> scale { -10'000'000, 10'000'000 };
	vector<long> seq (scale.second);
	iota(begin(seq), end(seq), scale.first);
	shuffle(begin(seq), end(seq), gen);

	IntTreeA A;
	auto aCost = check_cost(seq, scale, A);
	cout << "a spend: " 
		 << chrono::duration_cast<chrono::milliseconds>(aCost).count()
		 << "ms" << endl;
	
	IntTreeB B;
	auto bCost = check_cost(seq, scale, B);
	cout << "b spend: " 
		 << chrono::duration_cast<chrono::milliseconds>(bCost).count()
		 << "ms" << endl;

	IntTreeC C;
	auto cCost = check_cost(seq, scale, C);
	cout << "c spend: "
		 << chrono::duration_cast<chrono::milliseconds>(bCost).count()
		 << "ms" << endl;
}