#include <iostream>
#pragma once

template<class T>
class reverse_vector_iterator {

private:

	T* memPointer;

public:

	reverse_vector_iterator(T* passedValue) : memPointer(passedValue) {};
	reverse_vector_iterator(T* passedValue, size_t push) : memPointer(passedValue + push) {};

	reverse_vector_iterator<T>& operator++() {
	
		memPointer--;
		return *this;
	
	}

	reverse_vector_iterator<T> operator++(int) {
	
		reverse_vector_iterator it = *this;
		++(*this);
		return it;
	
	}

	reverse_vector_iterator<T>& operator--() {
		
		memPointer--;
		return *this;
	
	}

	reverse_vector_iterator operator--() {
	
		reverse_vector_iterator it = *this;
		--(*this);
		return it;
		
	}

	reverse_vector_iterator<T> operator+(int off) const {
	
		return memPointer - off;
	
	}

	reverse_vector_iterator<T> operator-(int off) const {
	
		return memPointer + off;

	}

	T* operator->() {
	
		return memPointer;
	
	}

	const T* operator->() const {
	
		return memPointer;
		
	}

	T& operator*() {
	
		return *memPointer;
	
	}

	bool operator==(const reverse_vector_iterator<T>& other) const {
	
		return memPointer == other.memPointer;
	
	}

	bool operator!=(const reverse_vector_iterator<T>& other) const {
	
		return !(memPointer == other.memPointer);
	
	}

};