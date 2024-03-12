#pragma once
#include <functional>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <cstddef>

template<typename Ty>
class ChainingHashTable
{
public:
    explicit ChainingHashTable(size_t size = 101);
    bool contains(const Ty& x) const;

    void make_empty();
    bool insert(const Ty& x);
    bool remove(const Ty& x);
private:
    size_t myhash(const Ty& x) const;
    std::pair<size_t, typename std::list<Ty>::const_iterator> 
            search(const Ty& x) const;
    std::vector<std::list<Ty>> m_theLists;
    size_t m_currentSize;
};

template<typename Ty>
ChainingHashTable<Ty>::ChainingHashTable(size_t size):
    m_theLists(size), m_currentSize{0}
{}

template<typename Ty>
bool ChainingHashTable<Ty>::contains(const Ty& x) const
{
    auto ret { search(x) };
    if(ret.second == m_theLists[ret.first].cend())
        return false;
    return true;
}

template<typename Ty>
void ChainingHashTable<Ty>::make_empty()
{
    for(auto& x: m_theLists)
        x.clear();
}

template<typename Ty>
bool ChainingHashTable<Ty>::insert(const Ty& x)
{
    auto ret { search(x) };
    if(ret.second != m_theLists[ret.first].cend())
        return false;
    m_theLists[ret.first].insert(ret.second, x);
    return true;
}

template<typename Ty>
bool ChainingHashTable<Ty>::remove(const Ty& x)
{
    auto ret { search(x) };
    if(ret.second == m_theLists[ret.first].cend())
        return false;
    m_theLists[ret.first].erase(ret.second);
    return true;
}

template<typename Ty>
size_t ChainingHashTable<Ty>::myhash(const Ty& x) const
{
    static std::hash<Ty> hf;
    return hf(x) % m_theLists.size();
}

template<typename Ty>
std::pair<size_t, typename std::list<Ty>::const_iterator>
    ChainingHashTable<Ty>::search(const Ty& x) const
{
    size_t pos { myhash(x) };
    auto ptr = std::find(m_theLists[pos].cbegin(), m_theLists[pos].cend(), x);
    return {pos, ptr};
}
