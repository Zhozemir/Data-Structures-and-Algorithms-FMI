#include "LinkedStack.hpp"

int main() {

	LinkedStack<int> st;

	st.push(3);
	st.push(5);
	st.push(8);

	std::cout << st.peek();

	st.pop();

	std::cout << st.peek();

	st.pop();
	st.pop();

	std::cout << st.isEmpty();

}