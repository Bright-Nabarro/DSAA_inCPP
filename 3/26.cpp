#include <iostream>
using namespace std;

template<typename T, size_t theSize>
class ThreeStack
{
public:
	T& top1() {return *(m_top-1);}
	T& top2() {return *(m_midTop-1);}
	T& top3() {return *(m_bottom-1);}
	const T& top1() const {return *(m_top-1);}
	const T& top2() const {return *(m_midTop-1);}
	const T& top3() const {return *(m_bottom-1);}
	void pop1() {m_top--;}
	void pop2() {m_midTop--;}
	void pop3() {m_bottom++;}
	bool push1(const T& element)
	{
		if(m_top == m_midBottom)
			return adjust_push(m_top, element, true);
		*m_top++ = element;
		return true;
	}
	bool push2(const T& element)
	{
		if(m_midTop == m_bottom)
			return adjust_push(m_midTop, element, true);
		*m_midTop++ = element;
		return true;
	}
	bool push3(const T& element)
	{
		if(m_bottom == m_midTop)
			return adjust_push(m_bottom, element, false);
		*m_bottom-- = element;
		return true;
	}
	size_t size1() const { return m_top - m_array; }
	size_t size2() const { return m_midTop - m_midBottom; }
	size_t size3() const { return m_array + theSize - 1 - m_bottom; }
	bool empty1() const { return size1() == 0; }
	bool empty2() const { return size2() == 0; }
	bool empty3() const { return size3() == 0; }
private:
	bool adjust_push(T*& ptr, const T& element, bool isDown)
	{
		int bias = m_midTop + (m_midBottom - m_midTop)/2
		   	- m_top - (m_bottom-m_top)/2;
		T tempArr[m_midTop-m_midBottom];
		T* mid = m_midBottom;
		for(auto& x: tempArr)
			x = *mid++;

		m_midBottom -= bias;
		m_midTop -= bias;
		if(m_midBottom <= m_top || m_midTop >= m_bottom)
			return false;
		size_t i = 0;
		for(T* p = m_midBottom; p != m_midTop; p++)
			*p = tempArr[i++];
		if(isDown)
			*ptr++ = element;
		else
			*ptr-- = element;
		return true;
	}

	T m_array	[theSize];
	T* m_top	{m_array};
	T* m_bottom	{m_array+theSize-1};
	T* m_midTop {m_array+theSize/2};
	T* m_midBottom{m_midTop};
};

int main()
{
	ThreeStack<int, 15> stk;
	
	//int intArr[] = {1, 2, 3, 4, 5, 6, 7};
	stk.push1(1); 	//1
	stk.push1(2); 	//2
	stk.push1(3); 	//3
	stk.push1(4); 	//4
	stk.push1(5); 	//5
	stk.push2(21);	//6
	stk.push2(22);	//7
	stk.push2(23);	//8
	stk.push1(6); 	//9
	stk.push1(7); 	//10
	stk.push1(8); 	//11
	stk.push3(31);	//12
	stk.push3(32);	//13
	stk.push3(33);	//14
	if(stk.push3(34))
		cout << "false" << endl;
	if(stk.push3(35))
		cout << "true" << endl;
	cout << stk.top1() << endl;
}
