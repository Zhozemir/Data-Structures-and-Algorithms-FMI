#include <iostream>

template <class T>
void insertionSort(T* arr, int length) {

	for (int i = 1; i < length; i++) {
	
		T element = arr[i];
		int index = i - 1;
		while (index >= 0 && arr[index] > element) {
		
			arr[index + 1] = arr[index];
			index--;
		
		}

		arr[index + 1] = element;
	
	
	}

}

int main() {

	int arr[] = { 3, 1, 4, 1, 9, 5 };

	insertionSort<int>(arr, 6);

	for (int num : arr)
		std::cout << num;

}