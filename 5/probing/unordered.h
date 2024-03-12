#include "probing.h"

namespace dsaa_stl
{

template<typename Ty>
class unordered_set
{
public:
    unordered_set();
    bool insert(Ty value);
    bool erase(const Ty& value);
    bool find(const Ty& value);
    size_t size() const;
    bool empty() const;
private:
    Probing<Ty> m_hashTable;
};

}   //namespace dsaa_stl