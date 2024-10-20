#include <iostream>

template <class T>
void Merge(T* firstArr, size_t firstSize, T* secondArr, size_t secondSize, T* resultArr) {

	size_t firstInd = 0;
	size_t secondInd = 0;
	size_t resultInd = 0;

	while (firstInd < firstSize && secondInd < secondSize) {

		resultArr[resultInd++] = (firstArr[firstInd] < secondArr[secondInd] ? firstArr[firstInd++] : secondArr[secondInd++]);

	}

	while (firstInd < firstSize)
		resultArr[resultInd++] = firstArr[firstInd++];

	while (secondInd < secondSize)
		resultArr[resultInd++] = secondArr[secondInd++];
	
}

template<class T>
void MergeSortStep(T* pArr, size_t size, T* pBuffer) {
	
	if (size <= 1)
		return;

	size_t middle = size / 2;

	MergeSortStep(pArr, middle, pBuffer);

	MergeSortStep(pArr + middle, size - middle, pBuffer + middle);

	Merge(pArr, middle, pArr + middle, size - middle, pBuffer);

	for (size_t i = 0; i < size; i++)
		pArr[i] = pBuffer[i];

}

template <class T>
void MergeSort(T* pArr, size_t size) {

	if (!pArr || size == 0)
		return;

	T* pBuffer = new T[size];

	MergeSortStep(pArr, size, pBuffer);

	delete[] pBuffer;

}

int main() {

	constexpr int size = 8;

	int arr[] = { 8, 6, 1, 4, 5, 3, 1, 9 };
	MergeSort(arr, size);

	for (int i = 0; i < size; i++)
		std:: cout << arr[i] << " ";

}