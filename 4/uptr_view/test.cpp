#include <cassert>
#include <iostream>
#include <memory>
#include "uptr_view.h"
using namespace std;

struct Node
{
	int element;
	unique_ptr<Node> next;
	Node(int theEle = 0, unique_ptr<Node>&& theNext = nullptr):
	element{theEle}, next{std::move(theNext)}{}
};

struct node
{
	int element;
	node* next;
	node(int e = 0, node* n = nullptr): element{e}, next{n}{};
};

void test_basic()
{
	uptr_view<int> uptrv1;
	assert(uptrv1 == nullptr);
	auto p1 { make_unique<int>(1) };
	uptrv1 = p1;
	assert(uptrv1 != nullptr);
	assert(*p1 == 1);
	assert(*(p1.get()) == 1);
	unique_ptr<int> p2{nullptr};
	uptr_view<int> uptrv2 {p2};
	assert(uptrv2 == nullptr);
}

void write_node()
{
	node* head = new node;
	for(int i = 1; i < 10; ++i)
	{
		node* temp = new node(i);
		temp->next = head;
		head = temp;
	}
	for(auto* p = head; p != nullptr; p=p->next)
	{
		cout << p->element << " ";
	}
	cout << endl;
}

void test_node()
{
	unique_ptr<Node> head { make_unique<Node>(0) };
	for(int i = 1; i <= 10; ++i)
	{
		auto temp { make_unique<Node>(i) };
		temp->next = std::move(head);
		head = std::move(temp);
	}
	for(uptr_view vp{head}; vp != nullptr; vp = vp->next)
	{
		cout << vp->element << " ";
	}
	cout << endl;
}

void test_release()
{
	auto p1 = make_unique<int>(1);
	uptr_view<int> pv { p1 };
	auto& p2 = pv.release();
	assert(p1 == p2);
	assert(pv == nullptr);
}

void test_assignment()
{
	uptr_view<int> pv {nullptr};
	auto p1 { make_unique<int>(1) };
	pv = p1;
	auto p2 { make_unique<int>(2) };
	pv = p2;

	uptr_view<int> pv2 {nullptr};
	assert(pv2 == nullptr);
	uptr_view<int> pv3 {pv2};
	assert(pv3 == nullptr);
}

template<typename Ty>
struct treeNode
{
	treeNode(){};
	Ty ele{};
	uptr_view<treeNode<Ty>> next{};
};

void test_que()
{
	unique_ptr<int> p { new int{1} };
	uptr_view pv{p};
	assert(pv.is_reference(p));
	unique_ptr<int> p2 { std::move(p) };
	assert(pv.is_reference(p));
	assert(!pv.is_reference(p2));
}

int main()
{
	test_basic();
	test_release();
	test_assignment();
	test_que();
}