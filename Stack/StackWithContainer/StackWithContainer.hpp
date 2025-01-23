#include <iostream>
#include<deque>

template<class T, class Container = std::deque<T>>
class StackWithContainer {

private:

	Container c;

public:

	void push(const T& el) {
	
		c.push_back(el);
	
	}

	void pop() {
	
		c.pop_back();
	
	}

	T& top() {
	
		return c.back();
	
	}

	const T& top() const {
	
		return c.back();
	
	}

	size_t size() const {
	
		return c.size();
	
	}

	bool empty() const {
	
		return c.empty();
	
	}

};