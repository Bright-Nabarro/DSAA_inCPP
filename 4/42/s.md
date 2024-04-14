Search of the appropriate leaf nodes and attempt to insert the key. If the number of keys in the leaf node reaches M, perform a split operation.

During the split operation, the median key is pushed up to its parent node and both resulting parent's node will have M/2 keys. If the parent node is also full, the splitting is done recursively, potentially continuing up to the root.