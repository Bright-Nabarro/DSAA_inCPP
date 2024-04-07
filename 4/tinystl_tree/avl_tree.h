#pragma once
#include <cstddef>  //for size_t
#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <format>
#include "uptr_view.h"

template<typename Ty, typename Compare, bool multi>
class AvlTree
{
public:
	class const_iterator;
	class iterator;
	using size_type = size_t;

protected:
	struct AvlNode;
	using uptr = std::unique_ptr<AvlNode>;
	using uptrV = uptr_view<AvlNode>;

public:
	AvlTree(): root{nullptr}, currentSize{0}{}
	
	AvlTree(const AvlTree& rhs): root{nullptr}, currentSize{rhs.currentSize}
	{ root = std::move(clone(rhs.root, nullptr)); }

	AvlTree& operator=(const AvlTree& rhs)
	{
		auto copy {rhs};
		swap(copy);
		return *this;
	}

	AvlTree(AvlTree&& rhs) noexcept
	{
		root = std::exchange(rhs.root, nullptr);
		currentSize = std::exchange(rhs.currentSize, 0);
	}

	AvlTree& operator=(AvlTree&& rhs) noexcept
	{
		this->swap(rhs);
		return *this;
	}

	virtual ~AvlTree() = default;

	void swap(AvlTree& rhs) noexcept
	{
		std::swap(root, rhs.root);
		std::swap(currentSize, rhs.currentSize);
	}

	size_type size() const noexcept
	{	return currentSize;	}

	const Ty& find_min() const
	{	return find_min(root)->element; }

	const Ty& find_max() const
	{	return find_max(root)->element; }

	bool contains (const Ty& x) const noexcept
	{	return contains(x, root);	}

	bool empty() const noexcept
	{	return root == nullptr;		}

	bool operator==(const AvlTree& rhs) const
	{	return compare(root, rhs.root);	}

	//use DOT language
	void print_tree(std::ostream& out) const
	{
		out << "digraph G {\n";
		print_tree(out, root);
		out << "}\n";
	}

	void clear()
	{	clear(root);		}

	//should add requires Ty == Ty_ref& || t == Ty_ref&&
	template<typename Ty_ref>
	std::pair<bool, uptrV> insert(Ty_ref&& x)
	{	return insert(std::forward<Ty_ref>(x), root, nullptr);	}

	bool erase(const Ty& x)
	{	return erase(x, root);	}

protected:
	const uptrV find_min(uptrV pv) const;
	const uptrV find_max(uptrV pv) const;
	const uptrV find_minmax(uptrV pv, bool isLeft) const;
	//uptrV find_min(uptrV pv);
	//uptrV find_max(uptrV pv);
	bool contains(const Ty& x, uptrV pv) const noexcept;
	void print_tree(std::ostream& out, uptrV pv) const;
	void print_nodes(std::ostream& out, 
					 const uptrV pv, uptrV next) const;
	void print_parent(std::ostream& out,
					const uptrV pv, uptrV parent) const;
	bool compare(uptrV tptr, uptrV rptr) const; 

	uptr clone(const uptr& rhsp, uptrV parent);
	void clear(uptr& ptr);
	//----------------------------------
	template<typename Ty_ref>
	std::pair<bool, uptrV>
	insert(Ty_ref&& x, uptr& ptr, uptrV parent);
	bool erase(const Ty& x, uptr& ptr, bool needUpdate = true);
	
	int height(uptrV pv) const;
	void balance(uptr& ptr, uptrV& retV);
	//left means left at first
	void rotate_left_child(uptr& ptr, uptrV& retV);
	void rotate_right_child(uptr& ptr, uptrV& retV);
	void rotate_left_right(uptr& ptr, bool isLeft, uptrV& retV);
	//left means left subtree to the middle
	void double_left_child(uptr& ptr, uptrV& retV);
	void double_right_child(uptr& ptr, uptrV& retV);
private:
	inline const static int sk_allowImbalance{1};
protected:
	inline static Compare cmp;
	uptr root;
	size_type currentSize;
};

template<typename Ty, typename Compare, bool multi>
struct AvlTree<Ty, Compare, multi>::AvlNode
{
	Ty element;
	uptrV parent;
	uptr left;
	uptr right;
	int height;

	AvlNode(const Ty& theElement, 
			uptrV theParent		= nullptr, 
			uptr&& theLeft 		= nullptr,
			uptr&& theRight 	= nullptr, 
			int h 				= 0):
		element	{theElement},
		parent 	{theParent},
		left	{std::move(theLeft)},
		right 	{std::move(theRight)},
		height 	{h}
		{ }

	AvlNode(Ty&& theElement, 
			uptrV theParent		= nullptr,
			uptr&& theLeft 		= nullptr,
			uptr&& theRight 	= nullptr,
			int h 				= 0):
		element	{std::move(theElement)},
		parent 	{theParent},
		left	{std::move(theLeft)},
		right 	{std::move(theRight)},
		height 	{h}
		{ }
};

template<typename Ty, typename Compare, bool multi>
void swap(AvlTree<Ty, Compare, multi>& lhs, AvlTree<Ty, Compare, multi>& rhs) noexcept
{
	lhs.swap(rhs);
}


//private method implamentation------------------------------------------------------
template<typename Ty, typename Compare, bool multi>
auto AvlTree<Ty, Compare, multi>::find_min(uptrV pv) const -> const uptrV
{
	return find_minmax(pv, true);
}

template<typename Ty, typename Compare, bool multi>
auto AvlTree<Ty, Compare, multi>::find_max(uptrV pv) const -> const uptrV
{
	return find_minmax(pv, false);
}

template<typename Ty, typename Compare, bool multi>
auto AvlTree<Ty, Compare, multi>::find_minmax(uptrV pv, bool isLeft) const 
-> const uptrV
{
	if(pv == nullptr)
		throw std::runtime_error{"there on elements in search tree"};
	
	uptrV p {pv};
	uptrV ret;
	for(p  = pv; p != nullptr; p = isLeft ? p->left : p->right)
	{
		ret = p;
	}
	return ret;
}

//template<typename Ty, typename Compare, bool multi>
//auto AvlTree<Ty, Compare, multi>::find_min(uptrV pv) -> uptrV
//{
//	return const_cast<uptrV>(std::as_const(*this).find_min(pv));
//}
//
//template<typename Ty, typename Compare, bool multi>
//auto AvlTree<Ty, Compare, multi>::find_max(uptrV pv) -> uptrV
//{
//	return const_cast<uptrV>(std::as_const(*this).find_max(pv));
//}

template<typename Ty, typename Compare, bool multi>
bool AvlTree<Ty, Compare, multi>::contains(const Ty& x, uptrV pv) const noexcept
{
	if(pv == nullptr)
		return false;
	else if(pv->element == x)
		return true;
	else
		return contains(x, pv->left) || contains(x, pv->right);
}

template<typename Ty, typename Compare, bool multi>
void AvlTree<Ty, Compare, multi>::print_tree(std::ostream& out, uptrV pv) const
{
	if(pv == nullptr)
		return;

	print_nodes(out, pv, pv->left);
	print_nodes(out, pv, pv->right);
	print_parent(out, pv, pv->parent);

	print_tree(out, pv->left);
	print_tree(out, pv->right);
}

template<typename Ty, typename Compare, bool multi>
void AvlTree<Ty, Compare, multi>::
print_nodes(std::ostream& out, const uptrV pv, uptrV next) const
{
	static size_t counter {0};

	if(next != nullptr)
	{
		out << std::format("{} -> {};\n", pv->element, next->element);
	}
	else
		out << std::format("{} -> {}{};\n", pv->element, "null", counter++);
}

template<typename Ty, typename Compare, bool multi>
void AvlTree<Ty, Compare, multi>::print_parent
	(std::ostream& out, const uptrV pv, uptrV parent) const
{
	if(parent == nullptr)
		return;
	else
		out << std::format("{} -> {};\n", pv->element, pv->parent->element);
}

template<typename Ty, typename Compare, bool multi>
bool AvlTree<Ty, Compare, multi>::compare(uptrV tptr, uptrV rptr) const
{
	if(tptr == nullptr && rptr == nullptr)
		return true;
	if(tptr == nullptr || rptr == nullptr)
		return false;
	if(tptr->element != rptr->element)
		return false;
	
	if(!compare(tptr->left, rptr->left))
		return false;
	if(!compare(tptr->right, rptr->right))
		return false;

	return true;
}

template<typename Ty, typename Compare, bool multi>
auto AvlTree<Ty, Compare, multi>::clone(const uptr& rhsp, uptrV parent) -> uptr
{
	if(rhsp == nullptr)
		return nullptr;
	else
		return std::make_unique<AvlNode>
			(rhsp->element, parent, clone(rhsp->left, rhsp), 
				clone(rhsp->right, rhsp), rhsp->height);
}

template<typename Ty, typename Compare, bool multi>
void AvlTree<Ty, Compare, multi>::clear(uptr& pv)
{
	if(pv == nullptr)
		return;
	clear(pv->left);
	clear(pv->right);
	pv.reset();
	--currentSize;
}

#define CON_IF(X)	if constexpr (X) {
#define CON_ELSE	} else {
#define CON_END		}

template<typename Ty, typename Compare, bool multi>
template<typename Ty_ref>
auto AvlTree<Ty, Compare, multi>::insert(Ty_ref&& x, uptr& ptr, uptrV parent)
-> std::pair<bool, uptrV>
{
	std::pair<bool, uptrV> ret;
	if(ptr == nullptr)
	{
		ptr = std::make_unique<AvlNode>(std::forward<Ty_ref>(x), parent);
		++currentSize;
		ret = { true, ptr };
	}
	else if(cmp(x, ptr->element))
		ret = insert(std::forward<Ty_ref>(x), ptr->left, ptr);
	else if(cmp(ptr->element, x))
		ret = insert(std::forward<Ty_ref>(x), ptr->right, ptr);
	else
	{
	CON_IF(multi)		//insert left
		ret = insert(std::forward<Ty_ref>(x), ptr->left, parent);
	CON_ELSE
		ret = { false, nullptr };
	CON_END
	}

	balance(ptr, ret.second);
	return ret;
}

template<typename Ty, typename Compare, bool multi>
bool AvlTree<Ty, Compare, multi>::erase(const Ty& x, uptr& ptr, bool updateSize) 
{
	bool ret;
	static uptrV trash{};

	if(ptr == nullptr)
		ret = false;
	else if(cmp(x, ptr->element))
		ret = erase(x, ptr->left, updateSize);
	else if(cmp(ptr->element, x))
		ret = erase(x, ptr->right, updateSize);
	else
	{
	CON_IF(multi)
		// implament later
	CON_ELSE
		if(ptr->left != nullptr && ptr->right != nullptr)
		{
			uptrV rpv = find_min(ptr->right);
			ptr->element = rpv->element;
			erase(ptr->element, rpv.release(), false);
			if(updateSize)
				--currentSize;
			ret = true;
		}
		else
		{
			ptr = (ptr->left != nullptr) ? std::move(ptr->left) : std::move(ptr->right);
			if (ptr != nullptr)
			{
				if(ptr->left != nullptr)
					ptr->left->parent = ptr;
				else if(ptr->right != nullptr)
					ptr->right->parent = ptr;
			}
			balance(ptr, trash);
			if(updateSize)
				--currentSize;
			ret = true;
 		}
	CON_END
	}
	balance(ptr, trash);
	return ret;
}

template<typename Ty, typename Compare, bool multi>
int AvlTree<Ty, Compare, multi>::height(const uptrV pv) const
{
	return pv == nullptr ? -1 : pv->height;
}

template<typename Ty, typename Compare, bool multi>
void AvlTree<Ty, Compare, multi>::balance(uptr& ptr, uptrV& retV)
{
										  
	if(ptr == nullptr)
		return;

	if(height(ptr->left) - height(ptr->right) > sk_allowImbalance)
	{
		//if ptr->left == nullptr, the if condition is impossible pass
		assert(ptr->left != nullptr);
		if(height(ptr->left->left) >= height(ptr->left->right))
			rotate_left_child(ptr, retV);
		else
		{
			double_left_child(ptr, retV);
		}
	}
	else if(height(ptr->right) - height(ptr->left) > sk_allowImbalance)
	{
		assert(ptr->right != nullptr);
		if(height(ptr->right->right) >= height(ptr->right->left))
			rotate_right_child(ptr, retV);
		else
		{
			double_right_child(ptr, retV);
		}
	}

	ptr->height = std::max(height(ptr->left), height(ptr->right)) + 1;
}

template<typename Ty, typename Compare, bool multi>
void AvlTree<Ty, Compare, multi>::rotate_left_child(uptr& k2, uptrV& retV)
{
	rotate_left_right(k2, true, retV);
}

template<typename Ty, typename Compare, bool multi>
void AvlTree<Ty, Compare, multi>::rotate_right_child(uptr& k2, uptrV& retV)
{
	rotate_left_right(k2, false, retV);
}


template<typename Ty, typename Compare, bool multi>
void AvlTree<Ty, Compare, multi>::rotate_left_right(uptr& k2, bool isLeft, uptrV& retV)
{
	enum {NONE, K2FIR, K1SEC} updateMark {NONE};
	uptrV k2Pnt = k2->parent;

	//rotate operations just modifiy k1 and k2's height
	//k1 left child, right child does not change
	auto& k2Fir = isLeft ? k2->left : k2->right;
	auto& k2Sec = isLeft ? k2->right : k2->left;
	if(retV.is_reference(k2Fir))
		updateMark = K2FIR;
	uptr k1 = std::move(k2Fir);
	auto& k1Fir = isLeft ? k1->left : k1->right;
	auto& k1Sec = isLeft ? k1->right : k1->left;
	if(retV.is_reference(k1Sec))
		updateMark = K1SEC;

	//rotate operations modify k1, k2, Z, Y's parents
	//because of using uptr design, need check to update 
	// k1->left->left and right else !!!
	k2Fir = std::move(k1Sec);
	k2->height = std::max(height(k2Fir), height(k2Sec)) + 1;
	if(k2Fir != nullptr && k2Fir->left != nullptr)
		k2Fir->left->parent = k2Fir;
	if(k2Fir != nullptr && k2Fir->right != nullptr)
		k2Fir->right->parent = k2Fir;

	k1Sec = std::move(k2);
	k1->height = std::max(height(k1Fir), height(k2)) + 1;
	k2 = std::move(k1);
	//change k1 parent
	k2->parent = k2Pnt;
	//change retV
	switch(updateMark)
	{
	case NONE:
		break;
	case K2FIR:
		retV = k2;
		break;
	case K1SEC:
		retV = k2Fir;
		break;
	}

	assert(k1Fir == (isLeft ? k2->left : k2->right));
	assert(k1Sec == (isLeft ? k2->right : k2->left));
	k1Sec->parent = k2;		//k2
	if(k1Fir != nullptr)		//Z
		k1Fir->parent = k2;

	//X, Y
	if(k1Sec->left != nullptr)			//Y in left, X in right
		k1Sec->left->parent = k1Sec;
	if(k1Sec->right != nullptr)			//X in left, Y in right
		k1Sec->right->parent = k1Sec;
}

template<typename Ty, typename Compare, bool multi>
void AvlTree<Ty, Compare, multi>::double_left_child(uptr& k3, uptrV& retV)
{
	rotate_right_child(k3->left, retV);
	rotate_left_child(k3, retV);
}


template<typename Ty, typename Compare, bool multi>
void AvlTree<Ty, Compare, multi>::double_right_child(uptr& k3, uptrV& retV)
{
	rotate_left_child(k3->right, retV);
	rotate_right_child(k3, retV);
}


//==iterator===========================================================
template<typename Ty, typename Compare, bool multi>
class AvlTree<Ty, Compare, multi>::const_iterator
{
public:
	const_iterator operator++();
	const_iterator operator++(int);
	const_iterator operator--();
	const_iterator operator--(int);
	
	const Ty& operator*() const noexcept;
	const Ty* operator->() const noexcept;
private:
	uptrV ptr;
};

template<typename Ty, typename Compare, bool multi>
class AvlTree<Ty, Compare, multi>::iterator : public const_iterator
{
public:
	iterator operator++();
	iterator operator++(int);
	iterator operator--();
	iterator operator--(int);
	
	Ty& operator*() noexcept;
	Ty* operator->() noexcept;
};