#include <iostream>
#include <sstream>
#include <cassert>
#include <random>
#include <vector>
#include <set>
#include <limits>
#include <fstream>
#include <string>
#include "avl_tree.h"
using namespace std;

typedef AvlTree<int, less<int>, false> TreeObj;

void test_ini()
{
	TreeObj t1;
}

void test_findMinMax()
{
	TreeObj t;
	t.insert(1);
	assert(t.find_max() == 1);
	t.insert(2);
	assert(t.find_max() == 2);
	t.insert(3);
	assert(t.find_max() == 3);
	assert(t.find_min() == 1);

	TreeObj t2;
	for(int i = 0; i < 100; ++i)
	{
		t2.insert(i);
		assert(t2.find_max() == i);
		assert(t2.find_min() == 0);
	}

	TreeObj t3;
	for(int i = 100; i > 0; --i)
	{
		t3.insert(i);
		assert(t3.find_min() == i);
		assert(t3.find_max() == 100);
	}
}

void test_insert()
{
	TreeObj t;
	assert(t.insert(1).first);
	assert(!t.insert(1).first);
	assert(t.insert(2).first);
	auto ret = t.insert(3);
	cout << ret.second->element << endl;


	TreeObj t2;
	const int bound2 {50};
	for(int i = 0; i < bound2; ++i)
	{
		auto ret = t2.insert(i);
		assert(ret.first);
		assert(ret.second->element == i);
	}
	for(int i = 0; i < bound2; ++i)
	{
		assert(!t2.insert(i).first);
	}
	//t2.print_tree(cout);

	TreeObj t3;
	const int bound3 {50};
	for(int i = bound3; i > 0; --i)
	{
		auto ret = t3.insert(i);
		assert(ret.first);
		assert(ret.second->element == i);
	}

	TreeObj t4;
	for(int i = 0, j = 50; i < j; i++, j--)
	{
		auto ret1 = t4.insert(i);
		t4.print_tree(cout);
		assert(ret1.first);
		assert(ret1.second->element == i);
		auto ret2 = t4.insert(j);
		t4.print_tree(cout);
		assert(ret2.first);
		assert(ret2.second->element == j);
	}

	TreeObj t5;
	random_device rd{};
	mt19937 gen{rd()};
	uniform_int_distribution<int> dist{0, 1000};
	for(int i = 0; i < 10000; i++)
	{
		int x = dist(gen);
		auto ret = t5.insert(x);
		if(ret.first)
			assert(ret.second->element == x);
	}

	TreeObj t6;
	for(int i = 100; i > 0; i--)
	{
		auto ret = t6.insert(i);
		assert(ret.first);
		assert(ret.second->element == i);
	}

	TreeObj t7;
	for(int i=100,j=0; i > j; i--, j++)
	{
		auto ret1 = t7.insert(i);
		assert(ret1.first);
		assert(ret1.second->element == i);
		auto ret2 = t7.insert(j);
		assert(ret2.first);
		assert(ret2.second->element == j);
	}
}

void test_remove()
{
	TreeObj t1;
	assert(t1.insert(1).first);
	assert(t1.erase(1));
	assert(!t1.erase(1));

	TreeObj t2;
	for(int i {0}; i < 500; ++i)
	{
		t2.insert(i);
	}
	for(int i {0}; i < 500; ++i)
	{
		assert(t2.erase(i));
	}
	for(int i {0}; i < 500; ++i)
	{
		assert(!t2.erase(i));
	}

	
}

void test_contains()
{
	TreeObj t1;
	t1.insert(1);
	assert(t1.contains(1));

	for(int i {0}; i < 500; ++i)
	{
		t1.insert(i);
		assert(t1.contains(i));
	}
	for(int i{0}; i < 500; ++i)
	{
		assert(t1.contains(i));
		t1.erase(i);
		assert(!t1.contains(i));
	}

	TreeObj t2;
	for(int i {0}, j{100}; i <= j; i++, j--)
	{
		t2.insert(i);
		t2.insert(j);
	}
	for(int i {0}; i < 100; i++)
	{
		assert(t2.contains(i));
	}
	for(int i {0}; i < 100; i++)
	{
		t2.erase(i);
	}
	for(int i{0}; i < 100; i++)
	{
		assert(!t2.contains(i));
	}

	TreeObj t3;
//	static random_device rd;
//	static mt19937 gen;
//	gen.seed(rd());
//	static uniform_int_distribution dist{0, 1000};
	vector<int> v;
	ifstream infile {"test.txt"};
	set<int> s;
	cout << t3.size() << endl;
	string temp;
	while(getline(infile, temp, ','))
	{
		v.push_back(stoi(temp));
	}
	for(auto x: v)
	{
		t3.insert(x);
		s.insert(x);
	}
	for(auto x: v)
	{
		assert(t3.contains(x));
	}
	t3.print_tree(cout);

	cout << "===========================" << endl;
	cout << t3.size() << endl;
	cout << s.size() << endl;
	int count{0};
	cout << "===========================" << endl;
	t3.print_tree(cout);
	cout.flush();
	for(auto x: v)
	{
		count++;
		//size_t size = t3.size();
		t3.erase(x);
		t3.print_tree(cout);
		cout << "==================================" << endl;
		cout << "==================================" << endl;
		cout << "==================================" << endl;
	}
	for(auto x: v)
	{
		if(t3.contains(x))
		{
			//cout << i << endl;
		}
	}
	cout << t3.size() << endl;
	t3.print_tree(cout);
}

//void test_print()
//{
//	TreeObj t1;
//	static random_device rd;
//	static mt19937 gen;
//	gen.seed(rd());
//	static uniform_int_distribution dist{0, 100};
//	for(int i{0}; i < 40; ++i)
//	{
//		t1.insert(dist(gen));
//	}
//	t1.print_tree(cout);
//}
//
void test_other()
{
	TreeObj t3;
	static random_device rd;
	static mt19937 gen;
	gen.seed(rd());
	static uniform_int_distribution<int> dist{0, 1000000};
	set<int> v;
	int min = numeric_limits<int>::max(),
		   max = numeric_limits<int>::min();
	for(int i {0}; i < 500; ++i)
	{
		int x = dist(gen);
		v.insert(x);
		if(x < min)
			min = x;
		if(max < x)
			max = x;
		t3.insert(x);
	}
	assert(t3.size() == v.size());
	assert(t3.find_min() == min);
	assert(t3.find_max() == max);
	for(auto x: v)
	{
		assert(t3.contains(x));
	}
	//t3.print_tree(cout);
	for(auto x: v)
	{
		t3.erase(x);
	}
	assert(t3.size() == 0);
	for(auto x: v)
	{
		assert(!t3.contains(x));
	}
}

void test_copy()
{
	TreeObj t1;
	static random_device rd;
	static mt19937 gen;
	gen.seed(rd());
	static uniform_int_distribution dist{0, 1000000};
	vector<int> v;
	for(int i {0}; i < 500; ++i)
	{
		v.push_back(dist(gen));
		t1.insert(v.back());
	}
	
	auto t2 {t1};
	decltype(t1) t3;
	t3.insert(114514);
	t3 = t1;
	for(auto x: v)
	{
		assert(t2.contains(x));
		assert(t3.contains(x));
	}
	assert(!t3.contains(114514));

	TreeObj t4;
	for(int i = 0; i < 500; ++i)
	{
		t4.insert(i);
	}
	TreeObj t5 {t4};
	TreeObj t6;
	t6 = t4;
	assert(t4 == t5);
	assert(t4 == t6);
	assert(t5 == t6);
}

void test_equal()
{
	TreeObj t1, t2;
	assert(t1 == t2);
	t1.insert(1);
	t2.insert(1);
	assert(t1 == t2);
	t1.insert(2);
	assert(t1 != t2);
	t1.erase(2);
	assert(t1 == t2);

	TreeObj t3, t4;
	for(int i = 0; i < 500; i++)
	{
		t3.insert(i);
		t4.insert(i);
	}
	assert(t3 == t4);
	for(int i = 0; i < 100; i++)
	{
		t3.erase(i);
		t4.erase(i);
	}
	assert(t3 == t4);
}

void test_move()
{
	TreeObj t1;
	static random_device rd;
	static mt19937 gen;
	gen.seed(rd());
	static uniform_int_distribution dist{0, 1000000};
	vector<int> v;
	for(int i {0}; i < 500; ++i)
	{
		v.push_back(dist(gen));
		t1.insert(v.back());
	}
	
	auto t2 {std::move(t1)};
	decltype(t1) t3;
	for(auto x: v)
	{
		assert(t2.contains(x));
	}
	t3 = std::move(t2);
	for(auto x: v)
	{
		assert(t3.contains(x));
	}
}

void test_empty()
{
	TreeObj t1;
	static random_device rd;
	static mt19937 gen;
	gen.seed(rd());
	static uniform_int_distribution dist{0, 1000000};
	vector<int> v;
	for(int i {0}; i < 500; ++i)
	{
		v.push_back(dist(gen));
		t1.insert(v.back());
	}
	assert(!t1.empty());
	t1.clear();
	assert(t1.empty());

	TreeObj t2;
	for(auto x: v)
	{
		t2.insert(x);
	}
	assert(!t2.empty());
	for(auto x: v)
	{
		t2.erase(x);
	}
	assert(t2.empty());
}


int main()
{
	test_ini();
	test_findMinMax();
	test_insert();
	test_remove();
	test_contains();
//	test_other();
	test_copy();
	test_equal();
	test_move();
	test_empty();
	cout << "o((>ω< ))o" << endl;
}