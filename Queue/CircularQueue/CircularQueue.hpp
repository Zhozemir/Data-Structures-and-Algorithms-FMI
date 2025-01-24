#include <iostream>

template<typename T>
class CircularQueue {

private:

	T* data;
	size_t capacity;
	size_t count;

	size_t putIter;
	size_t getIter;

	void resize();
	void copyFrom(const CircularQueue<T>& other);
	void free();

public:

	CircularQueue();
	CircularQueue(const CircularQueue<T>& other);
	CircularQueue<T>& operator= (const CircularQueue<T>& other);
	~CircularQueue();

	void push(const T& el);
	void pop();
	const T& peek() const;
	bool isEmpty() const;

};

template<typename T>
CircularQueue<T>::CircularQueue() {

	const size_t DEFAULT_CAP = 4;

	data = new T[DEFAULT_CAP];
	capacity = DEFAULT_CAP;
	count = 0;
	putIter = 0;
	getIter = 0;

}

template<typename T>
void CircularQueue<T>::push(const T& el) {

	if (count == capacity)
		resize();

	data[putIter] = el;

	(++putIter) %= capacity;
	count++;

}

template<typename T>
void CircularQueue<T>::pop() {

	if (count == 0)
		throw std::logic_error("The CircularQueue is empty!");

	count--;
	(++getIter) %= capacity;

}

template<typename T>
const T& CircularQueue<T>::peek() const {
	
	if (isEmpty())
		throw std::logic_error("Queue is empty!");

	return data[getIter];

}

template<typename T>
bool CircularQueue<T>::isEmpty() const {

	return count == 0;

}

template<typename T>
CircularQueue<T>::CircularQueue(const CircularQueue<T>& other) {

	copyFrom(other);

}

template<typename T>
CircularQueue<T>& CircularQueue<T>::operator=(const CircularQueue<T>& other) {
	
	if (this != &other) {
	
		free();
		copyFrom(other);
	
	}

	return *this;

}

template<typename T>
CircularQueue<T>::~CircularQueue() {

	free();

}

template<typename T>
void CircularQueue<T>::copyFrom(const CircularQueue<T>& other) {

	data = new T[other.capacity];

	for (int i = other.getIter; i != other.putIter; (i += 1) %= other.capacity)
		data[i] = other.data[i];

	count = other.count;
	capacity = other.capacity;

	putIter = other.putIter;
	getIter = other.getIter;

}

template<typename T>
void CircularQueue<T>::free() {

	delete[] data;
	count = 0;
	capacity = 0;

}

template<typename T>
void CircularQueue<T>::resize() {
	
	size_t newCapacity = capacity * 2;
	size_t currentCapacity = capacity;

	T* temp = new T[newCapacity];

	for (int i = 0; i < currentCapacity; i++) {
	
		temp[i] = peek();
		pop();
	
	}

	getIter = 0;
	putIter = capacity;

	count = capacity;
	capacity *= 2;
	
	delete[] data;
	data = temp;

}