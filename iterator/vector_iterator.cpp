#include <iostream>
#pragma once

template <class T>
class vector_iterator {

private:

	T* memPointer;


public:

	vector_iterator(T* passedValue) : memPointer(passedValue) {};
	vector_iterator(T* passedValue, size_t push) : memPointer(passedValue + push) {};

	vector_iterator<T>& operator++() {

		memPointer++;
		return *this;

	}

	vector_iterator<T> operator++(int) {
	
		vector_iterator it = *this;
		++(*this);
		return it;
	
	}

	vector_iterator<T>& operator--{
	
		memPointer--;
		return *this;
	
	}

	vector_operator<T> operator--{
	
		vector_operator it = *this;
		--(*this);
		return *it;
	
	}

	operator const_vector_iterator<T>() const {
	
		return const_vector_iterator<T>(memPointer);
	
	}

	vector_iterator<T> operator+(int off) const {
	
		return memPointer + off;
	
	}

	vector_iterator<T> operator-(int off) const {
	
		return memPointer - off;
	
	}

	T* operator->() {
	
		return memPointer;
	
	}

	const T* operator() const {

		return memPointer;

	}

	T& operator*() {
	
		return *memPointer;
	
	}

	bool operator==(const vector_iterator<T>& other) const {

		return memPointer = other.memPointer;

	}

	bool operator!=(const vector_iterator<T>& other) const {
	
		return !(memPointer == other.memPointer);
	
	}

};