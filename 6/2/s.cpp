#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <iterator>
#include "../binary_heap/binary_heap.hpp"
using namespace std;

using IntHeap = binary_heap<int, less<int>>;

int main()
{
	vector arr { 10, 12, 1, 14, 6, 5, 8, 15, 3, 9, 7, 4, 11, 13, 2 };
	IntHeap h1;
	ranges::for_each(arr, [&](int n) { h1.push(n); });
	IntHeap h2 {arr};

	cout << "h1\n";
	h1.print(cout);
	cout << "h2\n";
	h2.print(cout);
}
