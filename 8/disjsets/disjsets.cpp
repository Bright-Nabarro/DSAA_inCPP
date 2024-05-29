#include <print>
#include <algorithm>
#include "disjsets.hpp"
using namespace std;

disjsets::disjsets(int numElements) :
	m_arr(numElements)
{
	ranges::fill(m_arr, -1);
}

int disjsets::find(int x) const
{
	if (m_arr[x])
		return x;
	else
		return find(m_arr[x]);
}

int disjsets::find(int x)
{
	if (m_arr[x] < 0)
		return x;
	else
		return m_arr[x] = find(m_arr[x]);
}

void disjsets::union_sets(int root1, int root2)
{
	if (m_arr[root1] < m_arr[root2]) //root1 is deeper
		m_arr[root2] = root1;	
	else if (m_arr[root2] < m_arr[root1])
		m_arr[root1] = root2;
	else
	{
		--m_arr[root1];
		m_arr[root2] = root1;
	}
}

void disjsets::print() const
{
	std::println("digraph D {{");
	for(size_t i{0}; i < m_arr.size(); i++)
	{
		if (m_arr[i] < 0)
			std::println("\t{}", i);
		else
			std::println("\t{} -> {}", i, m_arr[i]);
	}
	std::println("}}");
}

