#pragma once
#include <span>
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
void heap_sort(std::vector<int>& arr)
{
	binary_heap<int, std::less<int>> bh { arr };
	arr.clear();
	while(!bh.empty())
	{
		arr.push_back(bh.top());
		bh.pop();
	}
}
