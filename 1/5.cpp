#include <bitset>
#include <iostream>

int num_of_1(int N)
{
	if (N == 1)
		return 1;
	else if (N == 0)
		return 0;
	if (N & 1) // N为奇数
		return num_of_1(N >> 1) + 1;
	else
		return num_of_1(N >> 1);
}
int main(void)
{
	int N = 0x7F;
	std::cout << num_of_1(N) << std::endl;
}