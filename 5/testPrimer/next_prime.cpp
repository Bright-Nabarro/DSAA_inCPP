#include <cmath>
#include "next_prime.h"

size_t next_prime(size_t n)
{
    if(n <= 1)
        return 2;
    size_t result {n};
outer_loop:
    while(true)
    {
        for(size_t i{2}; i <= sqrt(result); ++i)
        {
            if(result % i == 0)
            {
                ++result;
                goto outer_loop;
            }
        }
        return result;
    }
}