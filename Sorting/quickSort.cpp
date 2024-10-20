#include <iostream>

template <class T>
size_t advancedPartition(T* pArr, size_t len) {

	if (pArr[0] > pArr[len - 1])
		std::swap(pArr[0], pArr[len - 1]);

	T& partitioningElement = pArr[len - 1];

	size_t left = 0;
	size_t right = len - 1;

	while (true) {
	
		while (pArr[++left] < partitioningElement);

		while (pArr[--right] > partitioningElement) {
		
			if (left == right)
				break;
		
		}

		if (left >= right)
			break;
	
		std::swap(pArr[left], pArr[right]);
	
	}

	std::swap(pArr[left], partitioningElement);

	return left;

}

template <typename T>
void QuickSort(T* arr, size_t len) {

	if (len <= 1)
		return;

	size_t pivotIndex = advancedPartition(arr, len);

	QuickSort(arr, pivotIndex);
	QuickSort(arr + pivotIndex + 1, len - pivotIndex - 1);

}

int main() {

	constexpr int size = 8;

	int arr[] = { 3, 5, 1, 3, 8, 4, 9, 1 };
	QuickSort(arr, size);

	for (int i = 0; i < size; i++) {
	
		std::cout << arr[i] << " ";
	
	}


}