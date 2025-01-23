#include <iostream>

template<typename T>
class ArrayStack {

private:

	T* data;
	size_t currentSize;
	size_t capacity;

	void copyFrom(const ArrayStack& other);
	void free();

	void resize(size_t newCapacity);

public:

	ArrayStack();
	ArrayStack(const ArrayStack<T>& other);
	ArrayStack<T>& operator=(const ArrayStack<T>& other);
	~ArrayStack();

	void push(const T& el);
	void pop();
	const T& peek() const;

	size_t size() const;
	size_t isEmpty() const;

};

template<typename T>
ArrayStack<T>::ArrayStack() : currentSize(0), capacity(4) {

	data = new T[capacity];

}

template<typename T>
void ArrayStack<T>::push(const T& el) {

	if (currentSize >= capacity)
		resize(capacity * 2);

	data[currentSize++] = el;

}

template<typename T>
void ArrayStack<T>::pop() {

	if (isEmpty())
		throw std::logic_error("The ArrayStack is empty!");

	T el = data[--currentSize];

	if (currentSize * 2 <= capacity && capacity > 1)
		resize(capacity / 2);

}

template<typename T>
const T& ArrayStack<T>::peek() const {

	if (isEmpty())
		throw std::logic_error("The ArrayStack is empty!");

	return data[currentSize - 1];

}

template<typename T>
size_t ArrayStack<T>::size() const {

	return currentSize;

}

template<typename T>
size_t ArrayStack<T>::isEmpty() const {

	return size() == 0;

}

template<typename T>
void ArrayStack<T>::copyFrom(const ArrayStack<T>& other) {

	data = new T[other.capacity];

	for (int i = 0; i < other.currentSize; i++)
		data[i] = other.data[i];

	currentSize = other.currentSize;
	capacity = other.capacity;

}

template<typename T>
void ArrayStack<T>::free() {

	delete[] data;

}

template<typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T>& other) {

	copyFrom(other);

}

template<typename T>
ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack<T>& other) {

	if (this != &other) {

		free();
		copyFrom(other);

	}

	return *this;

}

template<typename T>
ArrayStack<T>::~ArrayStack() {

	free();

}

template<typename T>
void ArrayStack<T>::resize(size_t newCapacity) {

	T* temp = data;
	data = new T[newCapacity];

	for (int i = 0; i < currentSize; i++)
		data[i] = temp[i];

	capacity = newCapacity;
	delete temp;

}
