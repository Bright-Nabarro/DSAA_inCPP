#pragma once

namespace my_stl2
{

//3_3
template<typename Iterator, typename Object>
Iterator find(Iterator start, Iterator end, const Object& x)
{
	//use normal method
	for(auto ptr = start; ptr != end; ptr++)
		if(*ptr == x)
			return ptr;
	return end;
}
//3_4
template<template<typename> class Container, typename T>
Container<T> merge(const Container<T>& C1, const Container<T>& C2)
{
	Container<T> C_result;
	for(auto ptr1 = C1.begin(); ptr1 != C1.end(); ptr1++)
		for(auto ptr2 = C2.begin(); ptr2 != C2.end(); ptr2++)
			if(*ptr1 == *ptr2)
				C_result.push_back(*ptr1);
	return C_result;
}


}	//namespace my_stl2
