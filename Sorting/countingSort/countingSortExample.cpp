#include <iostream>

struct Student {

	std::string name;
	int grade;

};

void countingSortForGrades(Student* arr, size_t len) {

	const size_t GRADES_COUNT = 5;

	size_t* countArr = new size_t[GRADES_COUNT]{ 0 };

	for (int i = 0; i < len; i++)
		countArr[arr[i].grade - 2]++;

	for (int i = 1; i < GRADES_COUNT; i++)
		countArr[i] += countArr[i - 1];

	Student* result = new Student[len];

	for (int i = len - 1; i >= 0; i--) {
	
		Student& currStudent = arr[i];
		size_t index = --countArr[currStudent.grade - 2];
		result[index] = currStudent;
	
	}

	for (int i = 0; i < len; i++)
		arr[i] = result[i];

	delete[] result;
	delete[] countArr;

}

int main() {

	const size_t COUNT_STUDENTS = 5;
	
	Student arr[COUNT_STUDENTS] = {

		{"Georgi", 4},
		{"Alex", 6},
		{"Ivan", 4},
		{"Vladimir", 5},
		{"Maq", 5}

	};

	countingSortForGrades(arr, COUNT_STUDENTS);

	for (auto& student : arr) {
	
		std::cout << student.name << " - " << student.grade << std::endl;
	
	}
	
}