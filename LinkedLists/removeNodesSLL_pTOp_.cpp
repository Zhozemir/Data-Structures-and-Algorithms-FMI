#include <iostream>

struct Node {

	int data;
	Node* next;

	Node(int data, Node* next = nullptr) : data(data), next(next) {}

};

template <typename Predicate>
Node* removeNodes(Node* head, Predicate predicate) {

	Node** current = &head;

	while (*current) {
	
		if (predicate((*current)->data)) {

			Node* temp = *current;
			*current = (*current)->next;
			delete temp;

		}
		else
			current = &(*current)->next;
	
	}

	return head;

}

void printList(Node* head) {

	Node* current = head;

	while (current) {
	
		if(current->next)
			std::cout << current->data << " -> ";
		else
			std::cout << current->data;

		current = current->next;
	
	}

	std::cout << std::endl;

}

void freeList(Node* list) {

	Node* current = list;

	while (current) {
	
		Node* toDelete = current;
		current = current->next;
		delete toDelete;
	
	}

}

int main() {

	Node* head = new Node (1);
	head->next = new Node (2);
	head->next->next = new Node (3);
	head->next->next->next = new Node (4);
	head->next->next->next->next = new Node (5);

	std::cout << "Original list: ";
	printList(head);

	head = removeNodes(head, [](int data) {return data % 2 == 0; });

	std::cout << "List after removing even: ";

	printList(head);

	std::cout << "Removing all: ";

	head = removeNodes(head, [](int) {return true; });

	freeList(head);

}