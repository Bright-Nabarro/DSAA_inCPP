#include <iostream>
using namespace std;

template<typename Ty>
Ty e{0};

template<typename Ty>
struct Node
{
	Ty element;
	Node* left;
	Node* right;

	Node(const Ty& e, Node* l = nullptr, Node* r = nullptr)
	: element{e}, left{l}, right{r}{}
	Node(Ty&& e, Node* l = nullptr, Node* r = nullptr)
	: element{std::move(e)}, left{l}, right{r}{}
};

template<typename Ty>
Node<Ty>* gen_full_tree(int h)
{
	if(h == 1)
		return new Node{e<Ty>++};
	
	return new Node{e<Ty>++, gen_full_tree<Ty>(h-1), gen_full_tree<Ty>(h-1)};
}

template<typename Ty>
void print_tree(Node<Ty>* p, ostream& os)
{
	size_t counter{0};
	os << "-------------\n"
	   << "digraph tree{\n";
	print_node(p, os, counter);
	for(size_t i = 0; i < counter; i++)
	{
		os << "NULL" << i << "[lable=\"\"]\n";
	}
	os << "}\n"
	   << "-------------\n";
}

template<typename Ty>
void print_node(Node<Ty>* p, ostream& os, size_t& counter)
{
	if(p == nullptr)
		return;
	if(p->left != nullptr)
		cout << p->element << " -> " << p->left->element << '\n';
	else
		cout << p->element << " -> NULL" << counter++ << '\n';

	if(p->right != nullptr)
		cout << p->element << " -> " << p->right->element << '\n';
	else
		cout << p->element << " -> NULL" << counter++ << '\n';
	print_node(p->left, os, counter);
	print_node(p->right, os, counter);
}

int main()
{
	int h;
	cin >> h;
	auto* r1 = gen_full_tree<long>(h);
	print_tree(r1, cout);
}