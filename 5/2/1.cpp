#include <iostream>
#include <array>
using namespace std;
int main()
{
	array a = {4371, 1323, 6173, 4199, 4344, 9679, 1989};
	for(auto x: a)
		cout << x << '\t' << x % 19 << endl;
}
