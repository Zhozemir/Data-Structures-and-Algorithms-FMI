#include "TreeSet.hpp"

int main() {
	
	TreeSet<int> s;

	s.insert(1);
	s.insert(3);
	s.insert(6);
	s.insert(7);

	std::cout << s.contains(3);
	s.remove(3);
	std::cout << s.contains(3);
	std::cout << s.getSize();

	std::cout << s.isEmpty();
	
	for (auto it = s.cbegin(); it != s.cend();) {
	
		int value = *it;
		it++;
		s.remove(value);
	
	}

	std::cout << s.isEmpty();

}