#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

class puzzle
{
  private:
	std::vector<std::string> words;

  public:
	puzzle(std::initializer_list<std::string>);
	void display(std::ostream = std::cout);
};

puzzle::puzzle(std::initializer_list<std::string> ini_strs)
	: words(ini_strs.size())
{
	auto p_words = words.begin();
	auto p_ini_strs = ini_strs.begin();
	for (; p_ini_strs != ini_strs.end(); p_ini_strs++, p_words++)
	{
		*p_words = *p_ini_strs;
	}
}

bool func()