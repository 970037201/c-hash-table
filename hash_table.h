#pragma once

//A semi-static simple hash table implementation - 
//It cannot resize it's amount of buckets, that is fixed (Future project todo maybe?)
//It uses linked lists for buckets, as well as for collision resolution
//It uses the new and delete operators, as well as the == and != operators, for the given class.

//No license, use at your own liking, and risk.
//Not tested to be thread safe (Probably not)

template <class K>
struct hash {//Overload struct for custom hashes.
	virtual size_t operator()(const K& key) const {};
};

/*Example usage of overloading hash for your uses. Here we just cast our value to size_t.
template <>
struct hash<int> {
	size_t operator()(const int& key) const {
		return size_t(key);
	}
};
*/

template <class K, class V, size_t S>
class hash_table {
	struct elem {
		const K key;
		V val;
		elem* next;
	} *arr[S];//A static array of dynamic linked lists (array of buckets)
public:
	hash_table() : arr() {}//initialize to zero
	hash_table(const hash_table<K, V, S>&) = delete;//This class has pointers, cannot be easily copied.
	hash_table(hash_table<K, V, S>&&) = delete;//This class has pointers cannot be easily copied. 
	~hash_table();//delete all elements which were allocated by new
	//add a value, mapped to a key, replaces value with same key, you can only have unique keys in hashmap.
	void insert(const K& key, const V& val);
	V& operator[](const K& key) {//Access element by reference, for changing value - Do not access non existent element.
		elem* ptr = arr[key % S];
		for (; ptr->key != key; ptr = ptr->next);
		return ptr->val;
	}
	bool contains(const K& key);//Returns true if table contains element
	void remove(const K& key);//If element exists in hash table, it will be removed.
};

template<class K, class V, size_t S>
inline hash_table<K, V, S>::~hash_table() {
	for (size_t bucket = 0; bucket < S; ++bucket) {
		for (elem* temp, *ptr = arr[bucket]; ptr; ptr = temp) {
			temp = ptr->next;
			delete ptr;
		}
	}
}

template<class K, class V, size_t S>
inline void hash_table<K, V, S>::insert(const K& key, const V& val) {
	if (contains(key)) {
		operator[](key) = val;
	}
	else {
		arr[key % S] = new elem{ key, val, arr[key % S] };
	}
}

template<class K, class V, size_t S>
inline bool hash_table<K, V, S>::contains(const K& key) {
	elem* ptr = arr[key % S];
	if (ptr) {
		for (; ptr->key != key && ptr->next; ptr = ptr->next);
		return ptr->key == key;
	}
	return 0;
}

template<class K, class V, size_t S>
inline void hash_table<K, V, S>::remove(const K& key) {
	elem* ptr = arr[key % S];
	if (ptr) {
		if (ptr->key == key) {
			elem* temp = ptr->next;
			delete ptr;
			arr[key % S] = temp;
		}
		else {
			while (ptr->next) {
				if (ptr->next->key == key) {
					elem* temp = ptr->next->next;
					delete ptr->next;
					ptr->next = temp;
					break;
				}
				ptr = ptr->next;
			}
		}
	}
}
