#pragma once
#include <iostream>
#include <vector>

template<typename T>
class PriorityQueue {

private:

	static size_t leftChild(size_t ind);
	static size_t rightChild(size_t ind);

	static size_t parent(size_t ind);

	void heapify(size_t ind);

	std::vector<T> data;

public:

	PriorityQueue() = default;
	PriorityQueue(const std::vector<T>& v);

	void pop();
	void insert(const T& el);
	const T& peek() const;

	bool isEmpty() const;
	size_t size() const;

};

template<typename T>
size_t PriorityQueue<T>::leftChild(size_t ind) {

	return 2 * ind + 1;

}

template<typename T>
size_t PriorityQueue<T>::rightChild(size_t ind) {

	return 2 * ind + 2;

}

template<typename T>
size_t PriorityQueue<T>::parent(size_t ind) {

	return (ind - 1) / 2;

}

template<typename T>
void PriorityQueue<T>::heapify(size_t ind) {

	size_t currentElementIndex = ind;

	while (true) {
	
		size_t leftChildIndex = leftChild(currentElementIndex);
		size_t rightChildIndex = rightChild(currentElementIndex);

		bool shouldGoLeft = leftChildIndex < data.size() && data[leftChildIndex] > data[currentElementIndex];
		bool shouldGoRight = rightChildIndex < data.size() && data[rightChildIndex] > data[currentElementIndex];

		if (shouldGoLeft && shouldGoRight) {

			if (data[leftChildIndex] > data[rightChildIndex]) {

				std::swap(data[currentElementIndex], data[leftChildIndex]);
				currentElementIndex = leftChildIndex;

			}
			else {

				std::swap(data[currentElementIndex], data[rightChildIndex]);
				currentElementIndex = rightChildIndex;

			}

		}
		else if (shouldGoLeft) {

			std::swap(data[currentElementIndex], data[leftChildIndex]);
			currentElementIndex = leftChildIndex;

		}
		else if (shouldGoRight) {

			std::swap(data[currentElementIndex], data[rightChildIndex]);
			currentElementIndex = rightChildIndex;

		}
		else
			break;
	
	}

}

template<typename T>
PriorityQueue<T>::PriorityQueue(const std::vector<T>& v) : data(v) {

	for (int i = (v.size() / 2) - 1; i >= 0; i--)
		heapify(i);

}

template<typename T>
void PriorityQueue<T>::pop() {

	if (isEmpty())
		throw std::runtime_error("The queue is empty!");

	data[0] = data[data.size() - 1];
	data.pop_back();

	if (data.size() != 0)
		heapify(0);

}

template<typename T>
void PriorityQueue<T>::insert(const T& el) {

	data.push_back(el);

	int ind = data.size() - 1;
	int parentIndex = parent(ind);

	while(ind > 0 && data[ind] > data[parentIndex]){
	
		std::swap(data[ind], data[parentIndex]);
		ind = parentIndex;
		parentIndex = parent(ind);
	
	}

}

template<typename T>
const T& PriorityQueue<T>::peek() const {

	if (isEmpty())
		throw std::runtime_error("The queue is empty!");

	return data[0];

}

template<typename T>
bool PriorityQueue<T>::isEmpty() const {

	return data.empty();

}

template<typename T>
size_t PriorityQueue<T>::size() const {

	return data.size();

}