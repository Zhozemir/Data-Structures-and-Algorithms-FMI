#include <iostream>

struct Node {

	int data = 0;
	Node* next = nullptr;

	Node(int data, Node* next = nullptr) : data(data), next(next) {}
};

void pushBack(Node*& resBegin, Node*& resEnd, Node* toAdd) {

	if (!resBegin)
		resBegin = resEnd = toAdd;
	else {

		resEnd->next = toAdd;
		resEnd = toAdd;

	}

}

Node* mergeLists(Node* first, Node* second) {

	Node* resBegin = nullptr;
	Node* resEnd = nullptr;

	while (first, second) {
	
	
		if (first->data < second->data) {
		
			pushBack(resBegin, resEnd, first);
			first = first->next;

		}
		else {
		
			pushBack(resBegin, resEnd, second);
			second = second->next;
		
		}

		if (!first)
			pushBack(resBegin, resEnd, second);
		else
			pushBack(resBegin, resEnd, first);
	
	
	}

	return resBegin;

}

Node* getMid(Node* list) {

	Node* slow = list;
	Node* fast = list->next;

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

void print(const Node* list) {

	while (list) {
	
		if (list->next)
			std::cout << list->data << " -> ";
		else
			std::cout << list->data;

		list = list->next;
	
	}

}

void freeList(Node* list) {

	Node* toDelete = list;

	while (list) {

		Node* next = toDelete->next;
		delete toDelete;
		toDelete = next;

	}

}

int main()
{
	Node* list = new Node(20, new Node(14, new Node(7)));
	list = mergeSort(list);
	print(list);
	freeList(list);
	list = nullptr;
}