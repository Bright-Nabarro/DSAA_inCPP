#pragma once
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace my_stl2
{
//stringent check
//check empty
//fornt, back
//remove their noexcept attribute
class list_empty: public std::runtime_error
{
public:
	list_empty(const char* msg = "list is empty"):
	   std::runtime_error(msg){}
};
//check iterator invalid
//iterator operator++--
class iterator_invalid: public std::runtime_error
{
public:
	//need to specify iterator or reverse_itr
	iterator_invalid(const char* msg):
		std::runtime_error(msg){}
};
// Cannot precisely check iterator and reverse_iterator respectively.
// It is related to the virtual function.
// Invoke this virtual function in the insert and erase methods.
// Pass the list's 'this' pointer to the iterator's method.
// To access the list's private items in the iterator,
// we must declare four friend iterator classes.

// class list have three nested class
// all nested class's implation below
// use sentinel _head and _tail,
// begin() returns _head->next
// end() returns _tail
template <typename Object> class list
{
	friend class itr_check_interface;
	// nested class
  private:
	struct Node;

  public:
	// type information
	using value_type = Object;

  public:
	class const_iterator;
	class iterator;
	class const_reverse_iterator;
	class reverse_iterator;
	// method
  public:
	// normal constructor
	list() { init(); }
	list(const std::initializer_list<Object>& inil);
	template <typename other_iterator>
	list(other_iterator beg_ptr, other_iterator end_ptr);

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
	const_iterator cbegin() const { return _head->_next; }
	reverse_iterator rbegin() { return _tail->_prev; }
	const_reverse_iterator rbegin() const { return _tail->_prev; }
	const_reverse_iterator crbegin() const { return _tail->_prev; }

	iterator end() { return _tail; }
	const_iterator end() const { return _tail; }
	const_iterator cend() const { return _tail; }
	reverse_iterator rend() { return _head; }
	const_reverse_iterator rend() const { return _head; }
	const_reverse_iterator crend() const { return _head; }

	// element access
	Object& front()
		{ check_noempty(); return _head->_element; }
	const Object& front() const 
		{ check_noempty(); return _head->_element; }
	Object& back() 
		{ check_noempty(); return _tail->_element; }
	const Object& back() const 
		{ check_noempty(); return _tail->_element; }

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
	void push_front(const Object& x) 
		{ insert(begin(), x); }
	void push_front(Object&& x) 
		{ insert(begin(), std::move(x)); }
	void push_back(const Object& x) 
		{ insert(end(), (x)); }
	void push_back(Object&& x) 
		{ insert(end(), std::move(x)); }
	void pop_front() 
		{ erase(begin()); }
	void pop_back() 
		{ erase(back()); }

	iterator insert(iterator itr, const Object& x);
	iterator insert(iterator itr, Object&& x);
	iterator erase(iterator itr) ;
	iterator erase(iterator from, iterator to);

	// for exercises
	void swap_adjacent(iterator itr);
	void swap_adjacent(size_t n);
	void splice(iterator position, list& lst);
	// for stringent check
	void check_noempty();

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
template <typename Object> 
class list<Object>::const_iterator
{
	// outer class can access and modify
	friend class list<Object>;
  public:
	// iterator info
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
		check_noinvalid();
		return *this;
	}
	const_iterator operator++(int);
	const_iterator operator--()
	{
		current = current->_prev;
		check_noinvalid();
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
	size_t operator-(const_iterator itr);

  protected:
	Node* current;
	// for outer class construct
	const_iterator(Node* p) : current{p} {}
	void check_noinvalid() const;
};

template <typename Object>
typename list<Object>::const_iterator
list<Object>::const_iterator::operator++(int)
{
	auto temp = current;
	current = current->_next;
	check_noinvalid();
	return temp;
}

template <typename Object>
typename list<Object>::const_iterator
list<Object>::const_iterator::operator--(int)
{
	auto temp = current;
	current = current->_prev;
	check_noinvalid();
	return temp;
}

template <typename Object>
void list<Object>::const_iterator::check_noinvalid() const
{
	if(current == nullptr)
		throw iterator_invalid("iterator is nullptr");
}

//=========================iterator==========================//
// iterator inherits from const_iterator
// added method which can modify template Object type
template <typename Object> 
class list<Object>::iterator : public const_iterator
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
		const_iterator::check_noinvalid();
		return *this;
	}
	iterator operator++(int);
	iterator operator--()
	{
		current = current->_prev;
		const_iterator::check_noinvalid();
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
	const_iterator::check_noinvalid();
	return temp;
}

template <typename Object>
typename list<Object>::iterator list<Object>::iterator::operator--(int)
{
	auto temp = current;
	current = current->_prev;
	const_iterator::check_noinvalid();
	return temp;
}


//===================const_reverse_iterator========================//
template <typename Object>
class list<Object>::const_reverse_iterator: public const_iterator
{
	friend class list<Object>;
	using const_iterator::current;
public:
	const_reverse_iterator(){}
	const_reverse_iterator operator++()
	{
		current = current->_prev;
		const_iterator::check_noinvalid();
		return *this;
	}
	const_reverse_iterator operator++(int);
	const_reverse_iterator operator--()
	{
		current = current ->_next;
		const_iterator::check_noinvalid();
		return *this;
	}
	const_reverse_iterator operator--(int);
protected:
	const_reverse_iterator(Node* p): const_iterator{p} {}
};

template <typename Object>
typename list<Object>::const_reverse_iterator 
	list<Object>::const_reverse_iterator::operator++(int)
{
	auto temp = current;
	current = current->_prev;
	const_iterator::check_noinvalid();
	return temp;
}

template <typename Object>
typename list<Object>::const_reverse_iterator 
	list<Object>::const_reverse_iterator::operator--(int)
{
	auto temp = current;
	current = current->_next;
	const_iterator::check_noinvalid();
	return temp;
}

//=======================reverse_iterator===========================//
template <typename Object>
class list<Object>::reverse_iterator: public iterator
{
	friend class list<Object>;
	using const_iterator::current;
public:
	reverse_iterator(){}
	reverse_iterator operator++()
	{
		current = current->_prev;
		const_iterator::check_noinvalid();
		return *this;
	}
	reverse_iterator operator++(int);
	reverse_iterator operator--()
	{
		current = current ->_next;
		const_iterator::check_noinvalid();
		return *this;
	}
	reverse_iterator operator--(int);
protected:
	reverse_iterator(Node* p): iterator{p} {}
};

template <typename Object>
typename list<Object>::reverse_iterator list<Object>::reverse_iterator::operator++(int)
{
	auto temp = current;
	current = current->_prev;
	const_iterator::check_noinvalid();
	return temp;
}

template <typename Object>
typename list<Object>::reverse_iterator list<Object>::reverse_iterator::operator--(int)
{
	auto temp = current;
	current = current->_next;
	const_iterator::check_noinvalid();
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
	for (const auto& x : inil)
		push_back(x);
}

template <typename Object>
template <typename other_iterator>
list<Object>::list(other_iterator beg_ptr, other_iterator end_ptr)
{
	init();
	for (auto ptr = beg_ptr; ptr != end_ptr; ptr++)
		push_back(*ptr);
}

// the big five implation
template <typename Object> list<Object>::list(const list& rhs)
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
	: _size{rhs._size}, _head{rhs._head}, _tail{rhs._tail}
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
typename list<Object>::iterator list<Object>::erase(iterator itr) 
{
	check_noempty();
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

template <typename Object> void list<Object>::swap_adjacent(iterator itr)
{
	// swap itr and itr+1
	Object ele_1 = *itr;
	itr = erase(itr);
	Object ele_2 = *itr;
	itr = erase(itr);
	insert(itr, ele_2);
	insert(itr, ele_1);
}

template <typename Object> void list<Object>::swap_adjacent(size_t n)
{
	auto ptr = begin();
	for (int i = 0; i < n; i++)
		++ptr;
	swap_adjacent(ptr);
}

template <typename Object>
void list<Object>::splice(iterator position, list& lst)
{
	position.current->_prev->_next = lst._head->_next;
	lst._tail->_prev->_next = position.current;
	_size += lst._size;
	lst._head = lst._tail = nullptr;
	lst._size = 0;
}

template <typename Object>
void list<Object>::check_noempty()
{
	if(empty())
		throw list_empty();
}


} // namespace my_stl2
