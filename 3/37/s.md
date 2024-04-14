The approach is same as 3.36
Boundary conditions were not fully considered

# a

```cpp
auto* pNext = p->next;
auto* pNode = new {Node{p->element, pNext}}
std::move(p->element, x)    //now p is the previous node
p->next = pNode
```

# b
```cpp
if(p->next == nullptr)
{
    delete p;
    return;
}
std::move(p->element, p->next->element);
auto* pNext = p->next->next;
delete p->next;
p->next = pNext;
```