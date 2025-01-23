#include "ArrayStack.hpp"

int main() {

	ArrayStack<int> st;

	st.push(4);
	st.push(6);

	std::cout << st.peek();

	st.pop();

	std::cout << st.isEmpty();

	std::cout << st.peek();

}