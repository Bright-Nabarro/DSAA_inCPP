#include "deque.h"
#include <iostream>
using namespace std;
void func1()
{
    Deque<int> b;
    b.push(1);
    assert(b.front() == 1);
    assert(b.size() == 1);
    b.push(2);
    assert(b.front() == 2);
    assert(b.size() == 2);
    b.push(3);
    assert(b.front() == 3);
    assert(b.size() == 3);
    b.push(4);
    assert(b.front() == 4);
    assert(b.size() == 4);
    b.push(5);
    assert(b.front() == 5);
    assert(b.size() == 5);
    b.push(6);
    assert(b.front() == 6);
    assert(b.size() == 6);
    b.push(7);
    assert(b.front() == 7);
    assert(b.size() == 7);
    b.push(8);
    assert(b.front() == 8);
    assert(b.size() == 8);
    b.push(9);
    assert(b.front() == 9);
    assert(b.size() == 9);
    b.push(10);
    assert(b.front() == 10);
    assert(b.size() == 10);
    b.push(11);
    assert(b.front() == 11);
    assert(b.size() == 11);
    b.push(12);
    assert(b.front() == 12);
    assert(b.size() == 12);
    b.push(13);
    assert(b.front() == 13);
    assert(b.size() == 13);
    b.push(14);
    assert(b.front() == 14);
    assert(b.size() == 14);
    b.push(15);
    assert(b.front() == 15);
    assert(b.size() == 15);
    b.push(16);
    assert(b.front() == 16);
    assert(b.size() == 16);
    b.push(17);
    assert(b.front() == 17);
    assert(b.size() == 17);
    b.push(18);
    assert(b.front() == 18);
    assert(b.size() == 18);
    b.push(19);
    assert(b.front() == 19);
    assert(b.size() == 19);
    b.push(20);
    assert(b.front() == 20);
    assert(b.size() == 20);
    b.push(21);
    assert(b.front() == 21);
    assert(b.size() == 21);
    b.push(22);
    assert(b.front() == 22);
    assert(b.size() == 22);
    b.push(23);
    assert(b.front() == 23);
    assert(b.size() == 23);
}

void func2()
{
    Deque<int> b;
    b.inject(1);
    assert(b.back() == 1);
    assert(b.size() == 1);
    b.inject(2);
    assert(b.back() == 2);
    assert(b.size() == 2);
    b.inject(3);
    assert(b.back() == 3);
    assert(b.size() == 3);
    b.inject(4);
    assert(b.back() == 4);
    assert(b.size() == 4);
    b.inject(5);
    assert(b.back() == 5);
    assert(b.size() == 5);
    b.inject(6);
    assert(b.back() == 6);
    assert(b.size() == 6);
    b.inject(7);
    assert(b.back() == 7);
    assert(b.size() == 7);
    b.inject(8);
    assert(b.back() == 8);
    assert(b.size() == 8);
    b.inject(9);
    assert(b.back() == 9);
    assert(b.size() == 9);
    b.inject(10);
    assert(b.back() == 10);
    assert(b.size() == 10);
    b.inject(11);
    assert(b.back() == 11);
    assert(b.size() == 11);
    b.inject(12);
    assert(b.back() == 12);
    assert(b.size() == 12);
    b.inject(13);
    assert(b.back() == 13);
    assert(b.size() == 13);
    b.inject(14);
    assert(b.back() == 14);
    assert(b.size() == 14);
    b.inject(15);
    assert(b.back() == 15);
    assert(b.size() == 15);
    b.inject(16);
    assert(b.back() == 16);
    assert(b.size() == 16);
    b.inject(17);
    assert(b.back() == 17);
    assert(b.size() == 17);
    b.inject(18);
    assert(b.back() == 18);
    assert(b.size() == 18);
    b.inject(19);
    assert(b.back() == 19);
    assert(b.size() == 19);
    b.inject(20);
    assert(b.back() == 20);
    assert(b.size() == 20);
    b.inject(21);
    assert(b.back() == 21);
    assert(b.size() == 21);
    b.inject(22);
    assert(b.back() == 22);
    assert(b.size() == 22);
}

void func3()
{
    Deque<int> b;
    b.push(1);
    b.pop();
    b.push(2);
    b.push(3);
    b.push(4);
    b.push(5);
    b.push(6);
    b.push(7);
    b.push(8);
    b.push(9);
    b.push(10);
    b.push(11);
    b.push(12);
    b.push(13);
    b.push(14);
    b.push(15);
    b.push(16);
    b.pop();
    b.push(17);
    b.push(18);
    b.push(19);
    b.push(20);
    b.push(21);
    b.push(22);
    assert(b.size() == 20);
}

void func4()
{
    Deque<int> b;
    b.inject(1);   
    b.eject();
    assert(b.size() == 0);
}

int main()
{
    func1();
    func2();
    func3();
    func4();
}