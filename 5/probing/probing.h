#include <cstddef>
#include <functional>
#include <vector>
#include <limits>
#include <utility>
#include "next_prime.h"

template<typename Ty>
class Probing
{
public:
    explicit Probing(
			size_t size = 101,
			//the function provide must add x position itself
			std::function<size_t(size_t)> func
			= [](size_t x){ return x+1; }
			);
	virtual ~Probing() = default;
    bool contains(const Ty& x) const;
    void make_empty();
    bool insert(Ty x);
    bool remove(const Ty& x);
	bool is_empty() const;
	size_t size() const;
private:
    enum Entry { ACTIVE, EMPTY, DELETED };
    struct HashEntry
    {
        Ty m_value;
        Entry m_condition;
		HashEntry(): m_condition(EMPTY){}
		HashEntry(const Ty value, Entry condition):
			m_value {std::move(value)}, m_condition {condition}{}
    };
private:
	void rehash();
	size_t myhash(const Ty& x) const;
	//donot update m_currentSize
	bool internal_insert(Ty x);
	//the first element equals to contains logic
	//if the searched
	std::pair<bool, size_t> find_pos(const Ty& x) const;	

	std::vector<HashEntry> m_table;
	size_t m_currentSize {0};
	std::function<size_t(size_t)> m_probingFunc;
	mutable bool m_hashFaild {false};
};

template<typename Ty>
Probing<Ty>::Probing(size_t size,
		std::function<size_t(size_t)> func)
	: m_table(next_prime(size))
{
	m_probingFunc = [&func, this](size_t x)
		{
			size_t result = func(x);
			if(result >= m_table.size())
			{
				result -= m_table.size();
			}
			return result;
		};
}

template<typename Ty>
bool Probing<Ty>::contains(const Ty& x) const
{
	return find_pos(x).first;
}

template<typename Ty>
void Probing<Ty>::make_empty()
{
	size_t tableSize {m_table.size()};
	std::vector<HashEntry> emptyTable (tableSize);
	swap(emptyTable, m_table);
}

template<typename Ty>
bool Probing<Ty>::insert(Ty x)
{
	if(internal_insert(std::move(x)))
	{
		++m_currentSize;
		return true;
	}
	else
		return false;
}

template<typename Ty>
bool Probing<Ty>::is_empty() const
{
	return m_currentSize==0;
}

template<typename Ty>
size_t Probing<Ty>::size() const
{
	return m_currentSize;
}

template<typename Ty>
bool Probing<Ty>::remove(const Ty& x)
{
	auto pos = find_pos(x);
	if(pos.first)
	{
		m_table[pos.second].m_condition = DELETED;
		--m_currentSize;
		return true;
	}
	return false;
}

template<typename Ty>
void Probing<Ty>::rehash()
{
	m_hashFaild = false;
	size_t newSize {next_prime(m_table.size()*2)};
	auto oldTable = std::move(m_table);
	make_empty();
	m_table.resize(newSize);
	for(auto& entry: oldTable)
	{
		if(entry.m_condition == ACTIVE)
			internal_insert(entry.m_value);
	}
}

template<typename Ty>
size_t Probing<Ty>::myhash(const Ty& x) const
{
	static std::hash<Ty> hf;
	return hf(x) % m_table.size();
}

template<typename Ty>
bool Probing<Ty>::internal_insert(Ty x)
{
	auto pos = find_pos(x);
	if(m_hashFaild)
	{
		rehash();
		pos = find_pos(x);
	}
	if(!pos.first)
	{
		m_table[pos.second].m_value = std::move(x);
		m_table[pos.second].m_condition = ACTIVE;
		if(m_currentSize > m_table.size()/2)
        {
			rehash();
        }
		return true;
	}
	return false;
}

template<typename Ty>
std::pair<bool, size_t> Probing<Ty>::find_pos(const Ty& x) const
{
	//need return contains problem as the first result
	size_t pos, posI;
	pos = myhash(x);
	if(m_table[pos].m_condition == EMPTY)
		return {false, pos};
	if(m_table[pos].m_condition == ACTIVE 
		&& m_table[pos].m_value == x)
	{
		return {true, pos};
	}
	size_t hashCollisionFactor { m_table.size()/4 };
	size_t collision {0};
	for( posI = m_probingFunc(pos);
		m_table[posI].m_condition != EMPTY;
		posI = m_probingFunc(posI), ++collision)
	{
		if(m_table[posI].m_condition == ACTIVE 
			&& m_table[posI].m_value == x)
		{
			return {true, posI};
		}
		//hash failed
		if(posI == pos || collision > hashCollisionFactor)
		{
			m_hashFaild = true;
			break;
		}
	}
	return {false, posI};
}
