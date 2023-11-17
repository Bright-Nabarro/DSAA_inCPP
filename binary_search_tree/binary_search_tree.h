#pragma once
#include <stdexcept>
#include <iostream>
#include <utility>

namespace mystl2{

/**
 * @brief binary search tree, use operator< compare
 * 
 * @tparam T 
 */
template <typename Comparable>
class BinarySearchTree
{
public:
	BinarySearchTree(): m_root{nullptr}{};
	//big five
	BinarySearchTree(const BinarySearchTree& rhs);
	BinarySearchTree(BinarySearchTree&& rhs) noexcept;
	~BinarySearchTree();
	BinarySearchTree& operator=(const BinarySearchTree& rhs);
	BinarySearchTree& operator=(BinarySearchTree&& rhs) noexcept;

	//recursive wrapper
	//accessor
	const Comparable& find_min() const 			{return find_min(m_root) -> m_element;}
	const Comparable& find_max() const 			{return find_max(m_root) -> m_element;}
	bool contains(const Comparable& x) const	{return contains(x, m_root);}
	bool is_empty() const 						{return m_root == nullptr;}
	void print_tree
		(std::ostream& os = std::cout) const	{print_tree(m_root, os);}
	size_t depth() const 						{return depth(m_root, 0);}

	//modifier
	void make_empty() 					{make_empty(m_root);}
	void insert(const Comparable& x)	{insert(x, m_root);}
	void insert(Comparable&& x) 		{insert(x, std::move(m_root));}
	void remove(const Comparable& x) 	{remove(x, m_root);}
	void swap(Comparable& rhs) noexcept {std::swap(m_root, rhs.m_root);}

private:
	struct BinaryNode
	{
		Comparable m_element;
		BinaryNode* m_left;
		BinaryNode* m_right;
		
		BinaryNode(const Comparable& element, BinaryNode* left = nullptr,
				BinaryNode* right = nullptr): m_element{element}, 
				m_left{left}, m_right{right}{};
		BinaryNode(Comparable&& element, BinaryNode* left = nullptr,
				BinaryNode* right = nullptr): m_element{std::move(element)}, 
				m_left{left}, m_right{right}{};
	};

	BinaryNode* m_root;
	
	//recursive modifier function
	void insert(const Comparable& x, BinaryNode*& t);
	void insert(Comparable&& x, BinaryNode*& t);
	void remove(const Comparable& x, BinaryNode*& t);
	void make_empty(BinaryNode*& t);
	
	//recursive accessor function
	BinaryNode* find_min(BinaryNode* t) const;
	BinaryNode* find_max(BinaryNode* t) const;
	bool contains(const Comparable& x, BinaryNode* t) const;
	void print_tree(BinaryNode* t, std::ostream& os) const;
	BinaryNode* clone(BinaryNode* t) const;
	size_t depth(BinaryNode* t, size_t the_depth) const;
};

template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree& rhs)
{
	m_root = clone(rhs.m_root);
}

template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(BinarySearchTree&& rhs) noexcept:
	m_root{rhs.m_root}
{
	rhs.m_root = nullptr;
}

template<typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree()
{
	make_empty();
}

template<typename Comparable>
BinarySearchTree<Comparable>& BinarySearchTree<Comparable>::
	operator=(const BinarySearchTree& rhs)
{
	auto temp{rhs};
	swap(temp);
	return *this;
}

template<typename Comparable>
void BinarySearchTree<Comparable>::
	insert(const Comparable& x, BinaryNode*& t)
{
	if(t == nullptr)
		t = new BinaryNode(x);
	else if(x < t->m_element)
		insert(x, t->m_left);
	else if(t->m_element < x)
		insert(x, t->m_right);
	else
		return;
}

template<typename Comparable>
void BinarySearchTree<Comparable>::
	insert(Comparable&& x, BinaryNode*& t)
{
	if(t == nullptr)
		t = new BinaryNode(std::move(x));
	else if(x < t->m_element)
		insert(x, t->m_left);
	else if(t->m_element < x)
		insert(x, t->m_right);
	else
		return;
}

template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable& x, BinaryNode*& t)
{
	if(t == nullptr)
		return;
	else if(x < t->m_element)
		remove(x, t->m_left);
	else if(t->m_element < x)
		remove(x, t->m_left);
	else if(t->left != nullptr && t->right != nullptr)
	{
		t->m_element = find_min(t->m_right)->m_element;
		remove(t->m_element, t->m_right);
	}
	else
	{
		BinaryNode* temp = (t->m_left == nullptr)? t->m_right : t->m_left;
		t->m_element = temp->m_element;
		delete temp;
	}
}

template<typename Comparable>
void BinarySearchTree<Comparable>::make_empty(BinaryNode*& t)
{
	if(t == nullptr)
		return;
	make_empty(t->m_left);
	make_empty(t->m_right);
	delete t;
	t = nullptr;
}

template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode* 
BinarySearchTree<Comparable>::find_min(BinaryNode* t) const
{
	if(t -> m_left == nullptr)
		return t;
	return find_min(t -> m_left);
}

template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode* 
BinarySearchTree<Comparable>::find_max(BinaryNode* t) const
{
	if(t -> m_right == nullptr)
		return t;
	return find_min(t -> m_right);
}

template<typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable& x, BinaryNode* t) const
{
	if(t == nullptr)
		return false;
	else if(x < t->m_element)
		return contains(x, t);
	else if(t->m_element < x)
		return contains(x, t);
	else
		return true;
}

template<typename Comparable>
void BinarySearchTree<Comparable>::print_tree(BinaryNode* t, std::ostream& os) const
{
	if(t == nullptr)
		return;
	os << t->m_element << std::endl;
	print_tree(t->m_left, os);
	print_tree(t->m_right, os);
}

template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode*
BinarySearchTree<Comparable>::clone(BinaryNode* t) const
{
	make_empty();
	if(t == nullptr) return nullptr;
	return new BinaryNode{t->m_element, clone(t->m_left), clone(t->m_right)};
}



template<typename Comparable>
size_t BinarySearchTree<Comparable>::depth(BinaryNode* t, size_t the_depth) const
{
	if(t == nullptr)
		return the_depth;

	size_t left_depth = depth(t->m_left, the_depth+1);
	size_t right_depth = depth(t->m_right, the_depth+1);
	return left_depth > right_depth ? left_depth : right_depth;
}












































}	//namespace mystl2
