#include <iostream>

template<typename T>
class LinkedQueue {

private:

	struct Node {

		T data;
		Node* next;

		Node(const T& data) : data(data), next(nullptr) {}

	};

	Node* head;
	Node* tail;

	void copyFrom(const LinkedQueue& other);
	void free();

public:

	LinkedQueue();
	LinkedQueue(const LinkedQueue& other);
	LinkedQueue operator=(const LinkedQueue& other);
	~LinkedQueue();

	void push(const T& el);
	void pop();
	const T& peek() const;

	bool isEmpty() const;

};

template<typename T>
LinkedQueue<T>::LinkedQueue() : head(nullptr), tail(nullptr) {}

template<typename T>
void LinkedQueue<T>::push(const T& el) {

	Node* newNode = new Node(el);

	if (isEmpty()) {
	
		head = newNode;
		tail = newNode;
	
	}
	else {
	
		tail->next = newNode;
		tail = newNode;
	
	}

}

template<typename T>
void LinkedQueue<T>::pop() {
	
	if (isEmpty())
		throw std::logic_error("The LinkedQueue is empty!");
	else if (head == tail) {
	
		T el = head->data;
		delete head;
	
		head = nullptr;
		tail = nullptr;
	
	}
	else {
	
		Node* temp = head->next;

		delete head;
		head = temp;
	
	}

}

template<typename T>
const T& LinkedQueue<T>::peek() const {

	if (isEmpty())
		throw std::logic_error("The LinkedQueue is empty!");

	return head->data;

}

template<typename T>
bool LinkedQueue<T>::isEmpty() const {

	return head == nullptr && tail == nullptr;

}

template<typename T>
void LinkedQueue<T>::copyFrom(const LinkedQueue& other) {

	Node* iter = other.head;

	while (iter) {

		push(iter->data);
		iter = iter->next;

	}

}

template<typename T>
void LinkedQueue<T>::free() {

	Node* iter = head;

	while (iter) {

		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;

	}

	head = tail = nullptr;

}

template<typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue& other) {

	copyFrom(other);

}

template<typename T>
LinkedQueue<T> LinkedQueue<T>::operator=(const LinkedQueue& other) {

	if (this != &other) {

		free();
		copyFrom(other);

	}

	return *this;

}

template<typename T>
LinkedQueue<T>::~LinkedQueue() {

	free();

}