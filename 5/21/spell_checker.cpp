#include <string>
#include "spell_checker.h"
using namespace std;

struct spellChecker::ErrorWords
{
	size_t line;
	size_t col;
	string word;
};