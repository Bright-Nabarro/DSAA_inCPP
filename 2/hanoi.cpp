#include <iostream>
#include <string>

void hanoi(int n, std::string source_peg, std::string target_peg,
		   std::string aux_peg)
{
	if (n == 0)
		return;
	hanoi(n - 1, source_peg, aux_peg, target_peg);
	//由于结果是输出, 函数调用过程的本身相当于对其进行操作
	std::cout << "Move disk " << n << " from peg " << source_peg << " to peg "
			  << target_peg << "\n";
	hanoi(n - 1, aux_peg, target_peg, source_peg);
}

int main()
{
	hanoi(3, "A", "B", "C");
	return 0;
}