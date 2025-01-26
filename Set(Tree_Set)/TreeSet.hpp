#include <iostream>
#include <stack>

template<class T, typename Compare = std::less<T>>
class TreeSet {

private: 

	struct Node {

		T data;
		Node* left;
		Node* right;

		Node(const T& data, Node* left = nullptr, Node* right = nullptr) : data(data), left(left), right(right) {}

	};

	Node* root = nullptr;

	size_t size = 0;
	Compare comp;

	Node** findMinNode(Node** root);
	Node* copy(Node* current);
	void free(Node* current);

public:

	TreeSet() = default;
	explicit TreeSet(const Compare& comparator) : comp(comparator) {}
	TreeSet(const TreeSet<T, Compare>& other);
	TreeSet<T, Compare>& operator=(const TreeSet<T, Compare>& other);
	~TreeSet();

	bool insert(const T& data);
	bool contains(const T& data) const;
	bool remove(const T& data);

	size_t getSize() const;
	bool isEmpty() const;

	class ConstIterator {

	private:

		std::stack<Node*> nodeStack;

		void pushLeft(Node* node) {

			while (node) {

				nodeStack.push(node);
				node = node->left;

			}

		}

	public:

		ConstIterator(Node* root = nullptr) {
		
			pushLeft(root);
		
		}

		const T& operator*() const {
		
			return nodeStack.top()->data;
		
		}

		ConstIterator& operator++() {
		
			Node* node = nodeStack.top();
			nodeStack.pop();

			if (node->right)
				pushLeft(node->right);

			return *this;
		
		}

		ConstIterator operator++(int) {
		
			ConstIterator old = *this;
			++(*this);
			return old;
		
		}

		bool operator!=(const ConstIterator& other) const {
		
			return nodeStack != other.nodeStack;
		
		}

		bool operator==(const ConstIterator& other) const {
		
			return nodeStack == other.nodeStack;
		
		}

	};

	ConstIterator cbegin() const {

		return ConstIterator(root);

	}

	ConstIterator cend() const {
	
		return ConstIterator(nullptr);
	
	}

};

template<class T, typename Compare>
bool TreeSet<T, Compare>::insert(const T& data) {

	Node** current = &root;

	while (*current) {
	
		if (comp(data, (*current)->data))
			current = &(*current)->left;
		else if (comp((*current)->data, data))
			current = &(*current)->right;
		else
			return false;
	
	}

	*current = new Node(data);
	size++;
	return true;

}

template<class T, typename Compare>
bool TreeSet<T, Compare>::contains(const T& data) const {

	Node* current = root;

	while (current) {
	
		if (comp(data, current->data))
			current = current->left;
		else if (comp(current->data, data))
			current = current->right;
		else
			return true;
		
	}

	return false;

}

template<class T, typename Compare>
typename TreeSet<T, Compare>::Node** TreeSet<T, Compare>::findMinNode(Node** root) {

	Node** current = root;

	while ((*current)->left)
		current = &(*current)->left;

	return current;
	
}

template<class T, typename Compare>
bool TreeSet<T, Compare>::remove(const T& data) {
	
	Node** current = &root;

	while (*current) {
	
		if (comp(data, (*current)->data))
			current = &(*current)->left;
		else if (comp((*current)->data, data))
			current = &(*current)->right;
		else
			break;
	
	}

	if (!(*current))
		return false;

	Node* toDelete = *current;

	if (!(*current)->left && !(*current)->right)
		*current = nullptr;
	else if (!(*current)->right)
		*current = (*current)->left;
	else if (!(*current)->left)
		*current = (*current)->right;
	else {
	
		Node** rightMin = findMinNode(&(*current)->right);
		*current = *rightMin;
		*rightMin = (*rightMin)->right;

		(*current)->left = toDelete->left;
		(*current)->right = toDelete->right;
	
	}

	delete toDelete;
	size--;

	return true;

}

template<class T, typename Compare>
size_t TreeSet<T, Compare>::getSize() const {

	return size;

}

template<class T, typename Compare>
bool TreeSet<T, Compare>::isEmpty() const {

	return getSize() == 0;

}

template<class T, typename Compare>
typename TreeSet<T, Compare>::Node* TreeSet<T, Compare>::copy(Node* current) {

	if (!current)
		return nullptr;

	Node* res = new Node(current->data);
	res->left = copy(current->left);
	res->right = copy(current->right);

	return res;

}

template<class T, typename Compare>
void TreeSet<T, Compare>::free(Node* current) {

	if (!current)
		return;

	free(current->left);
	free(current->right);

	delete current;

}

template<class T, typename Compare>
TreeSet<T, Compare>::TreeSet(const TreeSet<T, Compare>& other) : comp(other.comp) {

	root = copy(other.root);
	size = other.size;

}

template<class T, typename Compare>
TreeSet<T, Compare>& TreeSet<T, Compare>::operator=(const TreeSet<T, Compare>& other) {
	
	if (this != other) {
		
		free(root);
		root = copy(other.root);
		size = other.size;
		comp = other.comp;
	
	}

	return *this;

}

template<class T, typename Compare>
TreeSet<T, Compare>::~TreeSet() {

	free(root);

}

