#pragma once
#include <cstdlib>
#include <iostream>

template<typename T>
class single_list
{
private:
	struct node{
		T _element;
		node* _next;
		node(node* ptr = nullptr): _next{ptr}{}
		node(const T& element, node* ptr = nullptr):
			_element{element}, _next{ptr}{}
		node(T&& element, node* ptr = nullptr):
			_element{std::move(element)}, _next{ptr}{}
	};
	node* _header;
	size_t _size;
public:
	void init();
	single_list() { init(); }
	single_list(const single_list&) = delete;
	single_list& operator=(const single_list&) = delete;
	single_list(single_list&&);
	single_list& operator=(single_list&&);
	~single_list();

	size_t size() const { return _size; }
	node* begin() { return _header->_next; }
	node* begin() const { return _header->_next; }
	void print(std::ostream& os = std::cout) const;
	bool contain(const T& x) const;
	void insert(const T& x);
	void insert(const T&& x);
	void remove(const T& x);
};

template<typename T>
void single_list<T>::init() 
{
	_size = 0;
	_header = new node; 
}

template<typename T>
single_list<T>::single_list(single_list&& rhs):
	_header{rhs._header}, _size{rhs._size}
{
	rhs._header = nullptr;
}

template<typename T>
single_list<T>& single_list<T>::operator=(single_list&& rhs)
{
	_header = rhs._header;
	_size = rhs._size;
	rhs._header = nullptr;
}

template<typename T>
single_list<T>::~single_list()
{
	for(auto p = _header; p != nullptr;)
	{
		auto temp = p;
		p = p->_next;
		delete temp;
	}
}

template<typename T>
bool single_list<T>::contain(const T& x) const
{
	for(auto p = begin(); p != nullptr; p=p->_next)
	{
		if(x < *p)
			return false;
		else if(!(*p < x))
			return true;
	}
	return false;
}

template<typename T>
void single_list<T>::insert(const T& x)
{
	auto forward_p = _header;
	auto back_p = begin();
	for(;back_p != nullptr;forward_p=forward_p->_next, back_p=back_p->_next)
	{
		if(forward_p->_element < x && x < back_p->_element)
		{
			forward_p->_next = new node(x, back_p);
			_size++;
			return;
		}
	}
	forward_p->_next = new node(x);
	_size++;
}

template<typename T>
void single_list<T>::insert(const T&& x)
{
	auto forward_p = _header;
	auto back_p = begin();
	for(;back_p != nullptr;forward_p=forward_p->_next, back_p=back_p->_next)
	{
		if(forward_p->_element < x && x < back_p->_element)
		{
			forward_p->_next = new node(std::move(x), back_p);
			_size++;
			return;
		}
	}
	forward_p->_next = new node(std::move(x));
	_size++;
}

template<typename T>
void single_list<T>::remove(const T& x)
{
	auto forward_p = begin();
	auto back_p = forward_p->_next;

	if(!(forward_p->_element < x) && !(x < forward_p->_element))
	{
		forward_p->_next = back_p->_next;
		delete back_p;
		_size--;
		return;
	}
	for(;back_p != nullptr;forward_p=forward_p->_next, back_p=back_p->_next)
	{
		if(!(*back_p < x) && !(x < *back_p))
		{
			forward_p->_next = back_p->_next;
			delete back_p;
			_size--;
			return;
		}
	}
}

template<typename T>
void single_list<T>::print(std::ostream& os) const
{
	for(auto p = begin(); p != nullptr; p=p->_next)
		os << p->_element << " ";
	os << std::endl;
}
