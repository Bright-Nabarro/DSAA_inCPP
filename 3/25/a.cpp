#include <iostream>
#include "min_stack.h"

using namespace std;

int main()
{
	MinStack<int> mStk1;
	for(int x: {5, 4, 7, 9, 4, 3, 2, 1, 1, 8, 0})
	{
		mStk1.push(x);
		cout << x << " ";
	}
	cout << endl;

	while(!mStk1.empty())
	{
		cout << mStk1.find_min() << " ";
		mStk1.pop();
	}
	cout << endl;
}
