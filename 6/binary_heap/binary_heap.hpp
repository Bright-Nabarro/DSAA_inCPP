#pragma once
#include <cstddef>		//for size_t
#include <vector>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <algorithm>

template<typename Ty, typename Compare = std::less<Ty>>
class BinaryHeap
{
public:
	explicit BinaryHeap(size_t capacity = 100);
	explicit BinaryHeap(const std::vector<Ty> items);
	
	bool is_empty() const noexcept;
	template<typename Ty_ref>
	void insert(Ty_ref&& value);
	void delete_min();
	const Ty& min() const;

	void print_heap(std::ostream& os) const;		//for debug
	size_t size() const noexcept;

private:
	void build_heap();
	template<typename Ty_ref>
	void percolate_up(size_t hole, Ty_ref&& x);
	void percolate_down(size_t hole);

	void print_node(std::ostream& os, size_t n) const;
private:
	inline static Compare m_compare {};
	std::vector<Ty> m_array;	//index begin with 1!
};


template<typename Ty, typename Compare>
BinaryHeap<Ty, Compare>::BinaryHeap(size_t capacity) :
	m_array(1)
{
	m_array.reserve(capacity);
}

template<typename Ty, typename Compare>
BinaryHeap<Ty, Compare>::BinaryHeap(const std::vector<Ty> items) :
	m_array(items.size()+1)
{
	std::move(items.begin(), items.end(), m_array.begin()+1);
	build_heap();
}

template<typename Ty, typename Compare>
bool BinaryHeap<Ty, Compare>::is_empty() const noexcept
{
	return size() == 0;
}

template<typename Ty, typename Compare>
template<typename Ty_ref>
void BinaryHeap<Ty, Compare>::insert(Ty_ref&& value)
{
	m_array.resize(size()+2);
	percolate_up(size(), value);
}

template<typename Ty, typename Compare>
void BinaryHeap<Ty, Compare>::delete_min()
{
	if(is_empty())
		throw std::underflow_error {"cannot deleteM an empty heap!"};

	m_array[1] = std::move(m_array[size()]);
	m_array.pop_back();
	percolate_down(1);
}

template<typename Ty, typename Compare>
const Ty& BinaryHeap<Ty, Compare>::min() const
{
	if(is_empty())
		throw std::out_of_range {"require items in empty heap"};

	return m_array[1];
}


template<typename Ty, typename Compare>
size_t BinaryHeap<Ty, Compare>::size() const noexcept
{
	return m_array.size()-1;
}

template<typename Ty, typename Compare>
void BinaryHeap<Ty, Compare>::print_heap(std::ostream& os) const
{
	size_t node = 1;
	os << "digraph G {\n";
	print_node(os, node);
	os << "}\n";
}

template<typename Ty, typename Compare>
void BinaryHeap<Ty, Compare>::build_heap()
{
	for(size_t i = size()/2; i > 0; i--)
	{
		percolate_down(i);
	}
}

template<typename Ty, typename Compare>
template<typename Ty_ref>
void BinaryHeap<Ty, Compare>::percolate_up(size_t hole, Ty_ref&& x)
{
	while(hole != 1)
	{
		size_t parent = hole/2;
		if(x < m_array[parent])
		{
			m_array[hole] = std::move(m_array[parent]);
			hole = hole/2;
		}
		else
			break;
	}
	m_array[hole] = std::forward<Ty_ref>(x);
}

template<typename Ty, typename Compare>
void BinaryHeap<Ty, Compare>::percolate_down(size_t hole)
{
	size_t bound = size()/2;
	Ty tmp = std::move(m_array[hole]);
	while(hole <= bound)
	{
		size_t child = hole*2;
		if(child != size() && m_compare(m_array[child+1], m_array[child]))
			++child;
		if(m_compare(m_array[child], tmp))
		{
			m_array[hole] = std::move(m_array[child]);
		}
		else	//right
			break;

		hole = child;
	}
	m_array[hole] = std::move(tmp);
}

template<typename Ty, typename Compare>
void BinaryHeap<Ty, Compare>::print_node(std::ostream& os, size_t n) const
{
	size_t left = 2*n, right = 2*n + 1;
	if(left <= size())
	{
		os << m_array[n] << " -> " << m_array[left] << "\n";
		print_node(os, left);
	}
	if(right <= size())
	{
		os << m_array[n] << " -> " << m_array[right] << "\n";
		print_node(os, right);
	}
}
