#include <iostream>

template<typename T>
class LinkedStack {

private:

	struct Node {

		T data;
		Node* next;

		Node(const T& data) : data(data), next(nullptr) {}

	};

	Node* head;

	void copyFrom(const LinkedStack& other);
	void free();

public:

	LinkedStack();
	LinkedStack(const LinkedStack& other);
	LinkedStack operator=(const LinkedStack& other);
	~LinkedStack();

	void push(const T& el);
	void pop();
	const T& peek() const;

	bool isEmpty() const;
	
};

template<typename T>
LinkedStack<T>::LinkedStack() : head(nullptr) {}

template<typename T>
void LinkedStack<T>::push(const T& el) {

	Node* newNode = new Node(el);

	if (isEmpty())
		head = newNode;
	else {
	
		newNode->next = head;
		head = newNode;
	
	}

}

template<typename T>
void LinkedStack<T>::pop() {

	if (isEmpty())
		throw std::logic_error("The LinkedStack is empty!");
	else if (head->next == nullptr) {
	
		delete head;
		head = nullptr;
	
	}
	else {
	
		Node* temp = head->next;
		delete head;
		head = temp;
	
	}

}

template<typename T>
const T& LinkedStack<T>::peek() const {

	if (isEmpty())
		throw std::logic_error("The LinkedStack is empty!");

	return head->data;

}

template<typename T>
bool LinkedStack<T>::isEmpty() const {

	return head == nullptr;

}

template<typename T>
void LinkedStack<T>::copyFrom(const LinkedStack& other) {

	head = nullptr;

	if (other.isEmpty())
		return;

	Node* iterOther = other.head;

	head = new Node(iterOther->data);

	Node* iterThis = head;

	do {

		iterOther = iterOther->next;

		if (iterOther) {

			iterThis->next = new Node(iterOther->data);
			iterThis = iterThis->next;

		}

	} while (iterOther);

}

template<typename T>
void LinkedStack<T>::free() {

	Node* iter = head;

	while (iter) {

		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;

	}

}

template<typename T>
LinkedStack<T>::LinkedStack(const LinkedStack& other) {

	copyFrom(other);

}

template<typename T>
LinkedStack<T> LinkedStack<T>::operator=(const LinkedStack& other) {

	if (this != &other) {

		free();
		copyFrom(other);

	}

	return *this;

}

template<typename T>
LinkedStack<T>::~LinkedStack() {

	free();

}