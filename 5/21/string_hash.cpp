#include <cassert>
#include <stdexcept>
#include "string_hash.h"
#include "next_prime.h"
using namespace std;


StrHashTable::StrHashTable() :
	StrHashTable(sk_initialTableSize)
{
}

StrHashTable::StrHashTable(size_t initialTableSize) :
	m_table(next_prime(initialTableSize))
{
}

bool StrHashTable::HashEntry::activity() const
{
	if(m_condition == ACTIVE)
		return true;
	return false;
}

bool StrHashTable::contains(const string& str) const
{
	auto ret {find_pos(str)};
	if(ret.first != ACTIVE || hashFail)
		return false;
	assert(m_table[ret.second].m_str == str);
	return true;
}

void StrHashTable::clear()
{
	m_table.clear();
	m_table.resize(sk_initialTableSize);
	m_size = 0;
	hashFail = false;
}

bool StrHashTable::insert(const string& str)
{
	auto ret { find_pos(str) };

	if(check_rehash())
		ret = find_pos(str);

	if(ret.first == ACTIVE)
		return false;

	m_table[ret.second] = {str, ACTIVE};
	m_size++;
	return true;
}

bool StrHashTable::remove(const string& str)
{
	check_rehash();
	auto ret { find_pos(str) };
	if(ret.first != ACTIVE)
		return false;
	
	m_table[ret.second].m_condition = DELETED;
	m_size--;
	return true;
}


size_t StrHashTable::string_hash(const std::string& str) const
{
	size_t hashVal {0};
	for(char ch : str)
	{
		hashVal = 37 * hashVal + ch;
	}
	return hashVal;
}

bool StrHashTable::check_rehash()
{
	bool ret { false };
#ifndef NODEBUG
	size_t rehashFailCounter{0};
#endif
	while(hashFail)
	{
#ifndef NODEBUG
		rehashFailCounter++;
		if(rehashFailCounter > 2)
		{
			throw logic_error{"consequence rehash >= 2"};
		}
#endif
		rehash();
		ret = true;
	}

	if(static_cast<double>(m_size) / m_table.size() > 0.5)
	{
		rehash();
		ret = true;
	}
	return ret;
}

void StrHashTable::rehash()
{
	StrHashTable newTable {m_table.size() * 2};
	for(auto x: m_table)
	{
		if(x.activity())
			newTable.insert(x.m_str);
	}
	*this = std::move(newTable);
}

auto StrHashTable::find_pos(const string& str) const -> pair<Entry, size_t>
{
	if(hashFail)
		return {EMPTY, 0};

	size_t pos{ string_hash(str) % m_table.size() };
	const size_t markPos {pos};
	size_t bais{1};
	while(true)
	{
		if(m_table[pos].activity() && m_table[pos].m_str == str)
			return {m_table[pos].m_condition, pos};
		if(m_table[pos].m_condition == EMPTY)
			return {m_table[pos].m_condition, pos};
		pos += bais;
		bais += 2;
		pos %= m_table.size();
		if(pos == markPos)
		{
			hashFail = true;
			return {EMPTY, 0};
		}
	}
}
