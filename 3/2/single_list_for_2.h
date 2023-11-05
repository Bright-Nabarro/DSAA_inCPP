#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>

namespace myds
{

template <typename T> class single_list
{
  public:
	typedef std::size_t size_type;
	typedef T value_type;

  private:
	template <typename U>
	//节点
	struct single_list_node
	{
		U _element;
		single_list_node<U>* next;
		single_list_node() : next(nullptr) {}
		single_list_node(U element) : _element(element), next(nullptr) {}
		single_list_node(U element, single_list_node<U>* n)
			: _element(element), next(n)
		{
		}
	};
	single_list_node<T>* firstNode;
	single_list_node<T>* lastNode;
	size_type _size;

  public:
	//构造，复制构造，析构
	single_list()
	{
		firstNode = nullptr;
		lastNode = nullptr;
		_size = 0;
	}
	single_list(const std::initializer_list<T> elements);
	single_list(const single_list<T>& sec_list);
	virtual ~single_list()
	{
		single_list_node<T>* nextNode;
		while (firstNode != nullptr)
		{
			nextNode = firstNode->next;
			delete firstNode;
			_size--;
			firstNode = nextNode;
		}
		assert(_size == 0);
	}
	single_list<T>& operator=(const single_list<T>& sec_list);
	//头，尾迭代器
	class iterator;
	iterator begin() { return iterator(firstNode); }
	iterator end()
	{
		if (lastNode == nullptr)
			return lastNode;
		return lastNode->next;
	}
	//
	bool empty() const { return _size == 0; }
	size_type size() const { return _size; }
	T& at(size_type index) const;
	T& operator[](size_type index) const;
	void push_back(const T& element);
	size_type find(const T& element) const;
	void insert(size_type index, const T& element);
	//替换元素
	void set(size_type index, const T& element);
	void erase(size_type index);
	//删除范围
	void remove(size_type fromIndex, size_type toIndex);
	void clear();
	//输出
	void output(std::ostream& os = std::cout);

	// forward iterator
	class iterator
	{
	  private:
		single_list_node<T>* node;

	  public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
		//构造
		iterator() : node(nullptr) {}
		iterator(single_list_node<T>* node_) : node(node_) {}
		//指针方法
		////解引用，返回引用
		T& operator*() const { return node->_element; }
		////->返回定义的指针
		T* operator->() const { return &node->_element; }
		//++
		iterator& operator++()
		{
			node = node->next;
			return *this;
		}
		iterator& operator++(int)
		{
			auto temp = *this;
			node = node->next;
			return temp;
		}
		//== !=
		bool operator!=(const iterator& it2) const { return node != it2.node; }

		bool operator==(const iterator& it2) const { return node == it2.node; }
	};

  public:
	// solutions for 2
	void swap_adjacent(size_t n)
	{
		if (n > size() - 1)
			throw std::out_of_range("swap adjacent out of range");

		single_list_node<T>* node = firstNode;
		for (size_t i = 0; i < n - 1; i++)
			node = node->next;
		auto forward = node->next;
		node->next = forward->next;
		auto store = node->next->next;
		node->next->next = forward;
		forward->next = store;
	}
};

template <typename T>
single_list<T>::single_list(const single_list<T>& sec_list)
{
	single_list_node<T>* nextNode;
	while (firstNode != nullptr)
	{
		nextNode = firstNode->next;
		delete firstNode;
		_size--;
		firstNode = nextNode;
	}
	if (firstNode == nullptr)
		_size = 0;
	assert(_size == 0);
	single_list_node<T>* cur;
	single_list_node<T>* sec_cur = sec_list.firstNode;
	cur = new single_list_node<T>(sec_cur->_element);
	_size++;
	firstNode = cur;
	while (true)
	{
		sec_cur = sec_cur->next;
		cur->next = new single_list_node<T>(sec_cur->_element);
		_size++;
		cur = cur->next;
		//退出条件
		if (sec_cur->next == nullptr)
		{
			lastNode = cur;
			break;
		}
	}
	assert(_size == sec_list._size);
}

template <typename T>
single_list<T>::single_list(const std::initializer_list<T> elements)
{
	_size = 0;
	firstNode = nullptr;
	lastNode = nullptr;
	auto iniptr = elements.begin();
	auto cur = new single_list_node<T>(*iniptr++);
	_size++;
	firstNode = cur;
	for (; iniptr != elements.end(); iniptr++)
	{
		cur->next = new single_list_node<T>(*iniptr);
		_size++;
		cur = cur->next;
	}
	lastNode = cur;
	assert(_size == elements.size());
}

template <typename T>
single_list<T>& single_list<T>::operator=(const single_list<T>& sec_list)
{
	single_list_node<T>* nextNode;
	while (firstNode != nullptr)
	{
		nextNode = firstNode->next;
		delete firstNode;
		_size--;
		firstNode = nextNode;
	}
	assert(_size == 0);
	single_list_node<T>* cur;
	single_list_node<T>* sec_cur = sec_list.firstNode;
	cur = new single_list_node<T>(sec_cur->_element);
	_size++;
	firstNode = cur;
	while (true)
	{
		sec_cur = sec_cur->next;
		cur->next = new single_list_node<T>(sec_cur->_element);
		_size++;
		cur = cur->next;
		//退出条件
		if (sec_cur->next == nullptr)
		{
			lastNode = cur;
			break;
		}
	}
	assert(_size == sec_list._size);
	return *this;
}

template <typename T> inline T& single_list<T>::at(size_type index) const
{
	if (index < 0 || index >= _size)
	{
		std::ostringstream s;
		s << ".at: index range " << index << " must "
		  << "[0," << _size << "]\n";
		throw std::out_of_range(s.str());
	}

	single_list_node<T>* current = firstNode;
	for (size_type i = 0; i < index; i++)
	{
		current = current->next;
	}
	return current->_element;
}

template <typename T>
inline T& single_list<T>::operator[](size_type index) const
{
	single_list_node<T>* current = firstNode;
	for (size_type i = 0; i < index; i++)
	{
		current = current->next;
	}
	return current->_element;
}

template <typename T> inline void single_list<T>::push_back(const T& element)
{
	if (_size == 0)
	{
		firstNode = lastNode = new single_list_node<T>(element);
		_size++;
		return;
	}
	lastNode->next = new single_list_node<T>(element);
	_size++;
	lastNode = lastNode->next;
}

template <typename T>
typename single_list<T>::size_type single_list<T>::find(const T& element) const
{
	//如果没有找到返回链表长度
	//空列表
	if (_size == 0)
		return 1;
	single_list_node<T>* cur = firstNode;
	size_type result;
	for (result = 0; result < _size && cur->_element != element;
		 result++, cur = cur->next)
		;
	return result;
}

template <typename T>
void single_list<T>::insert(size_type index, const T& element)
{
	if (index < 0 || index > _size)
	{
		std::ostringstream os;
		os << "insert index: " << index << " must in range: "
		   << "[0," << _size << "]\n";
		throw std::out_of_range(os.str());
	}
	if (index == 0)
	{
		if (firstNode == nullptr)
		{
			firstNode = new single_list_node<T>(element);
			lastNode = firstNode;
		}
		else
		{
			auto temp = new single_list_node<T>(element, firstNode);
			firstNode = temp;
		}
		_size++;
		return;
	}
	single_list_node<T>* cur = firstNode;
	for (size_type i = 0; i < index - 1; i++)
		cur = cur->next; //在前一位停下
	cur->next = new single_list_node<T>(element, cur->next);
	//在尾部插入需要重设lastNode
	if (index == _size)
		lastNode = cur->next;
	_size++;
}

template <typename T>
void single_list<T>::set(size_type index, const T& element)
{
	if (index < 0 || index >= _size)
	{
		std::ostringstream s;
		s << "set index: " << index << " must in range: "
		  << "[0," << _size << "]\n";
		throw std::out_of_range(s.str());
	}

	single_list_node<T>* cur = firstNode;
	for (size_type i = 0; i < index; i++)
		cur = cur->next;
	cur->_element = element;
}

template <typename T> void single_list<T>::erase(size_type index)
{
	if (index < 0 || index >= _size)
	{
		std::ostringstream s;
		s << "erase index: " << index << " must in range: "
		  << "[0," << _size << "]\n";
		throw std::out_of_range(s.str());
	}
	if (index == 0)
	{
		if (_size == 1)
		{
			delete firstNode;
			firstNode = lastNode = nullptr;
		}
		else
		{
			auto temp = firstNode->next;
			delete firstNode;
			firstNode = temp;
		}
		_size--;
		return;
	}
	single_list_node<T>* cur = firstNode;
	//在前一位停下
	for (size_type i = 0; i < index - 1; i++)
		cur = cur->next;
	single_list_node<T>* dNode = cur->next;
	if (dNode->next == nullptr) //删除的是最后一位
	{
		delete dNode;
		_size--;
		lastNode = cur;
	}
	else
	{
		cur->next = dNode->next;
		delete dNode;
		_size--;
	}
}

template <typename T>
void single_list<T>::remove(size_type fromIndex, size_type toIndex)
{
	// toIndex范围是[1,_size]
	// fromIndex范围是[0,_size-1]
	//删除的范围是[fromIndex,toIndex)
	//如想删除第一个或最后一个元素，需用formIndex和toIndex夹住
	// fromIndex如果等于toIndex, 会抛出invalid_argument异常
	if (fromIndex >= toIndex)
	{
		std::ostringstream s;
		s << "from index: " << fromIndex << "must <= to index: " << toIndex
		  << '\n';
		throw std::invalid_argument(s.str());
	}
	if (fromIndex < 0 || toIndex > _size)
	{
		std::ostringstream s;
		s << "remove out of range [0," << _size << "]\n";
		throw std::out_of_range(s.str());
	}

	single_list_node<T>* cur = firstNode;
	if (fromIndex == 0)
	{
		if (_size == 1) //之前的异常已经检查，_size=1时只能是删除一个元素
		{
			delete firstNode;
			firstNode = lastNode = nullptr;
			_size--;
		}
		else
		{
			single_list_node<T>* nextNode;
			cur = firstNode;
			//在前一位停下，防止toIndex是超尾元素
			for (size_type i = 0; i < toIndex - 1; i++)
			{
				nextNode = cur->next;
				delete cur;
				_size--;
				cur = nextNode;
			}
			// toIndex是超尾
			if (cur->next == nullptr)
			{
				delete cur;
				_size--;
				assert(_size == 0);
				firstNode = lastNode = nullptr;
			}
			else //正常情况
			{
				firstNode = cur->next;
				delete cur;
				_size--;
			}
		}
		return;
	}

	//在fromIndex前一位停下
	size_type i;
	for (i = 0; i < fromIndex - 1; i++)
		cur = cur->next;
	single_list_node<T>* nodeNext = cur;
	//在toIndex前一位停下
	single_list_node<T>* nextNode;
	//手动拨到下一位进行删除
	i++;
	cur = cur->next;
	for (; i < toIndex - 1; i++)
	{
		nextNode = cur->next;
		delete cur;
		_size--;
		cur = nextNode;
	}
	// toIndex是超尾
	if (cur->next == nullptr)
	{
		delete cur;
		_size--;
		lastNode = nodeNext;
		lastNode->next = nullptr;
	}
	else
	{
		nextNode = cur->next;
		delete cur;
		_size--;
		nodeNext->next = nextNode;
	}
}

template <typename T> void single_list<T>::clear()
{
	single_list_node<T>* cur = firstNode;
	single_list_node<T>* temp;
	while (cur != nullptr)
	{
		temp = cur->next;
		delete cur;
		_size--;
		cur = temp;
	}
	assert(_size == 0);
	firstNode = lastNode = nullptr;
}

} // namespace myds
#endif