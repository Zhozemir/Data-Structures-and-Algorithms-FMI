#include <iostream>
#pragma once

template <class T>
class const_vector_iterator {

private:

	T* memPointer;

public:

	const_vector_iterator(T* passedVal) : memPointer ( passedValue ) {}
	const_vector_iterator(T* passedVal, size_t push) : memPointer ( passedValue + push ) {}

	const_vector_iterator<T> operator+(int off) const {
	
		return { memPointer + off };
	
	}

	const_vector_iterator<T> operator-(int off) const {
	
		return { memPointer - off };
	
	}

	int operator-(const_vector_iterator<T> other) const {
	
		return memPointer - other.memPointer;
	
	}

	const T* operator->() const noexcept {
	
		return memPointer;
	
	}

	const T& operator*() const noexcept {
	
		return *memPointer;
	
	}

	bool operator==(const const_vector_iterator& other) const {
	
		return (memPointer == other.memPointer);

	}

	bool operator!=(const_vector_iterator& other) const {
	
		return !(memPointer == other.memPointer);

	}

};