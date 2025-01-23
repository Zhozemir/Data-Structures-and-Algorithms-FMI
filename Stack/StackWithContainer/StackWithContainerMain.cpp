#include "StackWithContainer.hpp"

int main() {

	StackWithContainer<int> s;

	s.push(1);
	s.push(6);
	s.push(7);

	std::cout << s.top();

	s.pop();

	std::cout << s.top();

	std::cout << s.empty();

}