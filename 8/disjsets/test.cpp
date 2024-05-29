#include <iostream>
#include <print>
#include "disjsets.hpp"
using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	disjsets dj(n+1);
	for(int i{0}; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		dj.union_sets(dj.find(a), dj.find(b));
	}
	dj.print();
	int q;
	cin >> q;
	for(int i{0}; i < q; i++)
	{
		int c, d;
		cin >> c >> d;
		if (dj.find(c) == dj.find(d))
			println("Yes");
		else
			println("No");
	}
}
