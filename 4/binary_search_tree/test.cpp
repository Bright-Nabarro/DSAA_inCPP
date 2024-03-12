#include <iostream>
#include <sstream>
#include <cassert>
#include <random>
#include <vector>
#include <set>
#include <limits>
#include "binary_search_tree.h"
using namespace std;

void test_ini()
{
    BinarySearchTree<int> b;
}

void test_insert()
{
    BinarySearchTree<int> t;
    assert(t.insert(1));
    assert(!t.insert(1));
    assert(t.insert(2));

    BinarySearchTree<int> t2;
    for(int i = 0; i < 500; ++i)
    {
        assert(t2.insert(i));
    }
    for(int i = 0; i < 500; ++i)
    {
        assert(!t2.insert(i));
    }
}

void test_remove()
{
    BinarySearchTree<int> t1;
    assert(t1.insert(1));
    assert(t1.remove(1));
    assert(!t1.remove(1));

    BinarySearchTree<int> t2;
    for(int i {0}; i < 500; ++i)
    {
        assert(t2.insert(i));
    }
    for(int i {0}; i < 500; ++i)
    {
        assert(t2.remove(i));
    }
    for(int i {0}; i < 500; ++i)
    {
        assert(!t2.remove(i));
    }

    
}

void test_contains()
{
    BinarySearchTree<int> t1;
    t1.insert(1);
    assert(t1.contains(1));

    for(int i {0}; i < 500; ++i)
    {
        t1.insert(i);
        assert(t1.contains(i));
    }

    BinarySearchTree<int> t3;
    static random_device rd;
    static mt19937 gen;
    gen.seed(rd());
    static uniform_int_distribution dist{0, 1000000};
    vector<int> v;
    for(int i {0}; i < 500; ++i)
    {
        v.push_back(dist(gen));
        t3.insert(v.back());
    }
    for(auto x: v)
    {
        assert(t3.contains(x));
    }
    for(auto x: v)
    {
        t3.remove(x);
    }
    for(auto x: v)
    {
        assert(!t3.contains(x));
    }
}

void test_print()
{
    BinarySearchTree<int> t1;
    t1.insert(3);
    t1.insert(5);
    t1.insert(13);
    t1.insert(1);
    t1.insert(8);
    t1.insert(12);
    t1.insert(7);
    t1.insert(11);
    t1.insert(2);
    t1.insert(9);
    t1.insert(10);
    t1.insert(4);
    t1.insert(6);
    t1.remove(8);
    ostringstream ossm;
    t1.print_tree(ossm);
}

void test_other()
{
    BinarySearchTree<int> t3;
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
    t3.print_tree(cout);
    for(auto x: v)
    {
        t3.remove(x);
    }
    assert(t3.size() == 0);
    for(auto x: v)
    {
        assert(!t3.contains(x));
    }
}

int main()
{
    test_ini();
    test_insert();
    test_remove();
    test_contains();
    test_print();
    test_other();
}