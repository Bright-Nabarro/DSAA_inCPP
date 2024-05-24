#pragma once
#include <cmath>
#include <cassert>
#include <functional>
#include <uptr_view.hpp>
#include <memory>
#include <vector>
#include <limits>
#define DEBUG
#ifdef DEBUG
#include <ostream>
#include <format>
#endif

template<typename Ty, typename Compare = std::less<Ty>>
class binomial_queue
{
	struct Node;
	using uptr = std::unique_ptr<Node>;
	using uptrV = tiny_utl::uptr_view<Node>;
	using cuptrV = tiny_utl::cuptr_view<Node>;
public:
	//Constructor
	binomial_queue() : m_trees(s_kDefaultVecSize), m_size{0}
	{ }

	binomial_queue(const binomial_queue& rhs)
	{
		clone(rhs.m_trees);
		m_size = rhs.size();
	}

	binomial_queue& operator=(const binomial_queue& rhs)
	{
		if (this == &rhs)
			return *this;
		clone(rhs.m_trees);
		m_size = rhs.size();
		return *this;
	}

	binomial_queue(binomial_queue&& rhs) noexcept = default;

	binomial_queue& operator=(binomial_queue&& rhs) noexcept = default;

	virtual ~binomial_queue() = default;

public:
	//Accessor
	[[nodiscard]] constexpr
	bool empty() const noexcept
	{
		return m_size == 0;
	}

	[[nodiscard]] constexpr
	size_t size() const noexcept
	{
		return m_size;
	}

	[[nodiscard]] constexpr
	const Ty& top() const noexcept
	{
		return m_trees[top_idx()]->value;
	}

	void clear() noexcept
	{
		m_size = 0;
		m_trees.clear();
	}

	//Modifier
	template<typename Ty_ref>
	requires std::is_same_v<Ty, std::decay_t<Ty_ref>>

	void push(Ty_ref&& value)
	{
		binomial_queue newQue{std::forward<Ty>(value)};
		this->merge(newQue);
	}

	void pop()
	{
		const size_t popedIdx { top_idx() };
		uptr oldRoot = std::move(m_trees[popedIdx]);

		binomial_queue newQue;
		uptrV popedChild { oldRoot->child };
		newQue.m_trees.resize(popedIdx+1);
		for(size_t iBias {popedIdx}; iBias >= 1; iBias--)
		{
			uptrV temp = popedChild;
			popedChild = popedChild->subling;
			newQue.m_trees[iBias-1] = std::move(temp.release());
		}
		
		newQue.m_size = (1 << popedIdx)-1;
		// m_size会在merge中+rhs.m_size
		m_size -= newQue.size() + 1;
		this->merge(newQue);
		assert(newQue.empty());
	}

	void merge(binomial_queue& rhs)
	{
		if (this == &rhs)
			return;

		m_size += rhs.m_size;

		if (m_size > capacity())	//扩充2倍容量
		{
			m_trees.resize(std::max(m_size, rhs.m_size) + 1);
		}
		
		enum {
			EMPTY = 0b0, LHS = 0b1, RHS = 0b10, CARRAY = 0b100
		};

		uptr carray;
		const size_t limit = ceil(log2(m_size+1));
		for(int i {0}; i < limit; i++)
		{
			assert(i < m_trees.size());
			int stat { EMPTY };
			if (carray)
				stat |= CARRAY;
			if (m_trees[i])
				stat |= LHS;
			if (i < rhs.m_trees.size() && rhs.m_trees[i])
				stat |= RHS;

			switch (stat)
			{
			case EMPTY:
			case LHS:
				break;
			case CARRAY:
				m_trees[i] = std::move(carray);
				break;
			case RHS:
				m_trees[i] = std::move(rhs.m_trees[i]);
				break;
			case LHS | RHS:
				carray = merge_tree(std::move(m_trees[i]), std::move(rhs.m_trees[i]));
				break;
			case LHS | CARRAY:
				carray = merge_tree(std::move(m_trees[i]), std::move(carray));
				break;
			case RHS | CARRAY:
			case LHS | RHS | CARRAY:	//LHS保持在原位置不动
				carray = merge_tree(std::move(rhs.m_trees[i]), std::move(carray));
				break;
			}
		}

		rhs.m_size = 0;
	}

#ifdef DEBUG
	//使用DOT语言，subling与child的层次关系被破坏
	//只能查看聚集情况

	void print(std::ostream& os) const
	{
		os << "digraph BQ {\n";
		for(cuptrV root : m_trees)
		{
			if (root == nullptr)
				continue;
			if (root->child)
				print_tree(root, os);
			else
			{
				assert(!root->subling);
				assert(root == m_trees[0]);
				os << std::format("\t{}\n", root->value);
			}
		}
		os << "}\n";
	}

		void print_tree(cuptrV vtr, std::ostream& os) const
	{
		if (!vtr || !vtr->child)
			return;
		
		os << std::format("\t{} -> {}\n", vtr->value, vtr->child->value);
		print_tree(vtr->child, os);
		print_subling(vtr, os);
	}
	
	void print_subling(cuptrV vtr, std::ostream& os) const
	{
		if (!vtr || !vtr->subling)
			return;
		os << std::format("\t{} -> {}\n", vtr->value, vtr->subling->value);
		print_tree(vtr->subling, os);
	}
	
#endif

private:
	binomial_queue(const Ty& value) : m_trees(1), m_size{1}
	{
		m_trees[0] = std::make_unique<Node>(value);
	}

	binomial_queue(Ty&& value) : m_trees(1), m_size{1}
	{
		m_trees[0] = std::make_unique<Node>(std::move(value));
	}

	[[nodiscard]] constexpr
	size_t top_idx() const noexcept
	{
		size_t minIdx { std::numeric_limits<size_t>::max() };
		for(size_t i {0}; i < m_trees.size(); i++)
		{
			if (m_trees[i] == nullptr)
				continue;

			if (minIdx == std::numeric_limits<size_t>::max())
				minIdx = i;
			else if (cpr(m_trees[i]->value, m_trees[minIdx]->value))
				minIdx = i;
		}
		assert(minIdx != std::numeric_limits<size_t>::max());
		return minIdx;
	}

	[[nodiscard]] constexpr
	size_t capacity() const noexcept
	{
		return (1 << m_trees.size()) - 1;	//1+2+...+2^n
	}

	[[nodiscard]]
	uptr merge_tree(uptr t1, uptr t2)
	{
		bool cprResult { cpr(t1->value, t2->value) };
		uptrV root { cprResult ? t1 : t2 };
		uptrV newChild { cprResult ? t2 : t1 };
		
		uptr oldChild = std::move(root->child);
		root->child = std::move(newChild.release());
		root->child->subling = std::move(oldChild);
		
		return std::move(root.release());
	}

	void clone(const std::vector<uptr>& rhsTrees)
	{
		m_trees.resize(rhsTrees.size());
		for(size_t i {0}; i < rhsTrees.size(); i++)
		{
			m_trees[i] = clone(rhsTrees[i]);
		}
	}

	uptr clone(cuptrV node)
	{
		if (node == nullptr)
			return nullptr;

		return std::make_unique<Node>(node->value,  clone(node->subling), clone(node->child));
	}


private:
	struct Node
	{
		Ty value;
		uptr subling;
		uptr child;
		Node(const Ty& v, uptr&& s = nullptr, uptr&& c = nullptr):
			value{v}, subling{std::move(s)}, child{std::move(c)}
		{ }
		Node(Ty&& v, uptr&& s = nullptr, uptr&& c = nullptr):
			value{std::move(v)}, subling{std::move(s)}, child{std::move(c)}
		{ }
	};

	inline static constexpr size_t s_kDefaultVecSize { 5 };
	inline static Compare cpr {};

	std::vector<uptr> m_trees;
	size_t m_size;
};

