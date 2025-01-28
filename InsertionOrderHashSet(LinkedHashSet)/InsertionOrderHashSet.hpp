#include <iostream>
#include <list>
#include <vector>
#include <forward_list>

template<typename Key, typename Hash = std::hash<Key>>
class Set {

private:

	std::list<Key> data;
	std::vector<std::forward_list<typename std::list<Key>::iterator>> hashTable;

	double maxLoadFactor = 0.75;
	Hash getHash;

	void resize();
	size_t getHashCode(const Key& key) const;
	double loadFactor() const;

public:

	Set();

	void add(const Key& key);
	void remove(const Key& key);

	class ConstIterator {

	private:

		typename std::list<Key>::const_iterator currElement;
		ConstIterator(typename std::list<Key>::const_iterator curr) : currElement(curr) {}
		friend class Set;

	public:

		const Key& operator* ()const{

			return *currElement;

		}

		const Key* operator->() const {

			return &(*currElement);

		}

		ConstIterator& operator++() {

			++currElement;
			return *this;

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
	
		return ConstIterator(data.cbegin());
	
	}

	ConstIterator cend() const {
		
		return ConstIterator(data.cend());
	
	}

	ConstIterator find(const Key& key) const {
	
		size_t hashCode = getHashCode(key);
		const auto& bucket = hashTable[hashCode];

		auto it = std::find_if(bucket.begin(), bucket.end(),
			[&key](auto listIt) { return *listIt == key; });

		if (it == bucket.end())
			return cend();

		return ConstIterator(*it);
	
	}

	


};

	template<typename Key, typename Hash>
	Set<Key, Hash>::Set() {
	
		hashTable.resize(8);
	
	}

	template<typename Key, typename Hash>
	void Set<Key, Hash>::add(const Key& key) {
	
		if (loadFactor() >= maxLoadFactor)
			resize();

		size_t hashCode = getHashCode(key);
		auto& bucket = hashTable[hashCode];

		auto it = std::find_if(bucket.begin(), bucket.end(),
			[&key](auto listIt) { return *listIt == key; });

		if (it != bucket.end())
			return;

		data.push_back(key);
		auto insertedIt = --data.end();
		bucket.push_front(insertedIt);
	
	}

	template<typename Key, typename Hash>
	void Set<Key, Hash>::remove(const Key& key) {
	
		size_t hashCode = getHashCode(key);
		auto& bucket = hashTable[hashCode];

		bucket.remove_if([this, &key](const auto& listIt) {

			if (*listIt == key) {

				data.erase(listIt);
				return true;

			}

			return false;

			});
	
	}

	template<typename Key, typename Hash>
	double Set<Key, Hash>::loadFactor() const {
	
		return static_cast<double>(data.size()) / hashTable.size();
	
	}

	template<typename Key, typename Hash>
	size_t Set<Key, Hash>::getHashCode(const Key& key) const {
	
		return getHash(key) % hashTable.size();
	
	}

	template <typename Key, typename Hash>
	void Set<Key, Hash>::resize(){

		size_t newSize = hashTable.size() * 2;
		std::vector<std::forward_list<typename std::list<Key>::iterator>> newHashTable(newSize);

		for (auto it = data.begin(); it != data.end(); ++it) {

			size_t newHashCode = getHash(*it) % newSize;
			newHashTable[newHashCode].push_front(it);

		}

		hashTable = std::move(newHashTable);

	}

