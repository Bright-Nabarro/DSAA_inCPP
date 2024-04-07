#include <iostream>
#include <utility>
using namespace std;

template<typename Ty>
struct Node
{
	Ty element;
	Node* next;
	Node(const Ty& e, Node* n = nullptr): element {e}, next {n} {}
};

template<typename Ty>
Node<Ty>* head{nullptr};

template<typename Ty>
void push_head(const Ty& x)
{
	Node<Ty>* newNode { new Node{x, head<Ty> } };
	head<Ty> = newNode;
}

template<typename Ty>
void free_head()
{
	if(head<Ty> == nullptr)
		return;

	auto* tmp = head<Ty>;
	head<Ty> = head<Ty>->next;
	delete tmp;
}

template<typename Ty>
void free_all()
{
	auto* p = head<Ty>;
	while(p != nullptr)
	{
		auto* tmp = p;
		p = p->next;
		delete tmp;
	}
}

template<typename NodeType>
bool check_cycle(NodeType* head)
{
	NodeType* fast, *slow;
	fast = slow = head;
	while(true)
	{
		if(fast == nullptr || fast->next == nullptr)
		{
			return false;
		}
		fast = fast->next->next;
		slow = slow->next;
		if(fast == slow)
			return true;
	}
}

int main()
{
	for(int i = 0; i < 10; i++)
		push_head(i);
	Node<int>* p1;
	for(p1 = head<int>; p1->next != nullptr; p1 = p1->next);

	p1->next = head<int>;

	cout << boolalpha << check_cycle(head<int>) << endl;

	for(long i = 0; i < 10; i++)
		push_head<long>(i);
	Node<long>* p2;
	for(p2 = head<long>; p2->next != nullptr; p2 = p2->next);
	cout << boolalpha << check_cycle(head<long>) << endl;
}