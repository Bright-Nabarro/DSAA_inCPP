```cpp
template<typename T>
struct AvlTree<T>::AvlNode
{
	T element;
	uptr left;
	uptr right;
	int height;

	AvlNode(const T& theElement, uptr&& theLeft = nullptr,
			   uptr&& theRight = nullptr, int h = 0);
	AvlNode(T&& theElement, uptr&& theLeft = nullptr,
			   uptr&& theRight = nullptr, int h = 0);
};
```

# a
`height` element is a int type data, stores 4 bytes, 32 bits.

# b
The max number of 8-bit int type is `0b0100'0000` -> 128.
In our implementation, the height of the bottom nodes is `0`. 
Therefore, if the height reaches 128, an insertion operation followed by a rebalancing could potentially increase the height to 129, resulting in an overflow. Consequently, an avl tree that would lead to this overflow scenario is a fully balanced tree with a height of 126, to which a node at depth 127 is appended. This configuration result in a total node count of $2^{126+1} = 1.7e38$.
Notice that the smallest avl tree will be smaller than this number. In other words, a tree with a height of 126 mat not be fully balanced but could still fortuitously accommodate the addition of a node at depth 127.