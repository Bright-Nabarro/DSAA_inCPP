#pragma once
#include <vector>
#include <type_traits>
#include <utility>
#include <cmath>
#include <format>
#include <stdexcept>
#ifdef DEBUG
#include <ostream>
#include <format>
#endif
#include <algorithm>

template<typename C, typename Ty>
concept Comparator = requires(C cpr, Ty a, Ty b)
{
	{ cpr(a, b) } -> std::convertible_to<bool>;
};

// compare (x, elememt), x is the inserted value
template <typename Ty, Comparator<Ty> Comp = std::less<Ty>>
class binary_heap
{
public:
	//Constructor
	binary_heap() : m_compare{}, m_array(1) { }
	binary_heap(const Comp& compare) : m_compare { compare }, m_array(1) { }

	explicit binary_heap(const std::vector<Ty>& array):
		m_compare{}, m_array(array.size()+1)
	{
		std::ranges::copy(array, m_array.begin()+1);
		build_heap();
	}

	virtual ~binary_heap() = default;

public:
	//Accessor
	[[nodiscard]] constexpr
	bool empty() const noexcept
	{
		return size() == 0;
	}

	[[nodiscard]] constexpr
	size_t size() const noexcept
	{
		return m_array.size() - 1;
	}

	[[nodiscard]] constexpr
	const Ty& top() const noexcept
	{
		return m_array[1];
	}

	[[nodiscard]]
	bool find(const Ty& value) const
	{
		static_assert(sizeof(Ty) != 0, "Warning: The find function is not efficient. Use with caution.");
		return find_itr(value) != m_array.end();
	}

	//Modifier
	template<typename Ty_ref>
	requires std::is_same_v<Ty, std::decay_t<Ty_ref>>
	void push(Ty_ref&& value)
	{
		size_t backIdx { m_array.size() };
		m_array.resize(backIdx + 1);
		m_array[backIdx] = std::forward<Ty_ref>(value);
		
		while(m_compare(value, parent_node(backIdx)))
		{
			std::swap(m_array[backIdx], parent_node(backIdx));
			backIdx = parent(backIdx);
			if (backIdx == 1)
				break;
		}
	}

	template<typename... Arg>
	void emplace(Arg... arg)
	{
		push(Ty { arg... } );
	}

	void pop()
	{
		if (empty())
			throw std::runtime_error { "heap is already empty" };
		m_array[1] = std::move(m_array.back());
		m_array.resize(m_array.size()-1);
		percolate_down(1);
	}

	void erase(const Ty& value)
	{
		static_assert(sizeof(Ty) != 0, "Warning: The erase function is not efficient. Use with caution.");
	
		auto itr = find_itr(value);	
		if (itr == m_array.end())
			throw std::runtime_error { std::format("cannot find {} in heap", value) };
		
		size_t pos { std::distance(m_array.begin(), itr) };
		assert(pos < m_array.size());

		m_array[pos] = std::move(m_array.back());
		m_array.resize(m_array.size()-1);
		percolate_down(pos);
	}

	void clear()
	{
		m_array.clear();
	}
	
#ifdef DEBUG

public:
	void print(std::ostream& os)
	{
		os << "digraph G{\n";
		if (size() == 1)
			os << top() << std::endl;
		else
			print(1, os);
		os << '}' << std::endl;
	}

	void print(size_t idx, std::ostream& os)
	{
				
		if (idx > size()/2)
			return;

		auto[c1, c2] = child(idx);

		if (c1 < m_array.size())
		{
			os << std::format("\t{} -> {}\n", m_array[idx], m_array[c1]);
			print(c1, os);
		}

		if (c2 < m_array.size())
		{
			os << std::format("\t{} -> {}\n", m_array[idx], m_array[c2]);
			print(c2, os);
		}
	}

#endif

private:
	//Method
	[[nodiscard]] constexpr
	size_t parent(size_t node) const noexcept
	{
		return node / 2;
	}
	[[nodiscard]]
	Ty& parent_node(size_t node) noexcept
	{
		return m_array[parent(node)];
	}

	[[nodiscard]] constexpr
	std::pair<size_t, size_t> child(size_t node) const noexcept
	{
		return { node*2, node*2 + 1 };
	}

	[[nodiscard]]
	auto find_itr(const Ty& value) const
	{
		return std::ranges::find(m_array, value);
	}
	
	void percolate_down(size_t idx)
	{
		const size_t limit = ceil(static_cast<double>(m_array.size())/2);
		const size_t backIdx { m_array.size() - 1 };
		auto Ori { std::move(m_array[idx]) };
		while(idx < limit)
		{
			auto[c1, c2] = child(idx);
			size_t pChild;
			if (c2 <= backIdx && m_compare(m_array[c2], m_array[c1]))
				pChild = c2;
			else
				pChild = c1;

			if (m_compare(m_array[pChild], Ori))
				m_array[idx] = std::move(m_array[pChild]);
			else
				break;

			idx = pChild;
		}
		m_array[idx] = std::move(Ori);
	}

	void build_heap()
	{
		size_t parent;
		for(parent = m_array.size() / 2; parent >= 1; parent--)
		{
			percolate_down(parent);
		}
	}

public:
	//Data member
	const Comp m_compare;
	std::vector<Ty> m_array;
};
