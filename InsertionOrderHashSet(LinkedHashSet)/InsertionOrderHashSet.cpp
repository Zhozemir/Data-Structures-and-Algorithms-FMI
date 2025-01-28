#include "InsertionOrderHashSet.hpp"

int main() {

	Set<int> s;

	s.add(4);
	s.add(5);
	s.add(6);

	for (auto it = s.cbegin(); it != s.cend(); it++)
		std::cout << *it;

	s.remove(5);

	for (auto it = s.cbegin(); it != s.cend(); it++)
		std::cout << *it;

	if (s.find(4) != s.cend())
		std::cout << "contains";
	else
		std::cout << "doesn't contain";

}