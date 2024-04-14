#pragma once
#include <cstddef>  //for size_t
#include <cassert>
#include <iostream>
#include <memory>
#include <utility>
#include <format>

// use < and == compare
template<typename T>
class BinarySearchTree
{
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree& rhs);
	BinarySearchTree& operator=(const BinarySearchTree& rhs);
	BinarySearchTree(BinarySearchTree&& rhs) noexcept;
	BinarySearchTree& operator=(BinarySearchTree&& rhs) noexcept;
	virtual ~BinarySearchTree() = default;
	void swap(BinarySearchTree& rhs) noexcept;

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
	struct BinaryNode;
	using uptr = std::unique_ptr<BinaryNode>;
	
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
	bool remove(const T& x, uptr& ptr, bool needUpdateSize = true);
	
private:
	uptr root;
	size_t currentSize;

public:
	void remove_all_leaves();
private:
	void remove_all_leaves(uptr& ptr);
};

template<typename T>
struct BinarySearchTree<T>::BinaryNode
{
	T element;
	uptr left;
	uptr right;
	BinaryNode(const T& theElement, uptr&& theLeft = nullptr,
			   uptr&& theRight = nullptr);
	BinaryNode(T&& theElement, uptr&& theLeft = nullptr,
			   uptr&& theRight = nullptr);
};


//===============================interface implement====================================//
template<typename T>
void swap(BinarySearchTree<T>& lhs, BinarySearchTree<T>& rhs) noexcept
{
	lhs.swap(rhs);
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree() :
	root {nullptr}, currentSize{0}
{}

//currentSize assignment need optimize
template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& rhs) :
	root {nullptr}, currentSize{rhs.currentSize}
{
	root = clone(rhs.root);
}

template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree& rhs)
{
	auto copy {rhs};
	swap(copy);
	return *this;
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree&& rhs) noexcept
{
	root = std::exchange(rhs.root, nullptr);
	currentSize = std::exchange(rhs.currentSize, 0);
}

template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=
					(BinarySearchTree&& rhs) noexcept
{
	this->swap(rhs);
	return *this;
}

template<typename T>
void BinarySearchTree<T>::swap(BinarySearchTree& rhs) noexcept
{
	std::swap(root, rhs.root);
	std::swap(currentSize, rhs.currentSize);
}

template<typename T>
size_t BinarySearchTree<T>::size() const noexcept
{
	return currentSize;
}

template<typename T>
const T& BinarySearchTree<T>::find_min() const
{
	return find_min(root)->element;
}

template<typename T>
const T& BinarySearchTree<T>::find_max() const
{
	return find_max(root)->element;
}

template<typename T>
bool BinarySearchTree<T>::contains(const T& x) const
{
	return contains(x, root);
}

template<typename T>
bool BinarySearchTree<T>::is_empty() const
{
	return root == nullptr;
}

template<typename T>
void BinarySearchTree<T>::print_tree(std::ostream& out) const
{
	out << "digraph G {\n";
	print_tree(out, root);
	out << "}\n";
}

template<typename T>
void BinarySearchTree<T>::make_empty()
{
	make_empty(root);
	assert(currentSize == 0);
}

template<typename T>
template<typename RT>
bool BinarySearchTree<T>::insert(RT&& x)
{
	return insert(std::forward<RT>(x), root);
}

template<typename T>
bool BinarySearchTree<T>::remove(const T& x)
{
	return remove(x, root);
}


//================================privative method=====================================//
template<typename T>
auto BinarySearchTree<T>::find_min(const uptr& ptr) const -> const uptr&
{
	return find_minmax(ptr, true);
}

template<typename T>
auto BinarySearchTree<T>::find_max(const uptr& ptr) const -> const uptr&
{
	return find_minmax(ptr, false);
}

template<typename T>
auto BinarySearchTree<T>::find_minmax(const uptr& ptr, bool isLeft) const 
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
auto BinarySearchTree<T>::find_min(uptr& ptr) -> uptr&
{
	return const_cast<uptr&>(std::as_const(*this).find_min(ptr));
}

template<typename T>
auto BinarySearchTree<T>::find_max(uptr& ptr) -> uptr&
{
	return const_cast<uptr&>(std::as_const(*this).find_max(ptr));
}

template<typename T>
bool BinarySearchTree<T>::contains(const T& x, const uptr& ptr) const
{
	if(ptr == nullptr)
		return false;
	else if(ptr->element == x)
		return true;
	else
		return contains(x, ptr->left) || contains(x, ptr->right);
}

template<typename T>
void BinarySearchTree<T>::print_tree(std::ostream& out, const uptr& ptr) const
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
void BinarySearchTree<T>::print_nodes(std::ostream& out, 
									  const uptr& ptr, const uptr& next) const
{
	static size_t counter {0};

	if(next != nullptr)
		out << std::format("{} -> {};\n", ptr->element, next->element);
	else
		out << std::format("{} -> {}{};\n", ptr->element, "null", counter++);
}

template<typename T>
auto BinarySearchTree<T>::clone(const uptr& rhsp) -> uptr
{
	if(rhsp == nullptr)
		return nullptr;
	else
		return std::make_unique<BinaryNode>
			(rhsp->element, clone(rhsp->left), clone(rhsp->right));
}

template<typename T>
void BinarySearchTree<T>::make_empty(uptr& ptr)
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
bool BinarySearchTree<T>::insert(RT&& x, uptr& ptr)
{
	if(ptr == nullptr)
	{
		ptr = std::make_unique<BinaryNode>(std::forward<RT>(x), nullptr, nullptr);
		++currentSize;
		return true;
	}
	
	if(x < ptr->element)
		return insert(std::forward<RT>(x), ptr->left);
	else if(ptr->element < x)
		return insert(std::forward<RT>(x), ptr->right);
	else
	{
		assert(x == ptr->element);
		return false;
	}
}

template<typename T>
bool BinarySearchTree<T>::remove(const T& x, uptr& ptr, bool needUpdateSize)
{
	if(ptr == nullptr)
		return false;

	if(x < ptr->element)
	{
		return remove(x, ptr->left, needUpdateSize);
	}
	else if(ptr->element < x)
	{
		return remove(x, ptr->right, needUpdateSize);
	}
	else if(ptr->left != nullptr && ptr->right != nullptr)
	{
		auto& rptr = find_min(ptr->right);
		ptr->element = rptr->element;
		//only one calling to remove
		remove(ptr->element, rptr, false);
		if(needUpdateSize)
			--currentSize;
		return true;
	}
	else
	{
		//smart pointer donot use expilicit release operation
		ptr = (ptr->left != nullptr) ? std::move(ptr->left) : std::move(ptr->right);
		if(needUpdateSize)
			--currentSize;
		return true;
	}
}

template<typename T>
BinarySearchTree<T>::BinaryNode::BinaryNode
(const T& theElement, uptr&& theLeft, uptr&& theRight) :
	element{theElement}, left{std::move(theLeft)}, right{std::move(theRight)}
{}

template<typename T>
BinarySearchTree<T>::BinaryNode::BinaryNode
(T&& theElement, uptr&& theLeft, uptr&& theRight) :
	element{std::move(theElement)}, left{std::move(theLeft)}, right{std::move(theRight)}
{}

template<typename T>
void BinarySearchTree<T>::remove_all_leaves()
{
	remove_all_leaves(root);
}


template<typename T>
void BinarySearchTree<T>::remove_all_leaves(uptr& ptr)
{
	if(ptr == nullptr)
		return;
	if(ptr->left == nullptr && ptr->right == nullptr)
	{
		ptr.reset();
		currentSize--;
		return;
	}
	remove_all_leaves(ptr->left);
	remove_all_leaves(ptr->right);
}