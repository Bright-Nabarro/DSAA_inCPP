# 27

```cpp
//fib algorithm in 2.4.2
long fib(int n)
{
    if(n <= 1)
        return 1;
    else
        return fib(n-1) + fib(n-2)
}
```

The stack space likely to run out when N=50.

 Initially, the function recursively calls `fib(n-1)` and `fib(n-2)`, each performing their calculation independently.
 This approach results in a significant amount of redundant computation. With every recursive call, the stack grows to stroe both the value at the current level and the return address. Consequently, the space complexity escaltes to $2^N$. 
 The stack space will be exhausted rapidly.