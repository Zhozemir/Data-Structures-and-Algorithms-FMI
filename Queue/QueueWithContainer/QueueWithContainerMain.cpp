#include "QueueWithContainer.hpp"

int main() {

	QueueWithContainer<int> q;

	q.push(3);
	q.push(5);
	q.push(8);

	std::cout << q.front();

	q.pop();

	std::cout << q.front();

	std::cout << q.size();

	std::cout << q.empty();




}