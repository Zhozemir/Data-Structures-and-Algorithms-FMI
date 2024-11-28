#include "priorityQueue.hpp";

int main() {

	PriorityQueue<int> pq;

	pq.insert(1);
	pq.insert(6);
	pq.insert(3);

	std::cout << pq.size() << std::endl; //3
	std::cout << pq.peek() << std::endl; //6

	pq.pop();

	std::cout << pq.size() << std::endl; //2;
	std::cout << pq.peek() << std::endl; //3
	std::cout << pq.isEmpty(); // false(0)

}