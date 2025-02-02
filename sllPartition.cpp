#include <iostream>

struct Node {

	int data;
	Node* next = nullptr;
	Node(int value, Node* ptr = nullptr) : data(value), next(ptr) {}

};

void pushBack(Node*& begin, Node*& end, Node* toAdd) {

	if (begin == nullptr)
		begin = end = toAdd;
	else {
	
		end->next = toAdd;
		end = toAdd;
		
	}

}

template<class PredicateType>
Node* partition(Node* list, const PredicateType& pred) {

	Node* trueListBegin = nullptr;
	Node* trueListEnd = nullptr;

	Node* falseListBegin = nullptr;
	Node* falseListEnd = nullptr;

	while (list != nullptr) {
	
		if (pred(list->data))
			pushBack(trueListBegin, trueListEnd, list);
		else
			pushBack(falseListBegin, falseListEnd, list);

		list = list->next;
	
	}

	if (trueListEnd) {
	
		trueListEnd->next = falseListBegin;
	
	}

	if (falseListEnd)
		falseListEnd->next = nullptr;

	return trueListBegin != nullptr ? : trueListBegin : falseListBegin;

}

void printList(Node* iter) {

	while (iter) {
	
		std::cout << iter->data;
		iter = iter->next;
	
	}

}

void freeList(Node* iter) {

	while (iter) {
	
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	
	}

}