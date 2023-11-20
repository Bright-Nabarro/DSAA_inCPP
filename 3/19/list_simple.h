#pragma once
#include <cstdlib>

namespace my_stl2
{

/**
 * @brief with out using head and tail node
 * 
 * @tparam Object 
 */
template<typename Object>
class list
{
private:	
	struct Node
	{
		Object m_element;
		Node* m_next;

		Node(const Object& element = Object{}, Node* next = nullptr)
			: m_element{element}, m_next{next}{};
	};
	size_t m_size;
	Node* m_first;
public:
	list():m_first{nullptr}{}
	~list() {
        Node* current = m_first;
        while (current != nullptr) {
            Node* temp = current;
            current = current->m_next;
            delete temp;
        }
    }
	void append(Object element) {
        if (m_first == nullptr) {
            m_first = new Node(element);
            return;
        }
        Node* current = m_first;
        while (current->m_next != nullptr) {
            current = current->m_next;
        }
        current->m_next = new Node(element);
    }
	Object get(size_t index) {
	    Node* current = m_first;
	    size_t count = 0;

	    while (current != nullptr) {
	        if (count == index)
	            return current->m_element;
	        count++;
	        current = current->m_next;
	    }
		return {};
	}
};

}   //my_stl2