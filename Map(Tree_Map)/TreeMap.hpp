#include <iostream>
#include <stack>

template<class Key, class Value, class Compare = std::less<Key>>
class Map {

private:

	struct Node {

		std::pair<Key, Value> data;
		Node* left;
		Node* right;

		Node(const std::pair<Key, Value>& data, Node* left = nullptr, Node* right = nullptr) : data(data), left(left), right(right) {}

	};

	Node* root;
	size_t size;
	Compare comp;

	Node** findMinNode(Node** current);
	Node* copy(Node* current);
	void free(Node* current);

public:

	Map();
	explicit Map(const Compare& comparator);
	Map(const Map& other);
	Map& operator=(const Map& other);
	~Map();

	bool insert(const std::pair<Key, Value>& newData);
	bool insert(const Key& k, const Value& v);
	bool containsKey(const Key& k) const;
	bool remove(const Key& k);
	size_t getSize() const;
	bool empty() const;

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
		const std::pair<Key, Value>& operator*() const {
			
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
		
			ConstIterator temp = *this
			++(*this);
			return temp;
		
		}
		bool operator==(const ConstIterator& other) const {
		
			return nodeStack == other.nodeStack;
		
		}
		bool operator!=(const ConstIterator& other) const {
		
			return !(*this == other);
		
		}

	};

	ConstIterator cbegin() const {
		
		return ConstIterator(root);
	
	}
	ConstIterator cend() const {
	
		return ConstIterator(nullptr);
	
	}

};

template<class Key, class Value, class Compare>
typename Map<Key, Value, Compare>::Node** Map<Key, Value, Compare>::findMinNode(Node** current) {

	while ((*current)->left)
		current = &(*current)->left;

	return current;

}

template<class Key, class Value, class Compare>
typename Map<Key, Value, Compare>::Node* Map<Key, Value, Compare>::copy(Node* current) {

	if (!current)
		return nullptr;

	Node* newNode = new Node(current->data);
	newNode->left = copy(current->left);
	newNode->right = copy(current->right);

	return newNode;

}

template<class Key, class Value, class Compare>
void Map<Key, Value, Compare>::free(Node* current){

	if (!current)
		return;

	free(current->left);
	free(current->right);

	delete current;

}

template<class Key, class Value, class Compare>
Map<Key, Value, Compare>::Map() : root(nullptr), size(0), comp(Compare()) {}

template<class Key, class Value, class Compare>
Map<Key, Value, Compare>::Map(const Compare& comparator) : root(nullptr), size(0), comp(comparator) {}

template<class Key, class Value, class Compare>
Map<Key, Value, Compare>::Map(const Map& other) : root(copy(other.root)), size(other.size), comp(other.comp) {}

template<class Key, class Value, class Compare>
Map<Key, Value, Compare>& Map<Key, Value, Compare>::operator=(const Map& other) {

	if (this != &other) {
		
		free(root);
		root = copy(other.root);
		size = other.size();
		comp = other.comp;
	
	}

	return *this;

}

template<class Key, class Value, class Compare>
Map<Key, Value, Compare>::~Map() {

	free(root);

}

template<class Key, class Value, class Compare>
bool Map<Key, Value, Compare>::insert(const std::pair<Key, Value>& newData) {

	Node** current = &root;
	while (*current) {
	
		if(comp(newData.first, (*current)->data.first))
			current = &(*current)->left;
		else if (comp((*current)->data.first, newData.first))
			current = &(*current)->right;
		else
			return false;

	}

	*current = new Node(newData);
	++size;
		return true;

}

template<class Key, class Value, class Compare>
bool Map<Key, Value, Compare>::insert(const Key& k, const Value& v) {

	return insert(std::make_pair(k, v));

}

template<class Key, class Value, class Compare>
bool Map<Key, Value, Compare>::containsKey(const Key& key) const {

	Node* current = root;

	while (current) {
	
		if (comp(key, current->data.first))
			current = current->left;
		else if (comp(current->data.first, key))
			current = current->right;
		else
			return true;
	
	}

	return false;

}

template<class Key, class Value, class Compare>
bool Map<Key, Value, Compare>::remove(const Key& k) {

	Node** current = &root;

	while (*current) {
	
		if (comp(k, (*current)->data.first))
			current = &(*current)->left;
		else if (comp((*current)->data.first, k))
			current = &(*current)->right;
		else
			break;

	}

	if (!(*current))
		return false;

	Node* toDelete = *current;

	if (!toDelete->left && !toDelete->right)
		*current = nullptr;
	else if (!toDelete->right)
		*current = toDelete->left;
	else if (!toDelete->left)
		*current = toDelete->right;
	else {
	
		Node** rightMin = findMinNode(&toDelete->right);
		*current = *rightMin;
		*rightMin = (*rightMin)->right;
		(*current)->left = toDelete->left;
		(*current)->right = toDelete->right;
	
	}

	delete toDelete;
	--size;

	return true;

}

template<class Key, class Value, class Compare>
size_t Map<Key, Value, Compare>::getSize() const {

	return size;

}

template<class Key, class Value, class Compare>
bool Map<Key, Value, Compare>::empty() const {

	return getSize() == 0;

}




