#include <algorithm>
#include <ctime>
#include <iostream>

template <typename T> int func(T a[], size_t N)
{
	std::sort(a, a + N);
	return a[N / 2];
}

int main()
{
	int ai[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::cout << func(ai, sizeof(ai) / sizeof(ai[0])) << std::endl;
	clock_t start, end;
	start = clock();

	end = clock();
}