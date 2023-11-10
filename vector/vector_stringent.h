#pragma once
#include <algorithm>
#include <initializer_list>
#include <stdexcept>

namespace my_stl2
{

template <typename Object> class vector;

template <typename Object>
void swap(vector<Object>& v1, vector<Object>& v2) noexcept;

template <typename Object> class vector
{
  public:
	explicit vector(int initSize = 0);
	vector(const std::initializer_list<Object>& inil);
	template <typename other_iterator>
	vector(other_iterator beg_ptr, other_iterator end_ptr);
	// big five
	vector(const vector& rhs);
	vector(vector&& rhs) noexcept;
	vector& operator=(const vector& rhs);
	vector& operator=(vector&& rhs) noexcept;
	~vector();

	//基本与索引
	void resize(int newSize);
	void reserve(int newCapacity);
	Object& operator[](int index);
	const Object& operator[](int index) const;
	Object& at(int index);
	const Object& at(int index) const;

  private:
	//迭代器
	class const_iterator;
	class iterator;

  public:
	//迭代器方法
	iterator begin() { return {&objects[0]}; }
	const_iterator begin() const { return {&objects[0]}; }
	iterator end() { return {&objects[theSize - 1]}; }
	const_iterator end() const { return {&objects[theSize - 1]}; }
	static const int SPARE_CAPACITY = 16;

	//常用方法
	void push_back(const Object& x);
	void push_back(const Object&& x);
	void pop_back();
	Object& front() { return *begin(); }
	const Object& front() const { return *begin(); }
	Object& back() { return *end(); }
	const Object& back() const { return *end(); }
	void insert(iterator itr, const Object& x);
	void erase(iterator itr);
	void erase(iterator from, iterator to);

	friend void swap<Object>
		(vector<Object>& v1, vector<Object>& v2) noexcept;

  private:
	int theSize;
	int theCapacity;
	Object* objects;
};

//======================const_iterator=======================
template <typename Object> class vector<Object>::const_iterator
{
	friend class vector;

  protected:
	Object* ptr;
	const_iterator(Object* p) : ptr{p} {}
	void check_inside(vector<Object>* outer);

  public:
	const Object& operator*() const { return *ptr; }
	const Object* operator->() const { return ptr; }
	const_iterator operator++();
	const_iterator operator++(int);
	const_iterator operator--();
	const_iterator operator--(int);
	const_iterator operator+(int n);
	const_iterator operator-(int n);
	bool operator==(const_iterator itr) { return ptr == itr.ptr; }
	bool operator!=(const_iterator itr) { return ptr != itr.ptr; }
};

template <typename Object>
typename vector<Object>::const_iterator
vector<Object>::const_iterator::operator++()
{
	--ptr;
	return {ptr};
}

template <typename Object>
typename vector<Object>::const_iterator
vector<Object>::const_iterator::operator++(int)
{
	auto temp = ptr++;
	return {temp};
}

template <typename Object>
typename vector<Object>::const_iterator
vector<Object>::const_iterator::operator--()
{
	--ptr;
	return {ptr};
}

template <typename Object>
typename vector<Object>::const_iterator
vector<Object>::const_iterator::operator--(int)
{
	auto temp = ptr--;
	return {temp};
}

template <typename Object>
typename vector<Object>::const_iterator
vector<Object>::const_iterator::operator+(int n)
{
	return {ptr + n};
}

template <typename Object>
typename vector<Object>::const_iterator
vector<Object>::const_iterator::operator-(int n)
{
	return {ptr - n};
}

template <typename Object>
void vector<Object>::const_iterator::check_inside(vector<Object>* outer)
{
	if (ptr >= outer->begin().ptr && ptr < outer->end().ptr)
		return;
	throw std::out_of_range("vector iterator out of range");
}

//======================iterator=======================
template <typename Object>
class vector<Object>::iterator : public const_iterator
{
	friend class vector;

  protected:
	iterator(Object* p) : const_iterator{p} {}

  public:
	Object& operator*() { return *const_iterator::ptr; }
	Object* operator->() { return const_iterator::ptr; }
	iterator operator++();
	iterator operator++(int);
	iterator operator--();
	iterator operator--(int);
	iterator operator+(int n);
	iterator operator-(int n);
};

template <typename Object>
typename vector<Object>::iterator vector<Object>::iterator::operator++()
{
	++const_iterator::ptr;
	return {const_iterator::ptr};
}

template <typename Object>
typename vector<Object>::iterator vector<Object>::iterator::operator++(int)
{
	auto temp = const_iterator::ptr++;
	return {temp};
}

template <typename Object>
typename vector<Object>::iterator vector<Object>::iterator::operator--()
{
	--const_iterator::ptr;
	return {const_iterator::ptr};
}

template <typename Object>
typename vector<Object>::iterator vector<Object>::iterator::operator--(int)
{
	auto temp = const_iterator::ptr--;
	return {temp};
}

template <typename Object>
typename vector<Object>::iterator vector<Object>::iterator::operator+(int n)
{
	return {const_iterator::ptr + n};
}

template <typename Object>
typename vector<Object>::iterator vector<Object>::iterator::operator-(int n)
{
	return {const_iterator::ptr - n};
}

//======================vector method=========================
template <typename Object>
void swap(vector<Object>& v1, vector<Object>& v2) noexcept
{
	std::swap(v1.theSize, v2.theSize);
	std::swap(v1.theCapacity, v2.theCapacity);
	std::swap(v1.objects, v2.objects);
}

template <typename Object>
vector<Object>::vector(int iniSize)
	: theSize{iniSize}, theCapacity{iniSize + SPARE_CAPACITY}
{
	try
	{
		objects = new Object[theCapacity];
	}
	catch (...)
	{
		objects = nullptr;
		throw;
	}
}

template <typename Object>
vector<Object>::vector(const std::initializer_list<Object>& inil)
	: vector(inil.size())
{
	auto ptr = begin();
	for (auto iptr = inil.begin(); iptr != inil.end(); iptr++, ptr++)
		*ptr = *iptr;
}

template <typename Object>
template <typename other_iterator>
vector<Object>::vector(other_iterator beg_ptr, other_iterator end_ptr)
{
	vector();
	for (auto ptr = beg_ptr; ptr != end_ptr; ptr++)
		push_back(*ptr);
}

template <typename Object>
vector<Object>::vector(const vector& rhs)
	: theSize{rhs.theSize}, theCapacity{rhs.theCapacity}
{
	objects = new Object[theCapacity];
	//带有异常安全检测, 如果copy失败, 删除新分配的objects
	try
	{
		std::copy(rhs.objects, rhs.objects + theSize, objects);
	}
	catch (...)
	{
		delete[] objects;
		throw;
	}
}

template <typename Object>
vector<Object>::vector(vector&& rhs) noexcept
	: theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{rhs.objects}
{
	rhs.objects = nullptr;
}

template <typename Object>
vector<Object>& vector<Object>::operator=(const vector& rhs)
{
	vector copy = rhs;
	swap(*this, copy);
	return *this;
}

template <typename Object>
vector<Object>& vector<Object>::operator=(vector&& rhs) noexcept
{
	swap(*this, rhs);
	return *this;
}

template <typename Object> vector<Object>::~vector() { delete[] objects; }

template <typename Object> void vector<Object>::resize(int newSize)
{
	//只有size > theCapacity时才会重新分配内存
	//调用时不可能执行reserve的第一个if语句
	if (newSize > theCapacity)
		reserve(newSize * 2);
	theSize = newSize;
}

template <typename Object> void vector<Object>::reserve(int newCapatity)
{
	if (newCapatity < theSize)
		return;

	Object* newObjects = new Object[newCapatity];
	try
	{
		std::copy(objects, objects + theSize, newObjects);
	}
	catch (...)
	{
		delete[] newObjects;
		throw;
	}
	delete[] objects;
	objects = newObjects;
	theCapacity = newCapatity;
}

template <typename Object> Object& vector<Object>::operator[](int index)
{
	return objects[index];
}

template <typename Object>
const Object& vector<Object>::operator[](int index) const
{
	return objects[index];
}

template <typename Object> Object& vector<Object>::at(int index)
{
	if (index >= theSize)
		throw std::out_of_range("my_stl2 vector index is out of range");
	return objects[index];
}

template <typename Object> const Object& vector<Object>::at(int index) const
{
	if (index >= theSize)
		throw std::out_of_range("my_stl2 vector index is out of range");
	return objects[index];
}

template <typename Object> void vector<Object>::push_back(const Object& x)
{
	if (theSize == theCapacity)
		reserve(theSize * 2 + 1);
	objects[theSize++] = x;
}

template <typename Object> void vector<Object>::push_back(const Object&& x)
{
	if (theSize == theCapacity)
		reserve(theSize * 2 + 1);
	objects[theSize++] = std::move(x);
}

template <typename Object> void vector<Object>::pop_back() { --theSize; }

template <typename Object>
void vector<Object>::insert(iterator itr, const Object& x)
{
	itr.check_inside(this);
	if (theSize == theCapacity)
		reserve(theSize * 2 + 1);
	for (auto p = end() - 1; p != itr; p--)
		*(p + 1) = *p;
	*(itr + 1) = x;
	theSize++;
}

template <typename Object> void vector<Object>::erase(iterator itr)
{
	itr.check_inside(this);
	for (auto p = itr; p != end(); p++)
		*p = *(p + 1);
	theSize--;
}

template <typename Object>
void vector<Object>::erase(iterator from, iterator to)
{
	for (auto itr = from; itr != to; itr++)
		erase(itr);
}

} // namespace my_stl2
