#include <iostream>
#include <vector>

template<typename Key, typename Value>
class HashMap {

	struct Node {

		Key key;
		Value value;
		bool isDeleted = false;
		bool isTaken = false;

		Node() = default;
		Node(Key key, Value value, bool isTaken, bool isDeleted) : key(key), value(value), isTaken(isTaken), isDeleted(isDeleted) {}


	};

	std::vector<Node> data;
	size_t jumpValue;
	size_t size = 0;
	double maxLoadFactor = 0.5;

	size_t getHashCode(const Key& key) const {

		return std::hash<Key>{}(key) % data.size();

	}

	void resize() {

		std::vector<Node> newData(2 * data.size());

		for (auto it = data.begin(); it != data.end(); it++) {

			if (it->isTaken && !it->isDeleted) {

				size_t index = std::hash<Key>{}(it->key) % newData.size();
				size_t startIndex = index;

				do {

					if (!newData[index].isTaken) {

						newData[index] = Node(std::move(it->key), std::move(it->value), true, false);
						break;

					}

					index = (index + jumpValue) % newData.size();

				} while (startIndex != index);


			}

		}

		data = std::move(newData);

	}

public:

	HashMap() {

		data.resize(100);
		jumpValue = 3;

	}

	double loadFactor() {
	
		return static_cast<double>(size) / data.size();
	
	}

	void add(const Key& key, const Value& value) {
	
		if (loadFactor() > maxLoadFactor)
			resize();

		size_t index = getHashCode(key);
		size_t startIndex = index;

		do {
		
			if (!data[index].isTaken || data[index].isDeleted) {

				data[index] = Node(key, value, true, false);
				size++;
				return;

			}
			else if (data[index].key == key)
				return;

			index = (index + jumpValue) % data.size();
		
		} while (startIndex != index);
	
	}

	Value getValue(const Key& key) const {
	
		size_t index = getHashCode(key);
		size_t startIndex = index;

		do {
			
			if (!data[index].isTaken)
				break;
			else if (!data[index].isDeleted && data[index].key == key)
				return data[index].value;

			index = (index + jumpValue) % data.size();
		
		} while (startIndex != index);
	

		throw std::out_of_range("Element not found!");
	
	}

	void remove(const Key& key) {
	
		size_t index = getHashCode(key);
		size_t startIndex = index;

		do {
		
			if (!data[index].isTaken)
				return;
			else if (!data[index].isDeleted && data[index].key == key) {
			
				data[index].isDeleted = true;
				size--;

				return;
			
			}

			index = (index + jumpValue) % data.size();
		
		} while (startIndex != index);
	
	}

	void print() const { 
	
		for (const auto& iter : data) {

			if (iter.isTaken && !iter.isDeleted)
				std::cout << iter.key << " " << iter.value << std::endl;

		}

	}

};

int main() {

	HashMap<std::string, int> hm;

	hm.add("Georgi", 10);
	hm.add("Ivan", 12);
	hm.add("Nikolay", 24);

	hm.print();

	std::cout << std::endl;

	hm.remove("Ivan");

	hm.print();

	std::cout << std::endl;

	std::cout << hm.getValue("Georgi");

}
