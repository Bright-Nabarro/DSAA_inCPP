#pragma once
#include <stdexcept>
#include <utility>
#include <initializer_list>

namespace my_stl2
{

// class list have three nested class
// all nested class's implation below
// use sentinel _head and _tail,
// begin() returns _head->next
// end() returns _tail
template <typename Object> class list
{
	// nested class
  private:
	struct Node;
  public:
	// type information
	using value_type = Object;

  public:
	class const_iterator;
	class iterator;
	// method
  public:
	list() { init(); }
	list(const std::initializer_list<Object>& inil);
	// the big five
	list(const list& rhs);
	list& operator=(const list& rhs);
	list(list&& rhs) noexcept(
		std::is_nothrow_move_constructible<Object>::value);
	list& operator=(list&& rhs) noexcept(
		std::is_nothrow_move_assignable<Object>::value&&
			std::is_nothrow_swappable_v<Object>);
	~list();
	// itr method
	iterator begin() { return _head->_next; }
	const_iterator begin() const { return _head->_next; }
	iterator end() { return _tail; }
	const_iterator end() const { return _tail; }
	// element access
	Object& front() { return _head->_element; }
	const Object& front() const { return _head->_element; }
	Object& back() { return _tail->_element; }
	const Object& back() const { return _tail->_element; }
	// capacity
	size_t size() const noexcept { return _size; }
	bool empty() const noexcept { return _size == 0; }
	// modifiers
	void swap(list& rhs) noexcept(std::is_nothrow_swappable_v<Object>);
	void clear() noexcept
	{
		while (!empty())
			pop_front();
	}
	void push_front(const Object& x) { insert(begin(), x); }
	void push_front(Object&& x) { insert(begin(), std::move(x)); }
	void push_back(const Object& x) { insert(end(), (x)); }
	void push_back(Object&& x) { insert(end(), std::move(x)); }
	void pop_front() noexcept { erase(begin()); }
	void pop_back() noexcept { erase(back()); }
	iterator insert(iterator itr, const Object& x);
	iterator insert(iterator itr, Object&& x);
	iterator erase(iterator itr) noexcept;
	iterator erase(iterator from, iterator to);
	// for exercises
	void swap_adjacent(iterator itr);
	void swap_adjacent(size_t n);
	// data members
  private:
	size_t _size;
	Node* _head;
	Node* _tail;
	void init();
};

//==================Node====================//
template <typename Object> struct list<Object>::Node
{
	Object _element;
	Node* _prev;
	Node* _next;

	Node(const Object& element = Object{}, Node* prev = nullptr,
		 Node* next = nullptr)
		: _element(element), _prev(prev), _next(next){};

	Node(Object&& element, Node* prev = nullptr, Node* next = nullptr)
		: _element(element), _prev(prev), _next(next){};
};

//===================const_iterator=======================//
template <typename Object> class list<Object>::const_iterator
{
	// outer class can access and modify
	friend class list<Object>;

  public:
	//iterator info
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = Object;
	using difference_type = std::ptrdiff_t;
	using pointer = Object*;
	using reference = Object&;

	const_iterator() : current{nullptr} {}
	// overloading operator
	const Object& operator*() const { return current->_element; }
	const Object* operator->() const { return &current->_element; }
	// return item as a parameter of const_iterator protected constructor
	const_iterator operator++()
	{
		current = current->_next;
		return *this;
	}
	const_iterator operator++(int);
	const_iterator operator--()
	{
		current = current->_prev;
		return *this;
	}
	const_iterator operator--(int);
	bool operator==(const const_iterator& citr) const
	{
		return current == citr.current;
	}
	bool operator!=(const const_iterator& citr) const
	{
		return current != citr.current;
	}

  protected:
	Node* current;
	// for outer class construct
	const_iterator(Node* p) : current{p} {}
};

template <typename Object>
typename list<Object>::const_iterator
list<Object>::const_iterator::operator++(int)
{
	auto temp = current;
	current = current->_next;
	return temp;
}

template <typename Object>
typename list<Object>::const_iterator
list<Object>::const_iterator::operator--(int)
{
	auto temp = current;
	current = current->_prev;
	return temp;
}

//=========================iterator==========================//
// iterator inherits from const_iterator
// added method which can modify template Object type
template <typename Object> class list<Object>::iterator : public const_iterator
{
	friend class list<Object>;
	using const_iterator::current;

  public:
	iterator() {}
	// overloading operator (non const function)
	Object& operator*() { return current->_element; }
	Object* operator->() { return &current->_element; }
	iterator operator++()
	{
		current = current->_next;
		return *this;
	}
	iterator operator++(int);
	iterator operator--()
	{
		current = current->_prev;
		return *this;
	}
	iterator operator--(int);

  protected:
	iterator(Node* p) : const_iterator{p} {}
};

template <typename Object>
typename list<Object>::iterator list<Object>::iterator::operator++(int)
{
	auto temp = current;
	current = current->_next;
	return temp;
}

template <typename Object>
typename list<Object>::iterator list<Object>::iterator::operator--(int)
{
	auto temp = current;
	current = current->_prev;
	return temp;
}

//=========================list method============================//
template <typename Object> void list<Object>::init()
{
	// exception safety
	_size = 0;
	_head = nullptr;
	_tail = nullptr;
	// delete nullptr is safe
	// if _head allocate failed, _head is nullptr
	// if _tail allocate failed, _tail is nullptr
	// and delete _head
	try
	{
		_head = new Node;
		_tail = new Node;
	}
	catch (...)
	{
		delete _head;
		_head = nullptr; // preventing dangling pointer
		throw;
	}
	_head->_next = _tail;
	_tail->_prev = _head;
}

template <typename Object>
list<Object>::list(const std::initializer_list<Object>& inil)
{
	init();
	for(const auto& x: inil)
		push_back(x);
}

// the big five implation
template <typename Object> 
list<Object>::list(const list& rhs)
{
	init();
	for (const auto& x : rhs)
		push_back(x);
}

template <typename Object>
list<Object>& list<Object>::operator=(const list& rhs)
{
	auto temp(rhs);
	swap(temp);
	return *this;
}

template <typename Object>
list<Object>::list(list&& rhs) noexcept(
	std::is_nothrow_move_constructible<Object>::value)
	: _head{rhs._head}, _tail{rhs._tail}, _size{rhs._size}
{
	rhs._head = nullptr;
	rhs._tail = nullptr;
	rhs._size = 0;
}

template <typename Object>
list<Object>& list<Object>::operator=(list&& rhs) noexcept(
	std::is_nothrow_move_assignable<Object>::value&&
		std::is_nothrow_swappable_v<Object>)
{
	swap(rhs);
	return *this;
}

template <typename Object> list<Object>::~list()
{
	clear();
	delete _head;
	delete _tail;
}

// list modifiers implation
template <typename Object>
void list<Object>::swap(list& rhs) noexcept(std::is_nothrow_swappable_v<Object>)
{
	std::swap(_size, rhs._size);
	std::swap(_head, rhs._head);
	std::swap(_tail, rhs._tail);
}

template <typename Object>
typename list<Object>::iterator list<Object>::insert(iterator itr,
													 const Object& x)
{
	Node* p = itr.current;
	Node* new_node = new Node{x, p->_prev, p};
	_size++;
	p->_prev->_next = new_node;
	p->_prev = new_node;
	return new_node;
}

template <typename Object>
typename list<Object>::iterator list<Object>::insert(iterator itr, Object&& x)
{
	Node* p = itr.current;
	Node* new_node = new Node{std::move(x), p->_prev, p};
	_size++;
	p->_prev->_next = new_node;
	p->_prev = new_node;
	return new_node;
}

template <typename Object>
typename list<Object>::iterator list<Object>::erase(iterator itr) noexcept
{
	Node* p = itr.current;
	iterator result{p->_next};
	p->_prev->_next = p->_next;
	p->_next->_prev = p->_prev;
	delete p;
	_size--;
	return result;
}

template <typename Object>
typename list<Object>::iterator list<Object>::erase(iterator from, iterator to)
{
	for (iterator itr = from; itr != to;)
		itr = erase(itr);
	return to;
}

template <typename Object>
void list<Object>::swap_adjacent(iterator itr)
{
	//swap itr and itr+1
	Object ele_1 = *itr;
	itr = erase(itr);
	Object ele_2 = *itr;
	itr = erase(itr);
	insert(itr, ele_2);
	insert(itr, ele_1);
}

template <typename Object>
void list<Object>::swap_adjacent(size_t n)
{
	auto ptr = begin();
	for(int i = 0; i < n; i++)
		++ptr;
	swap_adjacent(ptr);
}

} // namespace my_adt
