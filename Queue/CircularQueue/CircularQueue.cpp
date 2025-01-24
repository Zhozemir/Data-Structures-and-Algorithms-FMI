#include "CircularQueue.hpp"

int main() {

	CircularQueue<int> q;

	q.push(1);
	q.push(4);
	q.push(7);

	std::cout << q.peek();

	q.pop();

	std::cout << q.peek();

	std::cout << q.isEmpty();

}