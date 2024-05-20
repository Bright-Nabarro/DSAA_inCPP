#pragma once
#include <vector>
#include <fstream>
#include "string_hash.h"

class spellChecker
{
	public:
	//RAII
	spellChecker() = default;
	spellChecker(const spellChecker& rhs) = delete;
	spellChecker& operator=(const spellChecker& rhs) = delete;
	spellChecker(spellChecker&& rhs) = default;
	spellChecker& operator=(spellChecker&& rhs) = default;
	virtual ~spellChecker() = default;

public:
	spellChecker(std::ifstream& in);

	struct ErrorWords;
	std::vector<ErrorWords> addDictionary(std::ifstream& in);
	
private:
	std::vector<StrHashTable> dirTable;
};