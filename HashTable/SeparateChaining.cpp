#include <iostream>
#include <vector>
#include <forward_list>
#include <list>

template<typename Key, typename Value>
class HashMap {

private:

	typedef std::pair<Key, Value> element;

	std::list<element> data;

	std::vector<std::forward_list<typename std::list<element>::iterator>> hashTable;

	double maxLoadFactor = 8;

	size_t getHashCode(const Key& key) const {

	return std::hash<Key>{}(key) % hashTable.size();

	}

	void resize() {
	
		size_t htSize = hashTable.size();
		hashTable.clear();
		hashTable.resize(htSize * 2);

		for (auto it = data.begin(); it != data.end(); it++)
			hashTable[getHashCode(it->first)].push_front(it);
	
	}

public:

	HashMap() {

		hashTable.resize(2);

	}

	double loadFactor() const {
	
		return static_cast<double>(data.size()) / hashTable.size();
	
	}

	void add(const Key& key, const Value& value) {

		if (loadFactor() >= maxLoadFactor)
			resize();

		size_t hashCode = getHashCode(key);
		auto& bucket = hashTable[hashCode];

		auto iter = std::find_if(bucket.begin(), bucket.end(),

			[&key](const typename std::list<element>::iterator& currIter) {

				return currIter->first == key;

			});

		if (iter != bucket.end())
			return;

		data.push_back({ key, value });
		bucket.push_front(--data.end());

	}

	void remove(const Key& key) {

		size_t hashCode = getHashCode(key);

		auto& bucket = hashTable[hashCode];

		bucket.remove_if([this, key](const typename std::list<element>::iterator& currIter) {

			if (key == currIter->first) {

				data.erase(currIter);
				return true;

			}

			return false;

			});

	}

	int getValue(const Key& key) const {
	
		size_t hashCode = getHashCode(key);

		auto& bucket = hashTable[hashCode];
	
		auto iter = std::find_if(bucket.begin(), bucket.end(),

			[&key](const typename std::list<element>::iterator& currIter) {

				return currIter->first == key;

			});

		if (iter == bucket.end())
			throw std::out_of_range("Element not found!");

		return (*iter)->second;
			
	}

	void print() const {
	
	for (const auto& iter : data)
		std::cout << iter.first << " " << iter.second << std::endl;

	}

};

int main() {

	HashMap<std::string, int> hm;

	hm.add("Georgi", 20);
	hm.add("Ivan", 13);
	hm.add("Petur", 1);
	hm.add("Nikolay", 5);

	hm.print();

	hm.remove("Ivan");

	hm.print();

	std::cout << hm.getValue("Georgi");

}
