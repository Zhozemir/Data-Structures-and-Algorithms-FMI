#include <iostream>
#include <vector>

size_t getLeftChild(size_t index) {

	return index * 2 + 1;

}

size_t getRightChild(size_t index) {

	return index * 2 + 2;

}

void heapify(std::vector<int>& data, size_t index, size_t size) {

	size_t currentIndex = index;

	while (true) {
	
		size_t leftChildIndex = getLeftChild(currentIndex);
		size_t rightChildIndex = getRightChild(currentIndex);

		bool shouldGoLeft = leftChildIndex < size && data[leftChildIndex] > data[currentIndex];
		bool shouldGoRight = rightChildIndex < size && data[rightChildIndex] > data[currentIndex];

		if (shouldGoLeft && shouldGoRight) {

			if (data[leftChildIndex] > data[rightChildIndex]) {

				std::swap(data[currentIndex], data[leftChildIndex]);
				currentIndex = leftChildIndex;

			}
			else {

				std::swap(data[currentIndex], data[rightChildIndex]);
				currentIndex = rightChildIndex;

			}

		}
		else if (shouldGoLeft) {

			std::swap(data[currentIndex], data[leftChildIndex]);
			currentIndex = leftChildIndex;

		}
		else if (shouldGoRight) {

			std::swap(data[currentIndex], data[rightChildIndex]);
			currentIndex = rightChildIndex;

		}
		else
			break;
	
	}
	
}

void heapSort(std::vector<int>& v) {

	if (v.empty())
		return;

	for (int i = v.size() / 2 - 1; i >= 0; i--)
		heapify(v, i, v.size());

	for (int i = v.size() - 1; i > 1; i--) {
	
		std::swap(v[0], v[i]);
		heapify(v, 0, i);
	
	}

}

int main() {

	std::vector<int> v = { 3, 1, 5, 6, 1, 2, 3 };

	heapSort(v);

	for (const auto& el : v)
		std::cout << el << " ";

}