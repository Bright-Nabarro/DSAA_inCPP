#include <iostream>
#include <cctype>
using namespace std;

template<typename T, int size>
class arrayStack
{
private:
	T array[size];
	int lPos;
	int rPos;
public:
	arrayStack(): lPos{0}, rPos{size-1}{}
	//return false if array overflow
	bool pushL(const T& ele)
	{
		if(lPos > rPos)
			return false;
		array[lPos++] = ele;
		return true;
	}
	bool pushR(const T& ele)
	{
		if(rPos < lPos)
			return false;
		array[rPos--] = ele;
		return true;
	}
	const T& topL() const { return array[lPos-1]; }
	const T& topR() const { return array[rPos+1]; }
	void popL() { lPos--; }
	void popR() { rPos++; }
	int sizeL() { return lPos; }
	int sizeR() { return size-1 - rPos; }
	bool emptyL() { return sizeL() == 0; }
	bool emptyR() { return sizeR() == 0; }
};

int main()
{
	arrayStack<int, 10> stk;
	for(int i = 0; i < 11; i++)
	{
		if(!stk.pushL(i))
			cout << "overflow" << endl;
	}
	while(!stk.emptyL())
	{
		cout << stk.topL() << " ";
		stk.popL();
	}
	cout << endl;

	for(int i = 0; i < 11; i++)
	{
		if(!stk.pushR(i))
			cout << "overflow" << endl;
	}
	while(!stk.emptyR())
	{
		cout << stk.topR() << " ";
		stk.popR();
	}
}
