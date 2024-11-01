#pragma once
#include <iostream>

template<typename T>
class DoublyLinkedList {

private:

	size_t count = 0;

	struct Node {

		T data;
		Node* next;
		Node* prev;

		Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}

	};

	Node* head = nullptr;
	Node* tail = nullptr;
	
	void copyFrom(const DoublyLinkedList& other);
	void moveFrom(DoublyLinkedList&& other);
	void free();

public:

	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList<T>& other);
	DoublyLinkedList<T>& operator= (const DoublyLinkedList<T>& other);

	DoublyLinkedList(DoublyLinkedList<T>&& other);
	DoublyLinkedList<T>& operator=(DoublyLinkedList<T>&& other);

	~DoublyLinkedList();

	void push_back(const T& el);
	void push_front(const T& el);
	void pop_back();
	void pop_front();

	const T& front() const;
	const T& back() const;

	T& front();
	T& back();

	void print() const;

	size_t getSize() const;

	bool isEmpty() const;

	void clear();



	class DllIterator;
	class ConstDllIterator;

	DllIterator insert(const T& element, const ConstDllIterator& it);
	DllIterator remove(const DllIterator& it);

	DllIterator begin() {
	
		return DllIterator(*this, head);
	
	}

	DllIterator end() {
	
		return DllIterator(*this, nullptr);
	
	}

	ConstDllIterator cbegin() const {
	
		return ConstDllIterator(*this, head);
	
	}

	ConstDllIterator cend() const {
	
		return ConstDllIterator(*this, nullptr);
	
	}

	class DllIterator{
	
	private:

		friend class DoublyLinkedList;
		Node* currentElementPtr;
		DoublyLinkedList& list;

	public:

		DllIterator(DoublyLinkedList& list, Node* currentElementPtr) : list(list), currentElementPtr(currentElementPtr) {}

		T& operator*() {
		
			return currentElementPtr->data;

		}

		T* operator->() {
		
			return &currentElementPtr->data;
		
		}

		DllIterator operator++() {
		
			if (currentElementPtr)
				currentElementPtr = currentElementPtr->next;

			return *this;
		
		}

		DllIterator operator++(int) {
		
			DllIterator copy(*this);
			++(*this);
			return copy;
		
		}

		DllIterator operator--() {
		
			if (currentElementPtr)
				currentElementPtr = currentElementPtr->prev;
			else
				currentElementPtr = list.tail;

			return *this;
		
		}

		DllIterator operator--(int) {
			
			DllIterator copy(*this);
			--(*this);
			return copy;
		
		}

		bool operator==(const DllIterator& other) const {
		
			return currentElementPtr == other.currentElementPtr;
		
		}

		bool operator!=(const DllIterator& rhs) const {
		
			return !(*this == other);
		
		}

	};

	class ConstDllIterator {

	private:

		friend class DoublyLinkedList;
		Node* currentElementPtr;
		const DoublyLinkedList& list;

	public:

		ConstDllIterator(const DoublyLinkedList& list, Node* currentElementPtr) : list(list), currentElementPtr(currentElementPtr) {}
		ConstDllIterator(const DllIterator& iter) : list(iter.list), currentElementPtr(iter.currentElementPtr) {}

		const T& operator*() const {
		
			return currentElementPtr->data;
		
		}

		const T* operator->() {
		
			return &currentElementPtr->data;
		
		}

		ConstDllIterator& operator++() {
		
			if (currentElementPtr)
				currentElementPtr = currentElementPtr->next;

			return *this;
		
		}

		ConstDllIterator operator++(int) {
		
			ConstDllIterator copy(*this);
			++(*this);
			return copy;
		
		}

		ConstDllIterator& operator--() {
		
			if (currentElementPtr)
				currentElementPtr = currentElementPtr->prev;
			else
				currentElementPtr = list.tail;

			return *this;
		
		}

		ConstDllIterator operaotor--(int) {
		
			ConstDllIterator copy(*this);
			++(*this);

			return copy;
		
		}

		bool operator==(const ConstDllIterator& other) const {
		
			return currentElementPtr == other.currentElementPtr;
		
		}

		bool operator!=(const ConstDllIterator& other) const {
		
			return !(other == *this);
		
		}

	};

};

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

template<typename T>
void DoublyLinkedList<T>::copyFrom(const DoublyLinkedList<T>& other) {

	Node* otherIter = other.head;

	while (otherIter != nullptr) {
	
		push_back(otherIter->data);
		otherIter = otherIter->next;
		
	}

	count = other.count;

}

template<typename T>
void DoublyLinkedList<T>::moveFrom(DoublyLinkedList<T>&& other) {

	head = other.head;
	tail = other.tail;
	count = other.count;
	
	other.head = other.tail = nullptr;
	other.count = 0;

}

template<typename T>
void DoublyLinkedList<T>::free() {

	Node* iter = head;

	while (iter) {
	
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	
	}

	head = tail = nullptr;
	count = 0;

}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) {

	copyFrom(other);

}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {

	if (this != &other) {
	
		free();
		copyFrom(other);
	
	}

	return *this;

}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& other) {

	moveFrom(std::move(other));

}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>&& other) {

	if (this != &other) {
	
		free();
		moveFrom(std::move(other));
	
	}

	return *this;

}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {

	free();

}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& el) {

	Node* toAdd = new Node(el);

	if (isEmpty())
		head = tail = toAdd;

	else {
	
		tail->next = toAdd;
		toAdd->prev = tail;
		tail = toAdd;
	
	}

	count++;

}

template<typename T>
void DoublyLinkedList<T>::push_front(const T& el) {

	Node* toAdd = new Node(el);

	if (isEmpty())
		head = tail = toAdd;
	
	else {
	
		toAdd->next = head;
		head->prev = toAdd;
		head = toAdd;

	}

	count++;
	
}

template<typename T>
void DoublyLinkedList<T>::pop_back() {

	if (isEmpty())
		throw std::runtime_error("The list is empty!");

	if (head == tail) {
	
		delete head;
		head = tail = nullptr;
	
	}
	else {
	
		tail->prev->next = nullptr;

		Node* toDelete = tail;

		tail = tail->prev;
	
		delete toDelete;
	
	}

	count--;

}

template<typename T>
void DoublyLinkedList<T>::pop_front() {

	if (isEmpty())
		throw std::runtime_error("The list is empty!");

	if (head == tail) {
		
		delete head;
		head = tail = nullptr;
	
	}
	else {
	
		head->next->prev = nullptr;

		Node* toDelete = head;
		head = head->next;

		delete toDelete;
	
	}

	count--;

}

template<typename T>
const T& DoublyLinkedList<T>::front() const {

	if (isEmpty())
		throw std::runtime_error("The list is empty!");

	return head->data;

}

template<typename T>
T& DoublyLinkedList<T>::front() {

	if(isEmpty())
		throw std::runtime_error("The list is empty!");


	return head->data;
	
}

template<typename T>
const T& DoublyLinkedList<T>::back() const {

	if (isEmpty())
		throw std::runtime_error("The list is empty!");


	return tail->data;

}

template<typename T>
T& DoublyLinkedList<T>::back() {

	if (isEmpty())
		throw std::runtime_error("The list is empty!");

	return tail->data;

}

template<typename T>
typename DoublyLinkedList<T>::DllIterator DoublyLinkedList<T>::insert(const T& element, const ConstDllIterator& it) {

	if (it == cbegin()) {

		push_front(element);
		return begin();

	}
	else if (it == cend()) {

		push_back(element);
		return DllIterator(*this, tail);

	}
	else {

		Node* current = it.currentElementPtr;
		Node* toInsert = new Node(element);

		toInsert->next = current;
		toInsert->prev = current->prev;
		current->prev->next = toInsert;
		current->prev = toInsert;

		count++;

		return DllIterator(*this, toInsert);

	}

}

	template<typename T>
	typename DoublyLinkedList<T>::DllIterator DoublyLinkedList<T>::remove(const DllIterator& it) {
	
		Node* toDelete = it.currentElementPtr;

		if (!toDelete)
			throw std::runtime_error("Cannot remove end iterator");

		if (toDelete == head) {
		
			pop_front();
			return begin();
		
		}

		else if (toDelete == tail) {
		
			pop_back();
			return end();
		
		}
		else {
		
			toDelete->prev->next = toDelete->next;
			toDelete->next->prev = toDelete->prev;
			Node* nextNode = toDelete->next;

			delete toDelete;
		
			count--;

			return DllIterator(*this, nextNode);
		
		
		}
	
	}

template<typename T>
void DoublyLinkedList<T>::print() const{

	Node* iter = head;

	while (iter) {
	
		std::cout << iter->data;
		if (iter != tail)
			std::cout << "<->";
		iter = iter->next;
	
	}

	std::cout << std::endl;

}

template<typename T>
size_t DoublyLinkedList<T>::getSize() const {

	return count;

}

template<typename T>
bool DoublyLinkedList<T>::isEmpty() const {

	return head == nullptr;

}

template<typename T>
void DoublyLinkedList<T>::clear() {

	free();

}