#include <cassert>
#include "separate_chaining.h"
using namespace std;

void test_ini()
{
    ChainingHashTable<int> ht1;
    ChainingHashTable<int> ht2 {103};
}

void test_insert()
{
    ChainingHashTable<int> hf;
	for(size_t i{0}; i < 20; ++i)
	{
		assert(hf.insert(i));
	}
}

void test_remove()
{
	ChainingHashTable<int> hf;
	for(size_t i{0}; i < 20; ++i)
	{
		assert(hf.insert(i));
	}
	for(size_t i{0}; i < 20; ++i)
		assert(hf.remove(i));
}

void test_contains()
{
	ChainingHashTable<int> hf{1009} ;
	for(size_t i{0}; i < 100; ++i)
	{
		assert(hf.insert(i));
	}
	for(size_t i{0}; i < 100; ++i)
	{
		assert(hf.contains(i));
	}
	for(size_t i{100}; i < 200; ++i)
		assert(!hf.contains(i));
}

void test_make_empty()
{
	ChainingHashTable<int> hf{1009} ;
	for(size_t i{0}; i < 100; ++i)
		assert(hf.insert(i));
	for(size_t i{0}; i < 100; ++i)
		assert(hf.contains(i));
	hf.make_empty();
	for(size_t i{0}; i < 100; ++i)
		assert(!hf.contains(i));
}

int main()
{
    test_ini();
    test_insert();
	test_remove();
	test_contains();
	test_make_empty();
}
