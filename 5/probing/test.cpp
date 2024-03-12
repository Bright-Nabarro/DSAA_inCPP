#include <cassert>
#include "probing.h"
using namespace std;

void test_ini()
{
    Probing<int> p{};
    Probing<int> t1{101};
    Probing<int> t2{101, [](size_t x){return 13-x%13;}};
}

void test_insert()
{
    Probing<int> t1{};
    t1.insert(1);
    t1.insert(2);
    t1.insert(3);
    assert(t1.contains(1));
    assert(t1.contains(2));
    assert(t1.contains(3));
    assert(!t1.contains(4));

    Probing<int> t2{1011};
    for(size_t i {0}; i < 500; ++i)
    {
        assert(t2.insert(i));
    }
    for(size_t i {0}; i < 500; ++i)
        assert(t2.contains(i));
    for(size_t i{501}; i < 1000; ++i)
        assert(!t2.contains(i));
    for(size_t i{0}; i < 500; ++i)
        assert(!t2.insert(i));
}

void test_make_empty()
{
    Probing<int> t2{1011};
    for(size_t i {0}; i < 500; ++i)
    {
        assert(t2.insert(i));
    }
    for(size_t i {0}; i < 500; ++i)
        assert(t2.contains(i));
    for(size_t i{501}; i < 1000; ++i)
        assert(!t2.contains(i));
    for(size_t i{0}; i < 500; ++i)
        assert(!t2.insert(i));
    t2.make_empty();
    for(size_t i {0}; i < 500; ++i)
        assert(!t2.contains(i));

}

void test_remove()
{
    Probing<int> t1{};
    assert(!t1.contains(1));
    t1.insert(1);
    assert(t1.contains(1));
    assert(t1.remove(1));
    assert(!t1.contains(1));

    Probing<int> t2{1011};
    for(size_t i {0}; i < 500; ++i)
        assert(t2.insert(i));
    for(size_t i {0}; i < 500; ++i)
        assert(t2.contains(i));
    for(size_t i {0}; i < 500; ++i)
        assert(t2.remove(i));
    for(size_t i {0}; i < 500; ++i)
        assert(!t2.contains(i));
   for(size_t i {0}; i < 500; ++i)
        assert(!t2.remove(i));
}

void test_rehash()
{
    Probing<int> t1{101};
    for(size_t i {0}; i < 500; ++i)
        assert(t1.insert(i));

    Probing<int> t2 {10, [](int x){return x+3-x%3;}};
    for(size_t i {0}; i < 500; ++i)
        assert(t2.insert(i));
}

void test_is_empty()
{
    Probing<int> t1;
    assert(t1.is_empty());
    assert(t1.insert(1));
    assert(!t1.is_empty());
    assert(t1.remove(1));
    assert(t1.is_empty());

    Probing<int> t2 {10, [](int x){return x+3-x%3;}};
    assert(t2.is_empty());
    for(size_t i {0}; i < 500; ++i)
    {
        assert(t2.insert(i));
        assert(!t2.is_empty());
    }
    for(size_t i {0}; i < 500; ++i)
    {
        assert(t2.remove(i));
        if(i != 499)
            assert(!t2.is_empty());
    }
    assert(t2.is_empty());
}

int main()
{
    test_ini();
    test_insert();
    test_make_empty();
    test_remove();
    test_rehash();
    test_is_empty();
}
