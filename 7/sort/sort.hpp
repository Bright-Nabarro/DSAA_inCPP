#pragma once
#include <span>

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
	for(int gap { arr.size()/2 }; gap > 0; gap /= 2)
	{
		for(int i{gap-1}; i < arr.size(); i++)
		{
			Ty temp { std::move(arr[i]) };
			int j { i-gap };
			while(j >= 0 && temp < arr[j])
			{
				arr[j] = std::move(temp);
				j -= gap;
			}
			arr[j] = std::move(temp);
		}
	}
}
