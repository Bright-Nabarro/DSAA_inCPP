#include <iostream>
#include <vector>
using std::vector;
template <typename compareable>
int binary_search(const vector<compareable> &a, const compareable &x)
{
	int low = 0, high = a.size() - 1;
	while (low <= high)
	{
		int mid = (low + high) / 2;
		if (a[mid] < x)
			low = mid + 1;
		else if (a[mid] > x)
			high = mid - 1;
		else
			return mid;
	}
	return -1;
}

int main()
{
	vector<int> vi{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::cout << binary_search(vi, 8) << std::endl;
}