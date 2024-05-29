#pragma once
#include <span>
#include <cassert>
#include "binary_heap.hpp"

template<typename Ty>
void insertion_sort(std::span<Ty> arr)
{
	for(int i {1}; i < arr.size(); i++)
	{
		Ty temp = std::move(arr[i]);
		int j = i-1;
		while(j >= 0 && temp < arr[j])
		{
			arr[j+1] = std::move(arr[j]);
			j--;
		}
		arr[j+1] = std::move(temp);
	}
}

template<typename Ty>
void shell_sort(std::span<Ty> arr)
{
	int gap ( arr.size()/2 );
	for(; gap > 0; gap /= 2)
	{
		for(int i{gap}; i < arr.size(); i++)
		{
			Ty temp { std::move(arr[i]) };
			int j { i-gap };
			while(j >= 0 && temp < arr[j])
			{
				arr[j+gap] = std::move(arr[j]);
				j -= gap;
			}
			arr[j+gap] = std::move(temp);
		}
	}
}

template<typename Ty>
void heap_sort(std::vector<Ty>& arr)
{
	binary_heap<Ty, std::less<int>> bh { arr };
	arr.clear();
	while(!bh.empty())
	{
		arr.push_back(bh.top());
		bh.pop();
	}
}

template<typename Ty>
void merge(std::span<Ty> arr, std::vector<Ty>& tmpArr, size_t leftBeg, size_t center, size_t rightEnd)
{
	const size_t leftEnd { center };
	const size_t rightBeg { center+1 };
	const size_t numElements { rightEnd - leftBeg + 1 };

	size_t counter{0};
	size_t leftPos, rightPos;
	for(leftPos = leftBeg, rightPos = rightBeg;
		leftPos <= leftEnd && rightPos <= rightEnd;
	   )
	{
		if (arr[leftPos] < arr[rightPos])
			tmpArr[counter++] = std::move(arr[leftPos++]);
		else
			tmpArr[counter++] = std::move(arr[rightPos++]);
	}
	while(leftPos <= leftEnd)
	{
		assert(rightPos > rightEnd);
		tmpArr[counter++] = std::move(arr[leftPos++]);
	}
	while(rightPos <= rightEnd)
	{
		tmpArr[counter++] = std::move(arr[rightPos++]);
	}

	size_t pos {leftBeg};
	for(size_t i{0}; i < numElements; i++)
	{
		arr[pos++] = std::move(tmpArr[i]);
	}
}

template<typename Ty>
void merge_sort(std::span<Ty> arr, std::vector<Ty>& tmpArr, size_t left, size_t right)
{
	if (left >= right)
		return;

	size_t center = (left + right)/2;
	merge_sort(arr, tmpArr, left, center);
	merge_sort(arr, tmpArr, center+1, right);
	merge(arr, tmpArr, left, center, right);
};

template<typename Ty>
void merge_sort(std::span<Ty> arr)
{
	std::vector<Ty> tmpArr(arr.size());
	merge_sort(arr, tmpArr, 0, arr.size()-1);
}


