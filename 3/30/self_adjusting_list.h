#pragma once
#include <algorithm>
#include "deque.h"
//use 28 deque.h implamentation
//add seveal method in it

template<typename T>
class SelfAdjustingList
{
public:
    using iterator=T*;
    void insert(T x)
    {
        m_data.push(std::move(x));
    }
    iterator find(T x)
    {
        auto result = std::find(m_data.begin(), m_data.end(), x);       
        if(result == m_data.end())
            return result;
        m_data.erase(result);
        this->insert(std::move(x));
    }
private:
    Deque<T> m_data;
};