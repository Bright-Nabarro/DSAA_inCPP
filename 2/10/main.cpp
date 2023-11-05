#include "../../test_alg.h"
#include "add.h"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <ostream>

class test_add
{
  private:
	using func = string (*)(string, string);
	func alg;

  public:
	test_add(func alg) : alg(alg) {}
	void operator()()
	{
		int num1 = rand() % 1000000;
		int num2 = rand() % 1000000;
		int sum = num1 + num2;
		string string_sum =
			add_list_imp(std::to_string(num1), std::to_string(num2));
		if (string_sum != std::to_string(sum))
		{
			std::cout << "sum: " << (sum) << std::endl
					  << "string sum: " << string_sum << std::endl;
			throw "error";
		}
	}
};

int main()
{
	srand(time(0));
	int amount = 100000000;
	using alg_func = void();
	test_add list_alg(add_list_imp);
	std::cout << test_single<alg_func>(list_alg, amount) << std::endl;
	test_add default_alg(add_string_imp);
	;
	std::cout << test_single<alg_func>(default_alg, amount) << std::endl;
}
