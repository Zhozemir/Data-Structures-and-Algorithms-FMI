#pragma once
#include "iterators.hpp"

namespace Constants {

	constexpr unsigned GROWTH_FACTOR = 2;

}

template<class T>
class vector {

private:

	void copy(const vector& other);
	void move(vector&& other);
	void free();
	size_t calculate_capacity() const;

	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

public:

	using iterator = vector_iterator<T>;
	using const_iterator = const_vector_iterator<T>;
	using reverse_iterator = reverse_vector_iterator<T>;

	vector() = default();
	explicit vector(size_t count);
	vector(size_t count, const T& initial);

	vector(const vector& other);
	vector& operator=(const vector& other);

	vector(vector&& other);
	vector& operator=(vector&& other);

	void push_back(const T& element);
	void push_back(T&& element);
	void pop_back();

	void erase(const_iterator position);
	void erase(const_iterator first, const_iterator last);

	void clear();

	template<class... Args>
	void emplace_back(Args&&... args);

	T& operator[](size_t index)
		const T& operator[](size_t index) const;

	T* data();

	void resize(size_t n);
	void reserve(size_t n);
	void shrink_to_fit();

	size_t size() const;
	size_t capacity() const;
	bool empty() const;

	iterator begin() {

		return iterator(data);

	}

	iterator end() {

		return iterator(data + size());

	}

	const_iterator c_begin() const {

		return const_iterator(data);

	}

	const_iterator c_end() const {

		return const_iterator(data + size);

	}

	reverse_iterator rbegin() {

		return size() > 0 ? reverse_iterator(data + size() - 1) : reverse_iterator(nullptr);

	}

	reverse_iterator rend() {

		return size() > 0 ? reverse_iterator(data - 1) : reverse_iterator(nullptr);

	}

	const T& back() const {

		return data[size() - 1];

	}

	T& back() {

		return data[size() - 1];

	}

	const T& front() const {

		return data[0];

	}

	T& front() {

		return data[0];

	}

	~vector();

	template<class T>
	vector<T>::vector(size_t count) : 
		
		data(static_cast<T*>(operator new(count * sizeof(T)))),
		size(count), 
		capacity(count) 

	{

    for (size_t i = 0; i < count; i++)
        new (&data[i]) T();

	}

	template<class T>
	vector<T>::vector(size_t count, const T& initial) :

		data(static_cast<T*>(operator new(count * sizeof(T)))),
		size(count),
		capacity(count)

	{

		for (size_t i = 0; i < count; i++)
			new (&data[i]) T(initial);

	}

	template<class T>
	void vector<T>::copy(const vector<T>& other) {

		data = static_cast<T*> (operator new(other.capacity() * sizeof<T>)));

	for (size_t i = 0; i < other.size(); i++)
		new (&data[i]) T(other[i]);

	size = other.size();
	capacity = other.capacity;

	}

	template<class T>
	void vector<T>::move(vector<T>&& other) {

		data = other.data;
		size = other.size;
		capacity = other.capacity;

		other.data = nullptr;
		other.size = other.capacity = 0;

	}

	template<class T>
	void vector<T>::free() {

		for (size_t i = 0; i < size(); i++)
			data[i].~T();

		operator delete(data, capacity() * sizeof(T));

	}

	template<class T>
	vector<T>::vector(const vector& other) {

		copy(other);

	}

	template<class T>
		vector<T>& vector<T>::operator=(const vector& other) {

		if (this != other) {

			free();
			copy(other);

		}

		return *this;

	}

	template<class T>
	vector<T>::vector(vector&& other) {

		move(std::move(other));

	}

	template<T>
	vector<T>& vector<T>::operator=(vector&& other) {

		if (this != other) {

			free();
			move(std::move(other));

		}

		return *this;

	}

	template<class T>
	vector<T>::~vector() {

		free();

	}

	template<class T>
	size_t vector<T>::size() const {

		return size;

	}

	template<class T>
	size_t vector<T>::capacity() const {

		return capacity;

	}

	template<class T>
	size_t vector<T>::calculate_capacity() const {
	
		if (capacity() == 0)
			return 1;

		return capacity() * Constants::GROWTH_FACTOR;
	
	}

	template<class T>
	void vector<T>::resize(size_t n) {
		
		if (n < size()) {
		
			for (size_t i = n; i < size(); i++)
				(data + i)->~T();

			size = n;
	
		}
		else if (n > size()) {

			if (n <= capacity) {

				for (size_t i = size(); i < n; i++)
					new (&data[i]) T();

				size = n;

			}
		
			else {

				T* new_data = static_cast<T*> (operator new(n * sizeof(T)));

				for (size_t i = 0; i < size; i++)
					new (&new_data[i]) T(std::move(data[i]));

				for (size_t i = size(); i < n; i++)
					new (&new_data[i]) T();

				operator delete(data, capacity * sizeof(T));

				data = new_data;
				capacity = n;
				size = n;

			}
		
		}
	
	}

	template<class T>
	void vector<T>::reserve(size_t n) {

		if (n <= capacity())
			return;

		T* new_data = static_cast<T*>(operator new (n * sizeof(T)));

		for (size_t i = 0; i < size(); i++) {
		
			new(&new_data[i]) T(std::move(data[i]));
			data[i].~T();
		
		}

		operator delete(data, capacity() * sizeof(T));

		data = new_data;
		capacity = n;
		
	}

	template<class T>
	void vector<T>::shrink_to_fit() {
	
		if (capacity() == size())
			return;

		T* new_data = static_cast<T*>(operator new(size() * sizeof(T)));

		for (size_t i = 0; i < size(); i++) {
			
			new (&new_data T(std::move(data[i])));
			data[i].~T();
		
		}

		operator delete(data, capacity() * sizeof(T));

		capacity = size;
		data = new_data;
	
	}

	template<class T>
	void vector<T>::push_back(const T& element) {
	
		if (size() == capacity())
			reserve(calculate_capacity());

		new (&data[size++]) T(element);
	
	}

	template<class T>
	void vector<T>::push_back(T&& element) {
	
		if (size() == capacity())
			reserve(calculate_capacity());

		new (&data[size++]) T(std::move(element));
	
	}

	template<class T>
	void vector<T>::erase(const_iterator first, const_iterator last) {
	
		int deleted_count = last - first;

		if (deleted_count <= 0)
			return;

		int begin_offset = first - begin();
		int end_offset = last - begin();

		if (last != c_end()) {
		
			for (size_t i = end_offset; i < size(); i++)
				new (&data[begin_offset++]) T(std::move(data[i]));
		
		}

		for (size_t i = end_offset; i < size(); i++)
			(data + i)->~T();

		size -= deleted_count;

	}


	template<class T>
	void vector<T>::erase(const_iterator position) {
	
		erase(position, position + 1);
	
	}

	template<class T>
	void vector<T>::pop_back() {
	
		if (empty())
			return;

		erase(--end());
	
	}

	template<class T>
	template<class... Args>
	void vector<T>::emplace_back(Args&&... args) {
	
		if(size() == capacity()
			reserve(calculate_capacity());

		new (&data[size++]) T(std::forward<Args>(args)...);
	
	}

	template<class T>
	T& vector<T>::operator[] (size_t index) {
	
		return data[index];
	
	}

	template<class T>
	const T& vector<T>::operator[] (size_t index) const {
	
		return data[index];
	
	}

	template<class T>
	T* vector<T>::data() {
	
		return data;
	
	}

	template<T>
	void vector<T>::clear() {
	
		for (size_t i = 0; i < size(); i++)
			(data + i)->T();

		size = 0;
	
	}

	template<class T>
	bool vector<T>::empty() const {
	
		return size() == 0;
	
	}

};