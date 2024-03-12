#pragma once
#include <cstddef>  //for size_t
#include <memory>
#include <utility>
#include <cassert>

template<typename T>
class Deque
{
public:
    explicit Deque(size_t size = ms_kInitial_size);
    //using synthesized function
    virtual ~Deque() = default;
    //front
    void push(T x);
    void pop() { ++m_front; }
    const T& front() const;
    T& front();
    //rear
    void inject(T x);
    void eject() { --m_back; }
    const T& back() const;
    T& back();
    //gernal
    size_t size() const { 
        assert(m_back >= m_front);
        return m_back - m_front; 
    }
private:
    inline static const size_t ms_kInitial_size {10};
    std::unique_ptr<T[]> m_lists { nullptr };
    //half open range
    T* m_front;
    T* m_back;
    size_t m_capSize;
private:
    T* lists_front() { return m_lists.get(); }
    T* lists_back()  { return m_lists.get() + m_capSize;}
    bool is_full();
    void resize_alloc();
};

template<typename T>
Deque<T>::Deque(size_t size): m_capSize { size }
{
    m_lists = std::make_unique<T[]>(m_capSize);
    m_front = m_back = m_lists.get() + m_capSize/2;
}

template<typename T>
void Deque<T>::push(T x)
{
    *--m_front = std::move(x);
    if(is_full())
        resize_alloc();
}

template<typename T>
const T& Deque<T>::front() const
{
    return *m_front;
}

template<typename T>
T& Deque<T>::front()
{
    return const_cast<T&>(std::as_const(*this).front());
}

template<typename T>
void Deque<T>::inject(T x)
{
    *m_back++ = std::move(x);
    if(is_full())
        resize_alloc();
}

template<typename T>
const T& Deque<T>::back() const
{
    return *(m_back-1);
}

template<typename T>
T& Deque<T>::back()
{
    return const_cast<T&>(std::as_const(*this).back());
}

template<typename T>
bool Deque<T>::is_full()
{
    //two size of capacity left
    if(m_front == lists_front() || m_back == lists_back())
        return true;
    return false;
}

template<typename T>
void Deque<T>::resize_alloc()
{
    auto newCapSize = m_capSize*2;
    auto newLists = std::make_unique<T[]>(newCapSize);
    auto theSize = size();
    auto frontBias = newCapSize/2 - theSize;
    assert(frontBias > 0);
    auto ptr {m_front};
    auto idx {frontBias};
    for(; ptr != m_back; ++ptr, ++idx)
    {
        newLists[idx] = std::move(*ptr);
    }

    m_capSize = newCapSize;
    m_lists = std::move(newLists);
    m_front = m_lists.get()+frontBias;
    m_back = m_lists.get()+frontBias+theSize;
}