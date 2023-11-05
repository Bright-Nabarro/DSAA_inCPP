#include <iostream>
#include <vector>
using std::vector;

int max3(int x, int y, int z)
{
	int m1 = x > y ? x : y;
	return m1 > z ? m1 : z;
}

int maxSumRec(const vector<int> &a, int left, int right)
{
	if (left == right)
	{
		if (a[left] > 0)
			return a[left];
		else
			return 0; //此返回的0只用作max3的调用, 作为源数列全为负数的预防
	}

	int center = (left + right) / 2;
	int maxLeftSub = maxSumRec(a, left, center);
	int maxRightSub = maxSumRec(a, center + 1, right);

	//求中间到左右边界的最大子序列和
	//从中间向左边
	int maxM2L = 0, M2L = 0;
	for (int i = center; i >= left; i--)
	{
		M2L += a[i];
		if (maxM2L < M2L)
			maxM2L = M2L;
	}
	int maxM2R = 0, M2R = 0;
	for (int i = center + 1; i <= right; i++)
	{
		M2R += a[i];
		if (maxM2R < M2R)
			maxM2R = M2R;
	}
	int maxMiddleSub = maxM2L + maxM2R;

	return max3(maxLeftSub, maxRightSub, maxMiddleSub);
}

int maxSumRec2(const vector<int> &a, int left, int right)
{
	if (left == right)
	{ // Base case
		if (a[left] > 0)
			return a[left];
		else
			return 0;
	}

	int center = (left + right) / 2;
	int maxLeftSum = maxSumRec(a, left, center);
	int maxRightSum = maxSumRec(a, center + 1, right);

	int maxLeftBorderSum = 0, leftBorderSum = 0;
	for (int i = center; i >= left; --i)
	{
		leftBorderSum += a[i];
		if (leftBorderSum > maxLeftBorderSum)
		{
			maxLeftBorderSum = leftBorderSum;
		}
	}

	int maxRightBorderSum = 0, rightBorderSum = 0;
	for (int j = center + 1; j <= right; ++j)
	{
		rightBorderSum += a[j];
		if (rightBorderSum > maxRightBorderSum)
		{
			maxRightBorderSum = rightBorderSum;
		}
	}

	return max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}

int maxSubSum3(const vector<int> &a) { return maxSumRec(a, 0, a.size() - 1); }

int maxSubSum4(const vector<int> &a) { return maxSumRec2(a, 0, a.size() - 1); }
int main()
{
	vector<int> test{4, -3, 5, -2, -1, 2, 6, -2};
	std::cout << maxSubSum3(test) << std::endl;
	std::cout << maxSubSum4(test) << std::endl;
}