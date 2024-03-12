#include <cassert>
#include "binary_search_tree.h"

void test_ini()
{
    BinarySearchTree<int> b;
}

void test_insert()
{
    BinarySearchTree<int> t;
    t.insert(1);
}

int main()
{
    test_ini();
    test_insert();
}