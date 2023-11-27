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
	for(int i = 0; i < 5; i++)
		stk.pushL(i);
	for(int i = 10; i < 15; i++)
		stk.pushR(i);
	cout << stk.sizeL() << " " << stk.topL() << endl;
	cout << stk.sizeR() << " " << stk.topR() << endl;
}
