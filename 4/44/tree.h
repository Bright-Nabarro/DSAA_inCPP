#include <utility>
#include <iostream>

template<typename Ty>
class Tree
{
public:
	struct Node
	{
		Ty element;
		Node* sibling;
		Node* child;
		Node(const Ty& e, Node* s = nullptr, Node* c = nullptr): 
			element{e}, sibling{s}, child{c}{}
		Node(Ty&& e, Node* s = nullptr, Node* c = nullptr):
			element{std::move(e)}, sibling{s}, child{c}{}
	};
public:
	Tree(Ty e): root{new Node{std::move(e)}}{}
	Tree(const Tree&) = delete;
	Tree& operator=(const Tree&) = delete;
	Tree(Tree&&) = default;
	Tree& operator=(Tree&&) = default;
	~Tree()
	{
		clean(root);
	}
public:
	template<typename Ty_ref>
	Node* insert_nextLevel(Ty_ref&& x, Node* itr)
	{
		auto* ptr = itr;	
		if(ptr->child != nullptr)
		{
			return insert_sibling(std::forward<Ty>(x), ptr->child);
		}
		ptr->child = new Node{std::forward<Ty>(x)};
		return ptr->child;
	}
	template<typename Ty_ref>
	Node* insert_sibling(Ty_ref&& x, Node* itr)
	{
		auto* ptr = itr;
		for(; ptr->sibling != nullptr; ptr = ptr->sibling);
		ptr->sibling = new Node{std::forward<Ty>(x)};
		return ptr->sibling;
	}
	void print_tree(std::ostream& os)
	{
		if(root != nullptr)
			print_tree(root, os);
	}
	Node* get_root()
	{
		return root;
	}
private:
	void print_tree(Node* ptr, std::ostream& os)
	{
		for(auto* p = ptr; p != nullptr; p = p->sibling)
		{
			os << p->element << ' ';
		}
		os << '\n';
		for(auto* p = ptr; p != nullptr; p = p->sibling)
		{
			if(p->child != nullptr)
			{
				os << "[" << p->element << "]\t";
				print_tree(p->child, os);
			}
		}
	}
	void clean(Node* ptr) noexcept
	{
		if(ptr == nullptr)
			return;
		
		while(ptr != nullptr)
		{
			if(ptr->child != nullptr)
				clean(ptr->child);
			auto* temp = ptr->sibling;
			delete ptr;
			ptr = temp;
		}
	}
private:
	Node* root;
};