#include <iostream>

template<typename T>
class SinglyLinkedList {

private:

	struct Node {

		T data;
		Node* next;

		Node(const T& data) : data(data), next(nullptr) {}

	};

	Node* head = nullptr;
	Node* tail = nullptr;

	size_t size = 0;

	void copyFrom(const SinglyLinkedList<T>& other);
	void moveFrom(SinglyLinkedList<T>&& other);
	void free();

public:

	SinglyLinkedList() = default;
	SinglyLinkedList(const SinglyLinkedList<T>& other);
	SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& other);
	~SinglyLinkedList();

	SinglyLinkedList(SinglyLinkedList<T>&& other);
	SinglyLinkedList<T>& operator=(SinglyLinkedList<T>&& other);

	void pushFront(const T& el);
	void pushBack(const T& el);

	void popFront();

	const T& front() const;
	const T& back() const;

	T& front();
	T& back();

	size_t getSize() const;
	bool isEmpty() const;

	template<typename U>
	friend SinglyLinkedList<U> concat(SinglyLinkedList<U>& lhs, SinglyLinkedList<U>& rhs);

	void print() const;

	class Iterator {

	private:

		Node* currentElementPtr;

		friend class SinglyLinkedList;

	public:

		Iterator(Node* currentElementPtr = nullptr) : currentElementPtr(currentElementPtr) {}

		T& operator*() {
		
			return currentElementPtr->data;
		
		}

		T* operator->() {
		
			return &currentElementPtr->data;
		
		}

		Iterator& operator++() {
		
			if (currentElementPtr)
				currentElementPtr = currentElementPtr->next;

			return *this;
			
		}

		Iterator operator++(int) {
		
			Iterator copy(*this);
			++(*this);
			return copy;
		
		}

		Iterator& operator+=(size_t s) {
		
			while (s--)
				++(*this);

			return *this;
		
		}

		Iterator operator+(int i) const {
		
			Iterator res(*this);
			return res += i;

		}

		bool operator==(const Iterator& rhs) const {
		
			return currentElementPtr == rhs.currentElementPtr;
		
		}

		bool operator!=(const Iterator& rhs) const {
		
			return !(rhs == *this);
		
		}

	};

	class ConstIterator {

	private:

		Node* currElementPtr;

		friend class SinglyLinkedList;

	public:

		ConstIterator(Node* currentElementPtr = nullptr) : currElementPtr(currElementPtr) {}

		const T& operator*() const {
		
			return currElementPtr->data;
		
		}

		const T* operator->() const {
		
			return &currElementPtr->data;
		
		}

		ConstIterator& operator++() {
		
			if (currElementPtr)
				currElementPtr = currElementPtr->next;

			return *this;
		
		}

		ConstIterator operator++(int) {
		
			ConstIterator copy(*this);
			++(*this);
			return copy;
		
		}

		ConstIterator& operator+=(size_t s) {
			
			while(s--)
				++(*this);

			return *this;
		
		}

		ConstIterator& operator+(int i) const {
		
			ConstIterator res(*this);
			return res += i;
		
		}

		bool operator==(const ConstIterator& rhs) const {
		
			return currElementPtr == rhs.currElementPtr;
		
		}

		bool operator!=(const ConstIterator& rhs) const {
		
			return !(rhs == *this);
		
		}

	};

	 Iterator begin() {
	
		return Iterator(head);
	
	}

	Iterator end() {
	
		return Iterator(nullptr);
	
	}

	ConstIterator cbegin() const {
	
	
		return ConstIterator(head);
	
	}

	ConstIterator cend() const {
	
		return ConstIterator(nullptr);
	
	}

	Iterator insertAfter(const T& element, const ConstIterator& it);

	Iterator removeAfter(const ConstIterator& it);

};


template<typename T>
void SinglyLinkedList<T>::pushFront(const T& el) {

	Node* newNode = new Node(el);

	if (isEmpty()) {
	
		head = tail = newNode;
	
	}
	else {
	
		newNode->next = head;
		head = newNode;

	}

	size++;

}

template<typename T>
void SinglyLinkedList<T>::pushBack(const T& el) {

	Node* newNode = new Node(el);

	if (isEmpty()) {
	
		head = tail = newNode;
	
	}
	else {
	
		tail->next = newNode;
		tail = newNode;
	
	}

	size++;

}

template<typename T>
void SinglyLinkedList<T>::popFront() {

	if (!head)
		throw std::logic_error("Empty list!");

	if (head == tail) {
	
		delete head;
		head = tail = nullptr;
	
	}
	else {
	
		Node* toDelete = head;
		head = head->next;
		delete toDelete;

	}

	size--;

}

template<typename T>
const T& SinglyLinkedList<T>::front() const {

	if (!head)
		throw std::logic_error("Empty list!");

	return head->data;

}

template<typename T>
const T& SinglyLinkedList<T>::back() const {

	if (!tail)
		throw std::logic_error("Empty list!");

	return tail->data;
	
}

template<typename T>
T& SinglyLinkedList<T>::front() {

	if (!head)
		throw std::logic_error("Empty list!");

	return head->data;

}

template<typename T>
T& SinglyLinkedList<T>::back() {

	if (!tail)
		throw std::logic_error("Empty list!");

	return tail->data;

}

template<typename T>
size_t SinglyLinkedList<T>::getSize() const {

	return size;

}

template<typename T>
bool SinglyLinkedList<T>::isEmpty() const {

	return getSize() == 0;

}

template<typename T>
SinglyLinkedList<T> concat(SinglyLinkedList<T>& lhs, SinglyLinkedList<T>& rhs) {

	SinglyLinkedList<T> result;

	if (!lhs.head) {
	
		result.head = rhs.head;
		result.tail = rhs.tail;
	
	}
	else if (!rhs.head) {
	
		result.head = lhs.head;
		result.tail = lhs.tail;
	
	}
	else {

		lhs.tail->next = rhs.head;
		result.head = lhs.head;
		result.tail = rhs.tail;

	}

	result.getSize = lhs.size() + rhs.size();

	rhs.size() = lhs.size() = 0;

	rhs.head = rhs.tail = lhs.head = lhs.tail = nullptr;

	return result;

}

template<typename T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::insertAfter(const T& element, const typename SinglyLinkedList<T>::ConstIterator& it) {

	if (it == end())
		return end();

	Node* newNode = new Node(element);
	Node* itNode = it.currentElementPtr;

	newNode->next = itNode->next;
	itNode->next = newNode;

	size++;

	return SinglyLinkedList<T>::Iterator(newNode);

}

template<typename T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::removeAfter(const typename SinglyLinkedList<T>::ConstIterator& it) {

	if (it == end() || getSize() == 1)
		return end();

	Node* toDelete = (it + 1).currentElementPtr;

	Node* newNext = toDelete->next;

	it.currentElementPtr->next = newNext;
	size--;

	if (toDelete == tail) {
	
		tail = it.currentElementPtr;
	
	}

	delete toDelete;

	return SinglyLinkedList<T>::Iterator(newNext);

}

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other) {

	copyFrom(other);

}

template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other) {

	if (this != other) {
	
		free();
		copyFrom(other);
	
	}

	return *this;

}

template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {

	free();

}

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList&& other) {

	moveFrom(std::move(other));

}

template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList<T>&& other) {

	if (this != &other) {
	
		free();
		moveFrom(std::move(other));
	
	}

	return *this;

}

template<typename T>
void SinglyLinkedList<T>::copyFrom(const SinglyLinkedList& other) {

	Node* iter = other.head;

	while (iter) {
	
		pushBack(iter->data);
		iter = iter->next;
	
	}

}

template<typename T>
void SinglyLinkedList<T>::moveFrom(SinglyLinkedList<T>&& other) {

	head = other.head;
	tail = other.tail;
	size = other.size;

	other.head = other.tail = nullptr;
	other.size = 0;

}

template<typename T>
void SinglyLinkedList<T>::free() {

	Node* iter = head;

	while (iter) {
	
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	
	}

	head = tail = nullptr;
	size = 0;

}

template<typename T>
void SinglyLinkedList<T>::print() const {

	Node* iter = head;

	while (iter) {
	
		std::cout << iter->data << ' ';
		if (iter->next)
			std::cout << "->" << ' ';
	
		iter = iter->next;
	
	}

	std::cout << std::endl;

}
