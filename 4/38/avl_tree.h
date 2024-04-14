#pragma once
#include <cstddef>  //for size_t
#include <cassert>
#include <iostream>
#include <memory>
#include <utility>
#include <format>
#include <algorithm>
#include <vector>

// use < and == compare
template<typename T>
class AvlTree
{
public:
	AvlTree();
	AvlTree(const AvlTree& rhs);
	AvlTree& operator=(const AvlTree& rhs);
	AvlTree(AvlTree&& rhs) noexcept;
	AvlTree& operator=(AvlTree&& rhs) noexcept;
	virtual ~AvlTree() = default;
	void swap(AvlTree& rhs) noexcept;

	size_t size() const noexcept;
	const T& find_min() const;
	const T& find_max() const;
	bool contains (const T& x) const;
	bool is_empty() const;
	//use DOT language
	void print_tree(std::ostream& out) const;

	void make_empty();
	//should add requires T == RT& || t == RT&&
	template<typename RT>
	bool insert(RT&& x);
	bool remove(const T& x);

private:
	struct AvlNode;
	using uptr = std::unique_ptr<AvlNode>;

public:
	std::vector<std::pair<std::pair<int, int>, T>> generate_point()
	{
		std::vector<std::pair<std::pair<int, int>, T>> vec;
		int counter{1};
		vec.reserve(currentSize);
		generate_point(root, vec, counter);
		return vec;
	}
private:
	void generate_point(uptr& node, 
						std::vector<std::pair<std::pair<int, int>, T>>& vec, 
						int& counter)
	{
		if(node == nullptr)
			return;
		generate_point(node->left, vec, counter);
		vec.push_back({{counter++, node->height+1}, node->element});
		generate_point(node->right, vec, counter);
	}
	
private:
	const uptr& find_min(const uptr& ptr) const;
	const uptr& find_max(const uptr& ptr) const;
	const uptr& find_minmax(const uptr& ptr, bool isLeft) const;
	uptr& find_min(uptr& ptr);
	uptr& find_max(uptr& ptr);
	bool contains(const T& x, const uptr& ptr) const;
	void print_tree(std::ostream& out, const uptr& ptr) const;
	void print_nodes(std::ostream& out, 
					 const uptr& ptr, const uptr& next) const;

	uptr clone(const uptr& rhsp);
	void make_empty(uptr& ptr);
	template<typename RT>
	bool insert(RT&& x, uptr& ptr);
	bool remove(const T& x, uptr& ptr);
	
	int height(const uptr& ptr) const;
	void balance(uptr& ptr);
	//left means left at first
	void rotate_left_child(uptr& ptr);
	void rotate_right_child(uptr& ptr);
	void rotate_left_right(uptr& ptr, bool isLeft);
	//left means left subtree to the middle
	void double_left_child(uptr& ptr);
	void double_right_child(uptr& ptr);
private:
	inline const static int sk_allowImbalance{1};
private:
	uptr root;
	size_t currentSize;
};

template<typename T>
struct AvlTree<T>::AvlNode
{
	T element;
	uptr left;
	uptr right;
	int height;

	AvlNode(const T& theElement, uptr&& theLeft = nullptr,
			   uptr&& theRight = nullptr, int h = 0);
	AvlNode(T&& theElement, uptr&& theLeft = nullptr,
			   uptr&& theRight = nullptr, int h = 0);
};


//===============================interface implement====================================//
template<typename T>
void swap(AvlTree<T>& lhs, AvlTree<T>& rhs) noexcept
{
	lhs.swap(rhs);
}

template<typename T>
AvlTree<T>::AvlTree() :
	root {nullptr}, currentSize{0}
{}

//currentSize assignment need optimize
template<typename T>
AvlTree<T>::AvlTree(const AvlTree& rhs) :
	root {nullptr}, currentSize{rhs.currentSize}
{
	root = clone(rhs.root);
}

template<typename T>
AvlTree<T>& AvlTree<T>::operator=(const AvlTree& rhs)
{
	auto copy {rhs};
	swap(copy);
	return *this;
}

template<typename T>
AvlTree<T>::AvlTree(AvlTree&& rhs) noexcept
{
	root = std::exchange(rhs.root, nullptr);
	currentSize = std::exchange(rhs.currentSize, 0);
}

template<typename T>
AvlTree<T>& AvlTree<T>::operator=
					(AvlTree&& rhs) noexcept
{
	this->swap(rhs);
	return *this;
}

template<typename T>
void AvlTree<T>::swap(AvlTree& rhs) noexcept
{
	std::swap(root, rhs.root);
	std::swap(currentSize, rhs.currentSize);
}

template<typename T>
size_t AvlTree<T>::size() const noexcept
{
	return currentSize;
}

template<typename T>
const T& AvlTree<T>::find_min() const
{
	return find_min(root)->element;
}

template<typename T>
const T& AvlTree<T>::find_max() const
{
	return find_max(root)->element;
}

template<typename T>
bool AvlTree<T>::contains(const T& x) const
{
	return contains(x, root);
}

template<typename T>
bool AvlTree<T>::is_empty() const
{
	return root == nullptr;
}

template<typename T>
void AvlTree<T>::print_tree(std::ostream& out) const
{
	out << "digraph G {\n";
	print_tree(out, root);
	out << "}\n";
}

template<typename T>
void AvlTree<T>::make_empty()
{
	make_empty(root);
	assert(currentSize == 0);
}

template<typename T>
template<typename RT>
bool AvlTree<T>::insert(RT&& x)
{
	return insert(std::forward<RT>(x), root);
}

template<typename T>
bool AvlTree<T>::remove(const T& x)
{
	return remove(x, root);
}


//================================privative method=====================================//
template<typename T>
auto AvlTree<T>::find_min(const uptr& ptr) const -> const uptr&
{
	return find_minmax(ptr, true);
}

template<typename T>
auto AvlTree<T>::find_max(const uptr& ptr) const -> const uptr&
{
	return find_minmax(ptr, false);
}

template<typename T>
auto AvlTree<T>::find_minmax(const uptr& ptr, bool isLeft) const 
-> const uptr&
{
	if(ptr == nullptr)
		throw std::runtime_error{"there on elements in search tree"};

	uptr& nextPtr = isLeft ? ptr->left : ptr->right;
	if(nextPtr == nullptr)
		return ptr;
	else
		return find_minmax(nextPtr, isLeft);
}

template<typename T>
auto AvlTree<T>::find_min(uptr& ptr) -> uptr&
{
	return const_cast<uptr&>(std::as_const(*this).find_min(ptr));
}

template<typename T>
auto AvlTree<T>::find_max(uptr& ptr) -> uptr&
{
	return const_cast<uptr&>(std::as_const(*this).find_max(ptr));
}

template<typename T>
bool AvlTree<T>::contains(const T& x, const uptr& ptr) const
{
	if(ptr == nullptr)
		return false;
	else if(ptr->element == x)
		return true;
	else
		return contains(x, ptr->left) || contains(x, ptr->right);
}

template<typename T>
void AvlTree<T>::print_tree(std::ostream& out, const uptr& ptr) const
{
	if(ptr == nullptr)
		return;
	print_nodes(out, ptr, ptr->left);
	print_nodes(out, ptr, ptr->right);
	
	//recursive
	print_tree(out, ptr->left);
	print_tree(out, ptr->right);
}

template<typename T>
void AvlTree<T>::print_nodes(std::ostream& out, 
									  const uptr& ptr, const uptr& next) const
{
	static size_t counter {0};

	if(next != nullptr)
		out << std::format("{} -> {};\n", ptr->element, next->element);
	else
		out << std::format("{} -> {}{};\n", ptr->element, "null", counter++);
}

template<typename T>
auto AvlTree<T>::clone(const uptr& rhsp) -> uptr
{
	if(rhsp == nullptr)
		return nullptr;
	else
		return std::make_unique<AvlNode>
			(rhsp->element, clone(rhsp->left), clone(rhsp->right));
}

template<typename T>
void AvlTree<T>::make_empty(uptr& ptr)
{
	if(ptr == nullptr)
		return;
	make_empty(ptr->left);
	make_empty(ptr->right);
	ptr.reset();
	--currentSize;
}

template<typename T>
template<typename RT>
bool AvlTree<T>::insert(RT&& x, uptr& ptr)
{
	bool result;
	if(ptr == nullptr)
	{
		ptr = std::make_unique<AvlNode>(std::forward<RT>(x), nullptr, nullptr);
		++currentSize;
		result = true;
	}
	else if(x < ptr->element)
		result = insert(std::forward<RT>(x), ptr->left);
	else if(ptr->element < x)
		result = insert(std::forward<RT>(x), ptr->right);
	else
	{
		assert(x == ptr->element);
		result = false;
	}

	balance(ptr);
	return result;
}

template<typename T>
bool AvlTree<T>::remove(const T& x, uptr& ptr)
{
	bool result;
	if(ptr == nullptr)
		result = false;
	else if(x < ptr->element)
	{
		result = remove(x, ptr->left);
	}
	else if(ptr->element < x)
	{
		result = remove(x, ptr->right);
	}
	else if(ptr->left != nullptr && ptr->right != nullptr)
	{
		auto& rptr = find_min(ptr->right);
		ptr->element = rptr->element;
		//only one calling to remove
		remove(ptr->element, rptr);
		--currentSize;
		result = true;
	}
	else
	{
		//smart pointer donot use expilicit release operation
		ptr = (ptr->left != nullptr) ? std::move(ptr->left) : std::move(ptr->right);
		balance(ptr);
		--currentSize;
		result = true;
	}
	balance(ptr);
	return result;
}

template<typename T>
int AvlTree<T>::height(const uptr& ptr) const
{
	return ptr == nullptr ? -1 : ptr->height;
}

template<typename T>
void AvlTree<T>::balance(uptr& ptr)
{
	if(ptr == nullptr)
		return;

	if(height(ptr->left) - height(ptr->right) > sk_allowImbalance)
	{
		//if ptr->left == nullptr, the if condition is impossible pass
		assert(ptr->left != nullptr);
		if(height(ptr->left->left) >= height(ptr->left->right))
			rotate_left_child(ptr);
		else
			double_left_child(ptr);
	}
	else if(height(ptr->right) - height(ptr->left) > sk_allowImbalance)
	{
		assert(ptr->right != nullptr);
		if(height(ptr->right->right) >= height(ptr->right->left))
			rotate_right_child(ptr);
		else
			double_right_child(ptr);
	}

	ptr->height = std::max(height(ptr->left), height(ptr->right)) + 1;
}

template<typename T>
void AvlTree<T>:: rotate_left_child(uptr& k2)
{
	rotate_left_right(k2, true);
}

template<typename T>
void AvlTree<T>::rotate_right_child(uptr& k2)
{
	rotate_left_right(k2, false);
}

template<typename T>
void AvlTree<T>::rotate_left_right(uptr& k2, bool isLeft)
{
	//rotate operations just modifiy k1 and k2's height
	//k1 left child, right child does not change
	auto& k2Fir = isLeft ? k2->left : k2->right;
	auto& k2Sec = isLeft ? k2->right : k2->left;
	uptr k1 = std::move(k2Fir);
	auto& k1Fir = isLeft ? k1->left : k1->right;
	auto& k1Sec = isLeft ? k1->right : k1->left;

	k2Fir = std::move(k1Sec);
	k2->height = std::max(height(k2Fir), height(k2Sec)) + 1;
	k1Sec = std::move(k2);
	k1->height = std::max(height(k1Fir), height(k2)) + 1;
	k2 = std::move(k1);
}

template<typename T>
void AvlTree<T>::double_left_child(uptr& k3)
{
	rotate_right_child(k3->left);
	rotate_left_child(k3);
}

template<typename T>
void AvlTree<T>::double_right_child(uptr& k3)
{
	rotate_left_child(k3->right);
	rotate_right_child(k3);
}


//===============================node's method========================================//
template<typename T>
AvlTree<T>::AvlNode::AvlNode
(const T& theElement, uptr&& theLeft, uptr&& theRight, int h) :
	element{theElement}, left{std::move(theLeft)}, right{std::move(theRight)},
	height{h}
{}

template<typename T>
AvlTree<T>::AvlNode::AvlNode
(T&& theElement, uptr&& theLeft, uptr&& theRight, int h) :
	element{std::move(theElement)}, left{std::move(theLeft)}, right{std::move(theRight)},
	height{h}
{}