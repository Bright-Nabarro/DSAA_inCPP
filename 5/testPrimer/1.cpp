#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int x)
{
	int sq = sqrt(x);
	if (x == 1)
		return false;
	if (x == 2)
		return true;
	for(int i {2}; i <= sq; ++i)
	{
		if(x % i == 0)
			return false;
	}
	return true;
}

int main()
{
	int x;
	while(cin >> x)
		if(isPrime(x))
			cout << "yes" << endl;
		else
			cout << "no" << endl;
}
