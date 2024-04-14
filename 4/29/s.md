# a
The initial splay have N elements.
Proof by induction.

```
### basic case
First we access the smallest element from the initial trees. Then the smallest element become root is an empty left subtree(left subtree must smaller than smallest element). Obviously, single node is a chain.

### induction steps
Assume we perform k access with order, then the left subtree of root formed a single list from kth element to first element. Then we perform `k+1`th access, the `k+1`th element is located in right subtree of root. We use zigzig, zigzag or single rotation to upper this element. Whatever it is, the root's left subtree is always left subtree. So when `k+1`th elements becomes root, its left subtree doesnot change. Maintain a linked list from biggest to smallest.
```

### Base Case
Initially, we access the smallest element in the Splay tree. This results in the smallest element becoming the root, with an empty left subtree (since anything in the left subtree would have to be smaller than the smallest element), making it evident that a single node consitutes a chain.

### Iduction Steps
Let's assume that after performing k ordered accesses, the left subtree of the root forms a single chain from the kth element to the first. Next, we proceed with the `k+1`th element resides in the right subree of th root. Through a series of rotations --be it zig-zig, zig-zag, or a single rotation-- to elevate this element, the left subtree of the rootremains unchanged.
Consequently, when the `k+1`th element ascends to become the new root, its left subtree is preserved as is, thereby maintaining a linkedlist ordered from the largest to the smallest element.