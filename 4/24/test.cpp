#include <iostream>
#include <sstream>
#include <cassert>
#include <random>
#include <vector>
#include <set>
#include <limits>
#include "avl_tree.h"
using namespace std;

void test_ini()
{
    AvlTree<int> b;
}

void test_insert()
{
    AvlTree<int> t;
    assert(t.insert(1));
    assert(!t.insert(1));
    assert(t.insert(2));

    AvlTree<int> t2;
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
    AvlTree<int> t1;
    assert(t1.insert(1));
    assert(t1.remove(1));
    assert(!t1.remove(1));

    AvlTree<int> t2;
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
    AvlTree<int> t1;
    t1.insert(1);
    assert(t1.contains(1));

    for(int i {0}; i < 500; ++i)
    {
        t1.insert(i);
        assert(t1.contains(i));
    }

    AvlTree<int> t3;
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
    AvlTree<int> t1;
    static random_device rd;
    static mt19937 gen;
    gen.seed(rd());
    static uniform_int_distribution dist{0, 100};
    for(int i{0}; i < 40; ++i)
    {
        t1.insert(dist(gen));
    }
    t1.print_tree(cout);
}

void test_other()
{
    AvlTree<int> t3;
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
        t3.remove(x);
    }
    assert(t3.size() == 0);
    for(auto x: v)
    {
        assert(!t3.contains(x));
    }
}

void test_copy()
{
    AvlTree<int> t1;
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
}

void test_move()
{
    AvlTree<int> t1;
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
    AvlTree<int> t1;
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
    assert(!t1.is_empty());
    t1.make_empty();
    assert(t1.is_empty());

    AvlTree<int> t2;
    for(auto x: v)
    {
        t2.insert(x);
    }
    assert(!t2.is_empty());
    for(auto x: v)
    {
        t2.remove(x);
    }
    assert(t2.is_empty());
}

void avl_basic_test()
{
    AvlTree<int> t1;
    for(int i = 0; i < 10; ++i)
        t1.insert(i);
    //t1.print_tree(cout);
}

void avl_print_test()
{
    AvlTree<int> t1;
    for(int i = 0; i < 500; ++i)
        t1.insert(i);
    t1.print_tree(cout);
}

int main()
{
    test_ini();
    test_insert();
    test_remove();
    test_contains();
    //test_print();
    test_other();
    test_copy();
    test_move();
    test_empty();
    avl_basic_test();
    avl_print_test();
    cout << "o((>ω< ))o" << endl;
}