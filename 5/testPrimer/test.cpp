#include <iostream>
#include "next_prime.h"
using namespace std;

int main()
{
    size_t n;
    while(cin >> n)
    {
        cout << next_prime(n) << endl;;
    }
}