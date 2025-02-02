#include <iostream>

struct Node{

	int data = 0;
	Node* next = nullptr;

	Node(int data, Node* next = nullptr) : data(data), next(next) {}

};

void pushBack(Node*& resultBegin, Node*& resultEnd, Node* toAdd) {
	
	if (!resultBegin)
		resultBegin = resultEnd = toAdd;
	else {
	
		resultEnd->next = toAdd;
		resultEnd = toAdd;
	
	}
	
}

Node* mergeLists(Node* first, Node* second) {

	Node* resultBegin = nullptr;
	Node* resultEnd = nullptr;

	while (first && second) {
	
		if (first->data < second->data) {
		
			pushBack(resultBegin, resultEnd, first);
			first = first->next;
		
		}
		else {
		
			pushBack(resultBegin, resultEnd, second);
			second = second->next;
		
		}
		
	}

	if (!first)
		pushBack(resultBegin, resultEnd, second);
	else
		pushBack(resultBegin, resultEnd, first);


	return resultBegin;

}

Node* getMid(Node* list) {

	Node* slow = list;
	Node* fast = list;

	while (fast && fast->next) {
	
		slow = slow->next;
		fast = fast->next->next;
	
	}

	return slow;

}

Node* mergeSort(Node* list) {

	if (!list || !list->next)
		return list;

	Node* mid = getMid(list);

	Node* left = list;
	Node* right = mid->next;
	mid->next = nullptr;

	left = mergeSort(left);
	right = mergeSort(right);

	return mergeLists(left, right);

}