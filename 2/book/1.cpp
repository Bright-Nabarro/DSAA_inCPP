#include <vector>
#include <iostream>
#include <random>
#include <ctime>
#include <cassert>
using namespace std;

int maxSubSum1(const vector<int>& a)
{
	int maxSum = 0;
	for(int i = 0; i < a.size(); ++i)
	{
		for(int j = i; j < a.size(); ++j)
		{
			int thisSum = 0;
			//traverse subsequence
			for(int k = i; k <= j; ++k)
			{
				thisSum += a[k];
			}
			if(maxSum < thisSum)
				maxSum = thisSum;
		}
	}
	return maxSum;
}

int maxSubSum2(const vector<int>& a)
{
	int maxSum = 0;
	for(int i = 0; i < a.size(); ++i)
	{
		int thisSum = 0;
		for(int j = i; j < a.size(); ++j)
		{
			thisSum += a[j];
			if(maxSum < thisSum)
				maxSum = thisSum;
		}
	}
	return maxSum;
}

int max3(int n1, int n2, int n3)
{
	int max1 = n1 > n2? n1 : n2;
	return max1 > n3? max1 : n3;
}

int maxSubRec(const vector<int>& a, int left, int right)
{
	if(left == right)
	{
		if(a[left] > 0)
			return a[left];
		else
			return 0;
	}
	int mid = (left+right)/2;
	int maxLeftSum = maxSubRec(a, left, mid);
	int maxRightSum = maxSubRec(a, mid+1, right);

	int maxRightBorderSum = 0, rightBorderSum = 0;
	for(int i = mid+1; i <= right; i++)
	{
		rightBorderSum += a[i];
		if(maxRightBorderSum < rightBorderSum)
			maxRightBorderSum = rightBorderSum;
	}
	int maxLeftBorderSum = 0, leftBorderSum = 0;
	for(int i = mid; i >= left; i--)
	{
		leftBorderSum += a[i];
		if(maxLeftBorderSum < leftBorderSum)
			maxLeftBorderSum = leftBorderSum;
	}
	return max3(maxRightSum, maxLeftSum,
			maxRightBorderSum + maxLeftBorderSum);
}

int maxSubSum3(const vector<int>& a)
{
	return maxSubRec(a, 0, a.size()-1);
}

int main()
{
	mt19937 gen(time(0));
	uniform_int_distribution dis(-10, 10);

	vector<int> vi(10);
	for(auto& x: vi)
	{
		x = dis(gen);
		//cout << x << " ";
	}

	auto result = maxSubSum2(vi);
	assert(result == maxSubSum3(vi));
}
