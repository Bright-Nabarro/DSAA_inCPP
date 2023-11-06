#pragma once
#include<set>

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
//make multiset to unique set
template<template<typename> class Container, typename T>
void to_uniqueset(Container<T>& C)
{
	std::set<T> uniqueset{C.begin(), C.end()};
	C = Container<T>{uniqueset.begin(), uniqueset.end()};
}

//set union
template<template<typename> class Container, typename T>
Container<T> set_union(const Container<T>& C1, const Container<T>& C2)
{
	//assert C1&C2 are unique set
	Container<T> C_result;
	for(auto ptr1 = C1.begin(); ptr1 != C1.end(); ptr1++)
		for(auto ptr2 = C2.begin(); ptr2 != C2.end(); ptr2++)
			if(*ptr1 == *ptr2)
				C_result.push_back(*ptr1);
	return C_result;
}

//3_5
//set intersection
template<template<typename> class Container, typename T>
Container<T> set_intersect(const Container<T>& C1, const Container<T>& C2)
{
	//assert C1&C2 are unique set
	Container<T> C_result(C1);
	for(const auto& x: C2)
		C_result.push_back(x);
	to_uniqueset(C_result);
	return C_result;
}


}	//namespace my_stl2
