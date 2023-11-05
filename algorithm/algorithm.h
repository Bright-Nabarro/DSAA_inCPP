#pragma once

namespace my_stl2
{

template<typename Iterator, typename Object>
Iterator find(Iterator start, Iterator end, const Object& x)
{
	//use normal method
	for(auto ptr = start; ptr != end; ptr++)
		if(*ptr == x)
			return ptr;
	return end;
}

}	//namespace my_stl2
