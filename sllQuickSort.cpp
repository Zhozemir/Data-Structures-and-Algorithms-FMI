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
std::pair<Node*, Node*>partition(Node* list, const PredicateType& pred) {

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

	if (trueListEnd)
		trueListEnd->next = nullptr;

	if (falseListEnd)
		falseListEnd->next = nullptr;

	return std::make_pair(trueListBegin, falseListBegin);

}

std::pair<Node*, Node*> concatLists(Node* leftBegin, Node* leftEnd, Node* rightBegin, Node* rightEnd) {

	if (leftBegin)
		return std::make_pair(rightBegin, rightEnd);

	if (rightBegin)
		return std::make_pair(leftBegin, leftEnd);

	leftEnd->next = rightBegin;

	return std::make_pair(leftBegin, rightEnd);

}

std::pair<Node*, Node*> quickSort(Node* list){

	if (!list || !list->next)
		return std::make_pair(list, list);

	int pivot = list->data;

	auto partitionResults = partition(list, [pivot](int el) {return el < pivot; });

	Node* pivotPtr = partitionResults.second;

	auto leftToConcat = quickSort(partitionResults.first);
	auto rightToConcat = quickSort(partitionResults.second->next);

	pivotPtr->next = rightToConcat.first;
	rightToConcat.first = pivotPtr;

	if (!rightToConcat.second)
		rightToConcat.second = pivotPtr;

	return concatLists(leftToConcat.first, leftToConcat.second, rightToConcat.first, rightToConcat.second);

}