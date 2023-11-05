#include <iostream>

inline bool is_odd(int N) { return N & 1; }

int pow(int x, int N)
{
	if (N == 0)
		return 1;
	if (is_odd(N))
		return pow(x * x, N / 2) * x;
	else
		return pow(x * x, N / 2);
}

int main(void)
{
	int x = 3;
	int N = 4;
	std::cout << pow(x, N) << std::endl;
}