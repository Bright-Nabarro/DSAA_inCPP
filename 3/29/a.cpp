template<typename T>
class Lists
{
    //...
    void reverse()
    {
        if(front == nullptr || front->next == nullptr)
            return;

        Node* current, prev;
        prev = nullptr;
        current = front;
        while(current != nullptr)
        {
            auto nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }
        front = prev;
    }
private:
    class Node
    {
        T ele;
        Node* next;
    };
    Node* front;
};