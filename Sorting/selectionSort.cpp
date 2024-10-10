#include <iostream>

template <class T>

void selectionSort(T* arr, int size) {

	for (int i = 0; i < size - 1; i++) {

		int minElementIndex = i;

		for (int j = i + 1; j < size; j++) {
		
			if (arr[j] < arr[minElementIndex])
				minElementIndex = j;
		
		}

		if (i != minElementIndex)
			std::swap(arr[i], arr[minElementIndex]);

	}

}

int main() {

	int arr[] = { 4, 1, 3, 9, 8 };

	selectionSort(arr, 5);

	for (int num : arr)
		std::cout << num;

}
