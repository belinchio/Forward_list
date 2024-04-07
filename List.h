#pragma once

#include <cstddef>
#include <ios>
#include <iostream>

template<typename T>
struct Node
{
	size_t value;
	Node<T>* next;

	Node(size_t v, Node<T>* n) : value(v), next(n) {}

};

template<typename U>
class List {
private:
	Node<U>* m_head = nullptr;
	size_t m_size = 0u;

public:
	List() : m_head(), m_size() {}

	~List() {
		while (!empty()) {
			pop_front();
		}
	}

	Node<U>* getNode(size_t index) {
		Node<U>* n = m_head;
		for (auto i = 0; i < index; ++i) {
			n = n->next;
		}
		return n;
	}

	size_t& operator[] (size_t index) {
		return getNode(index)->value;
	} 

	[[nodiscard]] size_t size() const noexcept {
		return m_size;
	}

	[[nodiscard]] bool empty() const noexcept {
		return m_size == 0u;
	}

	void push_front(const size_t value) {
		m_head = new Node<U> (value, m_head);
		m_size++; 
	}

	void pop_front() {
		Node<U>* temp = m_head -> next;
		delete m_head;
		m_head = temp;
		m_size--;
	}

	void print() const {
		for (Node<U>* n = m_head; n; n = n->next) {
			std::cout << n->value << " ";
		}
		std::cout << std::endl;
	}

	void insert(Node<U>* elem, U value) {
		elem->next = new Node<U>(value, elem->next);
		m_size++;
	}
};

template<typename S>
void print(List<S>& lst) {
	for (auto i = 0; i < lst.size(); ++i) {
		std::cout << lst[i] << " ";
	}
	std::cout << std::endl;
}