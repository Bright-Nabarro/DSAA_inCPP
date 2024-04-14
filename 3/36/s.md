ptr is a pointer to a singly linked list's node

to remove ptr node
move ptr->next->element to ptr->element, and make ptr = ptr->next->next