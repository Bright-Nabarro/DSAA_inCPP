#include "polynomial.h"
using namespace std;

void test1()
{
	Polynomial f1("1 + x^2 + x");
	f1.display(cout);
	Polynomial f2("0 + 0x^0 + x");
	f2.display(cout);
	auto f3 = f1 * f2;
	f3.display(cout);

	Polynomial f4("1 + x");
	auto f5 = f4 * f4;
	f5.display(cout);
}

void test2()
{
}

int main()
{
	test1();
}