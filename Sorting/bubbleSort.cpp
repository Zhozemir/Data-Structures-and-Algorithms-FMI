//#include <iostream>
//
//template <class T>
//void bubbleSort(T* arr, unsigned len) {
//
//
//	unsigned end = len - 1;
//
//	for (int i = 0; i < len; i++) {
//	
//		unsigned lastSwappedIndex = 0;
//
//		for (int j = 0; j < end; j++) {
//		
//			if (arr[j] > arr[j + 1]) {
//			
//				std::swap(arr[j], arr[j + 1]);
//				lastSwappedIndex = j;
//			
//			}
//		
//		
//		}
//	
//		end = lastSwappedIndex;
//		if (lastSwappedIndex == 0)
//			return;
//
//	
//	}
//
//}
//
//int main() {
//
//	int arr[] = { 5, 1, 3, 9, 4, 3 };
//
//	bubbleSort<int>(arr, 6);
//
//	for (int num : arr)
//		std::cout << num;
//
//}