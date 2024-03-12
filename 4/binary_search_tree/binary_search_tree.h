#pragma once
#include <cstddef>  //for size_t
#include <iostream>
#include <memory>
#include <utility>
#include <cassert>
#include <format>

// use < and == compare
template<typename T>
class BinarySearchTree
{
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& rhs);
    BinarySearchTree& operator=(const BinarySearchTree& rhs);
    BinarySearchTree(BinarySearchTree&& rhs) noexcept;
    BinarySearchTree& operator=(BinarySearchTree&& rhs) noexcept;
    virtual ~BinarySearchTree() = default;
    void swap(BinarySearchTree& rhs) noexcept;

    size_t size() const;
    const T& find_min() const;
    const T& find_max() const;
    bool contains (const T& x) const;
    bool is_empty() const;
    //use DOT language
    void print_tree(std::ostream& out) const;

    void make_empty();
    bool insert(const T& x);
    bool insert(T&& x);
    bool remove(const T& x);

private:
    struct BinaryNode;
    using uptr = std::unique_ptr<BinaryNode>;
    
private:
    T& find(bool isLeft) const;
    bool contains(const T& x, const uptr& ptr);
    void print_tree(std::ostream& out, const uptr& ptr) const;
    void print_nodes(std::ostream& out, 
                     const uptr& ptr, const uptr& next) const;

    uptr& clone(const uptr& rhsp);
    void make_empty(uptr& ptr);
    bool insert(const T& x, uptr& ptr);
    bool insert(T&& x, uptr& ptr);
    bool remove(const T& x, uptr& ptr);
    
private:
    uptr root;
    size_t currentSize;
};

template<typename T>
void swap(BinarySearchTree<T>& lhs, BinarySearchTree<T>& rhs) noexcept
{
    lhs.swap(rhs);
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree() :
    root {nullptr}, currentSize{0}
{}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& rhs) :
    root {nullptr}, currentSize{rhs.currentSize}
{
    root = clone(rhs.root);
}

template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree& rhs)
{
    auto copy {rhs};
    swap(copy);
    return *this;
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree&& rhs) noexcept
{
    root = std::exchange(rhs.root, nullptr);
    currentSize = std::exchange(rhs.currentSize, 0);
}

template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=
                    (BinarySearchTree&& rhs) noexcept
{
    this->swap(rhs);
    return *this;
}

template<typename T>
void BinarySearchTree<T>::swap(BinarySearchTree& rhs) noexcept
{
    std::swap(root, rhs.root);
    std::swap(currentSize, rhs.currentSize);
}

template<typename T>
size_t BinarySearchTree<T>::size() const
{
    return currentSize;
}

template<typename T>
const T& BinarySearchTree<T>::find_min() const
{
    return find(true);
}

template<typename T>
const T& BinarySearchTree<T>::find_max() const
{
    return find(false);
}

template<typename T>
bool BinarySearchTree<T>::contains(const T& x) const
{
    return contains(x, root);
}

template<typename T>
bool BinarySearchTree<T>::is_empty() const
{
    return root == nullptr;
}

template<typename T>
void BinarySearchTree<T>::print_tree(std::ostream& out) const
{
    out << "digraph G {\n";
    print_tree(out, root);
    out << "}\n";
}

template<typename T>
void BinarySearchTree<T>::make_empty()
{
    make_empty(root);
    assert(currentSize == 0);
}

template<typename T>
bool BinarySearchTree<T>::insert(const T& x)
{
    return insert(x, root);
}

template<typename T>
bool BinarySearchTree<T>::insert(T&& x)
{
    return insert(std::move(x), root);
}

template<typename T>
bool BinarySearchTree<T>::remove(const T& x)
{
    return remove(x, root);
}

template<typename T>
T& BinarySearchTree<T>::find(bool isLeft) const
{
    uptr& ptr {root};
    while(ptr != nullptr)
    {
        if(isLeft)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    return ptr->element;
}

template<typename T>
bool BinarySearchTree<T>::contains(const T& x, const uptr& ptr)
{
    if(ptr->element == x)
        return true;
    else
        return contains(x, ptr) || contains(x, ptr);
}

template<typename T>
void BinarySearchTree<T>::print_tree(std::ostream& out, const uptr& ptr) const
{
    if(ptr == nullptr)
        return;
    print_nodes(out, ptr, ptr->left);
    print_nodes(out, ptr, ptr->right);
    
    //recursive
    print_tree(out, ptr->left);
    print_tree(out, ptr->right);
}

template<typename T>
void BinarySearchTree<T>::print_nodes(std::ostream& out, 
                                      const uptr& ptr, const uptr& next) const
{
    if(ptr != nullptr)
        out << std::format("{} -> {};\n", ptr->element, next->element);
    else
        out << std::format("{} -> {};\n", ptr->element, "null");
}

template<typename T>
auto BinarySearchTree<T>::clone(const uptr& rhsp) -> uptr&
{
    if(rhsp == nullptr)
        return nullptr;
    else
        return std::make_unique<BinaryNode>
                    (rhsp->element, clone(rhsp->left), clone(rhsp->right));
}

template<typename T>
void BinarySearchTree<T>::make_empty(uptr& ptr)
{
    if(ptr == nullptr)
        return;
    make_empty(ptr->left);
    make_empty(ptr->right);
    ptr.reset();
    --currentSize;
}

template<typename T>
bool BinarySearchTree<T>::insert(const T& x, uptr& ptr)
{
    if(ptr == nullptr)
    {
        ptr = make_unique(x, nullptr, nullptr);
        return true;
    }
    
    if(ptr->element < x)
        return insert(x, ptr->left);
    else if(x < ptr->element)
        return insert(x, ptr->right);
    else
    {
        assert(x == ptr->element);
        return false;
    }
}

template<typename T>
bool BinarySearchTree<T>::insert(T&& x, uptr& ptr)
{
    if(ptr == nullptr)
    {
        ptr = std::make_unique<BinaryNode>(std::move(x), nullptr, nullptr);
        ++currentSize;
        return true;
    }
    
    if(ptr->element < x)
        return insert(std::move(x), ptr->left);
    else if(x < ptr->element)
        return insert(std::move(x), ptr->right);
    else
    {
        assert(x == ptr->element);
        return false;
    }
}

template<typename T>
bool BinarySearchTree<T>::remove(const T& x, uptr& ptr)
{
    if(ptr == nullptr)
        return false;

    if(x < ptr.element)
    {
        return remove(x, ptr->left);
    }
    else if(ptr.element < x)
    {
        return remove(x, ptr->right);
    }
    else
    {
        ptr.reset();
        --currentSize;
        return true;
    }
}

template<typename T>
struct BinarySearchTree<T>::BinaryNode
{
        T element;
        uptr left;
        uptr right;
        BinaryNode(const T& theElement, uptr theLeft = nullptr,
                   uptr theRight = nullptr);
        BinaryNode(T&& theElement, std::unique_ptr<BinaryNode> theLeft = nullptr,
                   std::unique_ptr<BinaryNode> theRight = nullptr);
};

template<typename T>
BinarySearchTree<T>::BinaryNode::BinaryNode
(const T& theElement, std::unique_ptr<BinaryNode> theLeft,
                   std::unique_ptr<BinaryNode> theRight) :
    element{theElement}, left{std::move(theLeft)}, right{std::move(theRight)}
{}

template<typename T>
BinarySearchTree<T>::BinaryNode::BinaryNode
(T&& theElement, std::unique_ptr<BinaryNode> theLeft,
                   std::unique_ptr<BinaryNode> theRight) :
    element{std::move(theElement)}, left{std::move(theLeft)}, right{std::move(theRight)}
{}
