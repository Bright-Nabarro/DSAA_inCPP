#pragma once
#include <vector>
#include <type_traits>
#include <utility>
#include <ostream>
#include <format>
#include <algorithm>

#define DEBUG

template<typename C, typename Ty>
concept Comparator = requires(C cpr, Ty a, Ty b)
{
	{ cpr(a, b) } -> std::convertible_to<bool>;
};

// compare (x, elememt), x is the inserted value
template <typename Ty, Comparator<Ty> Comp>
class binary_heap
{
public:
	//Constructor
	binary_heap() : m_array(1) { }

	explicit binary_heap(const std::vector<Ty>& array):
		m_array(array.size()+1)
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

	//Modifier
	template<typename Ty_ref>
	requires std::is_same_v<Ty, std::decay_t<Ty_ref>>
	void push(Ty_ref&& value)
	{
		size_t backIdx { m_array.size() };
		m_array.resize(backIdx + 1);
		m_array[backIdx] = std::forward<Ty>(value);
		
		while(s_kCompare(value, parent_node(backIdx)))
		{
			std::swap(m_array[backIdx], parent_node(backIdx));
			backIdx = parent(backIdx);
			if (backIdx == 1)
				break;
		}
	}

	void pop()
	{
		percolate_down(1);
		m_array.resize(m_array.size()-1);
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

	void percolate_down(size_t idx)
	{
		const size_t limit { m_array.size()/2 };
		const size_t backIdx { m_array.size() - 1 };
		auto Ori { m_array[idx] };
		while(idx < limit)
		{
			auto[c1, c2] = child(idx);
			size_t sc = s_kCompare(m_array[c1], m_array[c2]) ? c1 : c2;
			if (s_kCompare(m_array[backIdx], m_array[sc]))
				break;
			m_array[idx] = std::move(m_array[sc]);
			idx = sc;
		}
		m_array[idx] = std::move(m_array[backIdx]);
		m_array[m_array.size()-1] = std::move(Ori);
	}

	void build_heap()
	{
		size_t parent;
		for(parent = m_array.size() / 2; parent >= 1; parent--)
		{
			percolate_down(parent);
		}
	}

#ifdef DEBUG
public:
#else
private:
#endif
	//Data member
	inline const static Comp s_kCompare{};
	std::vector<Ty> m_array;
};
