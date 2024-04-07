#include <cassert>
#include <iostream>
#include <numeric>
#include "binary_heap.hpp"
using namespace std;

//#define PRINT_NODE

void test_ini()
{
	BinaryHeap<int> bh1;
#ifdef PRINT_NODE
	bh1.print_heap(cout);
#endif

	vector<int> vi {1, 2, 3, 4, 6, 5};
	BinaryHeap<int> bh2{vi};

#ifdef PRINT_NODE
	bh2.print_heap(cout);
#endif
}

void test_empty()
{
	BinaryHeap<int> bh1;
	assert(bh1.is_empty());
	vector<int> vi2 {3};
	BinaryHeap<int> bh2 {vi2};
	assert(!bh2.is_empty());
	BinaryHeap<int> bh3;
	bh3.insert(1);
	assert(!bh3.is_empty());
	BinaryHeap<int> bh4;
	for(int i = 100; i > 0; i--)
	{
		bh4.insert(i);
	}
	assert(!bh4.is_empty());
}

void test_insert()
{
	BinaryHeap<int> bh1;
	bh1.insert(1);
	BinaryHeap<int> bh2;
	for(int i = 20; i > 0; i--)
	{
		bh2.insert(i);
	}
#ifdef PRINT_NODE
	bh2.print_heap(cout);
#endif
}

void test_min()
{
	BinaryHeap<int> bh1;
	try
	{
		[[maybe_unused]] auto trash = bh1.min();
		assert(true);
	} catch(out_of_range& e) {
		//yes;
	} catch(...) {
		assert(true);
	}

	BinaryHeap<int> bh2;
	bh2.insert(0);
	assert(bh2.min() == 0);
	for(int i = 1; i < 100; i++)
	{
		bh2.insert(i);
		assert(bh2.min() == 0);
	}

	BinaryHeap<int> bh3;
	for(int i = 100; i > 0; i--)
	{
		bh3.insert(i);
		assert(bh3.min() == i);
	}
}

void test_remove()
{
	BinaryHeap<int> bh1;
	try {
		bh1.delete_min();
		assert(true);
	} catch(underflow_error& e) {
		// success
	} catch(...) {
		assert(true);
	}

	vector<int> vi2 {1, 2, 3, 4, 5, 6};
	BinaryHeap<int> bh2{vi2};
	bh2.delete_min();
	assert(bh2.min() == 2);
	bh2.delete_min();
	assert(bh2.min() == 3);
	bh2.delete_min();
	assert(bh2.min() == 4);
	bh2.delete_min();
	assert(bh2.min() == 5);
	bh2.delete_min();
	assert(bh2.min() == 6);

	vector<int> vi3(100);
	iota(vi3.begin(), vi3.end(), 1);
	BinaryHeap<int> bh3{vi3};
	for(int i = 0; i < 100; i++)
	{
		assert(bh3.min() == i+1);
		bh3.delete_min();
	}
}

void test_print()
{
	BinaryHeap<int> bh1;
	for(int i = 0; i < 300; i++)
		bh1.insert(i);
	bh1.print_heap(cout);
}

int main()
{
	test_ini();
	test_empty();
	test_insert();
	test_min();
	test_remove();
	test_print();
	cout << "o((>ω< ))o" << endl;
}