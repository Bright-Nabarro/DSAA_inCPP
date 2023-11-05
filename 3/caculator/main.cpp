#include "caculator.h"

int main()
{
	while (true)
		try
		{
			std::string expr;
			std::getline(std::cin, expr);
			double result = Caculator::exec(expr);
			std::cout << result << std::endl;
		}
		catch (std::invalid_argument& e)
		{
			std::cout << e.what() << std::endl;
			getchar();
		}
}