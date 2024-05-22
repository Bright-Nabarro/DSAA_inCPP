#pragma once
#include <memory>
#include <type_traits>
#include <uptr_view.hpp>
#include <ostream>
#include <format>

#define DEBUG

template<typename C, typename Ty>
concept Cpr = requires(C c, Ty t1, Ty t2) {
	{ c(t1, t2) } -> std::convertible_to<bool>;
};

template<typename Ty, Cpr<Ty> cpr>
class leftist_heap
{
private:
	struct Node;
	using uptr = std::unique_ptr<Node>;
	using uptrV = tiny_utl::uptr_view<Node>;
	using cuptrV = tiny_utl::cuptr_view<Node>;
	struct Node
	{
		Ty m_value;
		uptr left;
		uptr right;
		int npl;
		Node(const Ty& value, uptr&& l = nullptr,
			 uptr&& r = nullptr, int n = 0):
			m_value {value}, left {std::move(l)},
			right {std::move(r)}, npl {n} 
		{ }
		Node(Ty&& value, uptr&& l = nullptr,
			 uptr&& r = nullptr, int n = 0):
			m_value {std::move(value)}, left {std::move(l)},
			right {std::move(r)}, npl {n} 
		{ }
	};

public:
	//constructor
	leftist_heap(): root{nullptr} { }
	leftist_heap(const leftist_heap& rhs)
	{
	}
	leftist_heap& operator= (const leftist_heap& rhs);
	leftist_heap(leftist_heap&& rhs) = default;
	leftist_heap& operator= (leftist_heap&& rhs) = default;
	virtual ~leftist_heap() = default;
	//leftist_heap& operator=(
public:
	//accessor
	[[nodiscard]] constexpr
	bool empty() const noexcept
	{
		return root == nullptr;
	}

	[[nodiscard]] constexpr
	const Ty& top() const noexcept
	{
		return root->m_value;
	}

	//modifier
	template<typename Ty_ref> requires std::is_same_v<Ty, std::decay_t<Ty_ref>>
	void push(Ty_ref&& value)
	{
		root = merge(std::move(root), std::make_unique<Node>(std::forward<Ty>(value)));
	}
	
	void pop()
	{
		root = merge(std::move(root->left), std::move(root->right));
	}

	void merge(leftist_heap& rhs)
	{
		root = merge(std::move(root), std::move(rhs.root));
	}

	void clear()
	{
		root = nullptr;
	}

#ifdef DEBUG
	void print(std::ostream& os) const
	{
		if (root == nullptr)
			return;
		
		static size_t counter {0};
		os << "digraph V {\n";
		if (root->left == nullptr && root->right == nullptr)
			os << std::format("{}\n", root->m_value);
		else
			print(root, os, counter);
		os << "}\n";
	}

	void print(cuptrV node, std::ostream& os, size_t& counter) const
	{
		if (node == nullptr)
			return;
		if (node->left != nullptr)
		{
			os << std::format("n_{} -> n_{}\n", node->m_value, node->left->m_value);
			print(node->left, os, counter);
		}
		else
			os << std::format("n_{} -> NULL{}\n", node->m_value, counter++);

		if (node->right != nullptr)
		{
			os << std::format("n_{} -> n_{}\n", node->m_value, node->right->m_value);
			print(node->right, os, counter);
		}
		else
			os << std::format("n_{} -> NULL{}\n", node->m_value, counter++);

	}
	
	void print_npl(std::ostream& os) const
	{
		if (root == nullptr)
			return;

		static size_t counter {0};
		os << "digraph N {\n";
		print(root, os, counter);
		print_npl(root, os, counter);
		os << "}\n";
	}
	
	void print_npl(cuptrV node, std::ostream& os, size_t& counter) const
	{
		if (node == nullptr)
			return;
		os << std::format("n_{} [label={}]\n", node->m_value, node->npl);
		print_npl(node->left, os, counter);
		print_npl(node->right, os, counter);
	}

#endif

private:
	uptr merge(uptr&& h1, uptr&& h2)
	{
		if (h1 == nullptr)
			return h2;
		if (h2 == nullptr)
			return h1;

		if (compare(h1->m_value, h2->m_value))
			return merge_right_tree(std::move(h1), std::move(h2));
		else
			return merge_right_tree(std::move(h2), std::move(h1));
	}

	uptr merge_right_tree(uptr&& root, uptr&& child)
	{
		if (root->left == nullptr)
			root->left = std::move(child);

		else
		{
			root->right = merge(std::move(root->right), std::move(child));
			if (root->left->npl < root->right->npl)
				std::swap(root->left, root->right);

			root->npl = root->right->npl + 1;
		}
		
		return root;
	}

	uptr clone(cuptrV vtr) const
	{
		if (vtr == nullptr)
			return nullptr;
		uptr newNode = std::make_unique(vtr->m_value, clone(vtr->left),
						 				clone(vtr->right), vtr->npl);
		return newNode;
	}

private:
	inline static cpr compare{};
	uptr root;
};

