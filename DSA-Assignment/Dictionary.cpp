//#include "Dictionary.h"
//using namespace std;
//#include <iostream>
//
//// constructor
//template <typename KeyType, typename ItemType>
//Dictionary<KeyType, ItemType>::Dictionary() : size(0) {
//	for (int i = 0; i < MAX_SIZE; i++) {
//		items[i] = nullptr;
//	}
//}
//
//// destructor
//template <typename KeyType, typename ItemType>
//Dictionary<KeyType, ItemType>::~Dictionary() {
//	for (int i = 0; i < MAX_SIZE; i++) {
//		Node* current = items[i];
//		while (current != nullptr) {
//			Node* temp = current;
//			current = current->next;
//			delete temp;
//		}
//	}
//}
//
//// Purpose: Generate a hash index for a given key.
//// Precondition: None.
//// Postcondition: Returns an index between 0 and tableSize - 1.
//template <typename KeyType, typename ItemType>
//int Dictionary<KeyType, ItemType>::hash(const KeyType& key) const {
//	return key % MAX_SIZE;
//}
//
//// Purpose: Add a key-value pair to the dictionary.
//// Precondition: Key must be unique.
//// Postcondition: Adds the key-value pair, or updates the value if the key already exists.
//template <typename KeyType, typename ItemType>
//bool Dictionary<KeyType, ItemType>::add(const KeyType& newKey,const ItemType& newItem) {
//	int index = hash(newKey);
//
//	Node* current = items[index];
//
//	while (current != nullptr) {
//		if (current->key == newKey) {
//			current->item = newItem;
//			return true;
//		}
//		current = current->next;
//	}
//
//	Node* newNode = new Node;
//	newNode->key = newKey;
//	newNode->item = newItem;
//	newNode->next = items[index];
//
//	items[index] = newNode;
//	size++;
//	return true;
//}
//
//// Purpose: Remove a key-value pair from the dictionary.
//// Precondition: The key must exist in the dictionary.
//// Postcondition: Removes the key-value pair if it exists, returns true if successful.
//template <typename KeyType, typename ItemType>
//bool Dictionary<KeyType, ItemType>::remove(const KeyType& key) {
//	int index = hash(key);
//	Node* current = items[index];
//	Node* previous = nullptr;
//
//	while (current != nullptr) {
//		if (current->key == key) {
//			if (previous == nullptr) {
//				items[index] = current->next;
//			}
//			else {
//				previous->next = current->next;
//			}
//			delete current;
//			size--;
//			return true;
//		}
//		previous = current;
//		current = current->next;
//	}
//	return false;
//}
//// Purpose: Retrieve the value associated with a key.
//// Precondition: The key must exist in the dictionary.
//// Postcondition: Returns the value associated with the key.
//template <typename KeyType, typename ItemType>
//ItemType Dictionary<KeyType, ItemType>::get(const KeyType& key) const {
//	int index = hash(key);
//	Node* current = items[index];
//
//	while (current != nullptr) {
//		if (current->key == key)
//		{
//			return current->item;
//		}
//		current = current->next;
//	}
//	throw runtime_error("Key not found.");
//}
//
//// Purpose: Check if a key exists in the dictionary.
//// Precondition: None.
//// Postcondition: Returns true if the key exists; otherwise, returns false.
//template <typename KeyType, typename ItemType>
//bool Dictionary<KeyType, ItemType>::contains(const KeyType& key) const{
//	int index = hash(key);
//	Node* current = items[index];
//
//	while (current != nullptr) {
//		if (current->key == key) {
//			return true;
//		}
//		current = current->next;
//	}
//	return false;
//}
//
//// Purpose: Check if the dictionary is empty.
//// Precondition: None.
//// Postcondition: Returns true if the dictionary is empty; otherwise, returns false.
//template <typename KeyType, typename ItemType>
//bool Dictionary<KeyType, ItemType>::isEmpty() const{
//	return size == 0;
//}
//
//// Purpose: Check the size of the dictionary.
//// Precondition: None.
//// Postcondition: Returns the number of items currently in the dictionary.
//template <typename KeyType, typename ItemType>
//int Dictionary<KeyType, ItemType>::getLength() const{
//	return size;
//}
//
//// Purpose: Display all key-value pairs in the dictionary.
//// Precondition: None.
//// Postcondition: Prints all key-value pairs to the console.
//template <typename KeyType, typename ItemType>
//void Dictionary<KeyType, ItemType>::print() const{
//	for (int i = 0; i < MAX_SIZE; i++) {
//		Node* current = items[i];
//		while (current != nullptr) {
//			cout << "Key: " << current->key << "\tItem: " << current->item << endl;
//			current = current->next;
//		}
//	}
//}