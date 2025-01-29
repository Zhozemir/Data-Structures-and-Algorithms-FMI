#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <forward_list>
#include <stdexcept>

template<typename Key, typename Value, typename Hash = std::hash<Key>>
class Map {

public:

	using Element = std::pair<Key, Value>;

private:

	std::list<Element> data;
	std::vector<std::forward_list<typename std::list<Element>::iterator>> hashTable;

	double maxLoadFactor = 0.75;
	Hash getHash;

	void resize();
	size_t getHashCode(const Key& key) const;
	double loadFactor() const;
 
public:

	Map();
	void add(const Key& key, const Value& value);
	void remove(const Key& key);

	class ConstIterator {

	private:

		typename std::list<Element>::const_iterator currElement;

		ConstIterator(typename std::list<Element>::const_iterator curr) : currElement(curr) {}

		friend class Map;

	public:

		const Element& operator*() const {

			return *currElement;

		}

		const Element* operator->() const {
		
			return &(*currElement);
		
		}

		ConstIterator& operator++() {

			++currElement;
			return (*this);

		}

		ConstIterator operator++(int) {
			
			ConstIterator temp = *this;
			++(*this);
			return temp;
		
		}

		bool operator==(const ConstIterator& other) const {
		
			return currElement == other.currElement;
		
		}

		bool operator!=(const ConstIterator& other) const {
		
			return currElement != other.currElement;
		
		}

	};

	ConstIterator cbegin() const {
	
		return ConstIterator(data.begin());
	
	}

	ConstIterator cend() const {
	
		return ConstIterator(data.cend());
	
	}

	ConstIterator find(const Key& key) const {

		size_t hashCode = getHashCode(key);
		const auto& bucket = hashTable[hashCode];

		auto iter = std::find_if(bucket.begin(), bucket.end(),
			[&key](const auto& it) { return it->first == key; });

		if (iter == bucket.end())
			return cend();

		return ConstIterator(*iter);

	}

};

template<typename Key, typename Value, typename Hash>
Map<Key, Value, Hash>::Map() {

	hashTable.resize(8);

}

template<typename Key, typename Value, typename Hash>
void Map<Key, Value, Hash>::add(const Key& key, const Value& value) {

	if (loadFactor() >= maxLoadFactor)
		resize();

	size_t hashCode = getHashCode(key);
	auto& bucket = hashTable[hashCode];

	auto iter = std::find_if(bucket.begin(), bucket.end(),
		[&key](const auto& it) { return it->first == key; });

	if (iter != bucket.end())
		return;

	data.emplace_back(key, value);
	bucket.push_front(--data.end());

}

template<typename Key, typename Value, typename Hash>
void Map<Key, Value, Hash>::remove(const Key& key) {

	size_t hashCode = getHashCode(key);
	auto& bucket = hashTable[hashCode];

	bucket.remove_if([this, &key](const auto& it) {

		if (it->first == key) {

			data.erase(it);
			return true;

		}

		return false;

		});

}

template<typename Key, typename Value, typename Hash>
size_t Map<Key, Value, Hash>::getHashCode(const Key& key) const {

	return getHash(key) % hashTable.size();
	
}

template<typename Key, typename Value, typename Hash>
double Map<Key, Value, Hash>::loadFactor() const {

	return static_cast<double> (data.size()) / hashTable.size();

}

template <typename Key, typename Value, typename Hash>
void Map<Key, Value, Hash>::resize(){

	size_t newSize = hashTable.size() * 2;
	std::vector<std::forward_list<typename std::list<Element>::iterator>> newHashTable(newSize);

	for (auto it = data.begin(); it != data.end(); ++it) {

		size_t newHashCode = getHashCode(it->first) % newSize;
		newHashTable[newHashCode].push_front(it);

	}

	hashTable = std::move(newHashTable);

}
