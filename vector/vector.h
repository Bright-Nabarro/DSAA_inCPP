#pragma once
#include <algorithm>
#include <stdexcept>
namespace my_stl2
{

template <typename Object> class vector;

template <typename Object>
void swap(vector<Object>& v1, vector<Object>& v2) noexcept;

template <typename Object> class vector
{
  public:
	// big five
	explicit vector(int initSize = 0);
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
	//常用方法
	void push_back(const Object& x);
	void push_back(const Object&& x);
	void pop_back();
	Object& front() { return objects[0]; }
	const Object& front() const { return objects[0]; }
	Object& back() { return objects[theSize - 1]; }
	const Object& back() const { return objects[theSize - 1]; }
	//迭代器
	using iterator = Object*;
	using const_iterator = const Object*;
	iterator begin() { return &objects[0]; }
	const_iterator begin() const { return &objects[0]; }
	iterator end() { return &objects[theSize - 1]; }
	const_iterator end() const { return &objects[theSize - 1]; }
	static const int SPARE_CAPACITY = 16;

	friend void swap<Object>(vector<Object>& v1, vector<Object>& v2) noexcept;

  private:
	int theSize;
	int theCapacity;
	Object* objects;
};

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
	objects = new Object[theCapacity];
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
		throw std::out_of_range("my_adt vector index is out of range");
	return objects[index];
}

template <typename Object> const Object& vector<Object>::at(int index) const
{
	if (index >= theSize)
		throw std::out_of_range("my_adt vector index is out of range");
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

} // namespace my_adt
