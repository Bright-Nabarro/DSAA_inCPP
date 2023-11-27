#pragma once
#include <stack>
#include <cassert>

template<typename T>
class MinStack
{
public:
	T& top() { return m_mainStack.top(); }
	const T& top() const { return m_mainStack.top(); }
	void push(const T& element)
	{
		m_mainStack.push(element);
		if(m_min.empty() || element <= m_min.top())
			m_min.push(element);
	}
	void pop()
	{
		assert(m_min.top() <= m_mainStack.top());
		if(m_mainStack.top() == m_min.top())
			m_min.pop();
		m_mainStack.pop();
	}
	size_t size() { return m_mainStack.size(); }
	bool empty() { return m_mainStack.empty(); }
public:
	T& find_min() { return m_min.top(); }
	const T& find_min() const { return m_min.top(); }
private:
	std::stack<T> m_mainStack;
	std::stack<T> m_min;
};
