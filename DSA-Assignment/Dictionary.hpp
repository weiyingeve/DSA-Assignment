#pragma once
#include "Dictionary.h"
#include "DoublyLinkedList.h"
#include "Printable.h"
#include <iostream>
using namespace std;


// Constructor
template <typename KeyType, typename ItemType> Dictionary<KeyType, ItemType>::Dictionary() : size(0) {
    for (int i = 0; i < MAX_SIZE; i++) {
        items[i] = nullptr;
    }
}

// Destructor
template <typename KeyType, typename ItemType> Dictionary<KeyType, ItemType>::~Dictionary() {}

// Purpose: Generate a hash index for a given key.
// Precondition: None.
// Postcondition: Returns an index between 0 and MAX_SIZE - 1.
template <typename KeyType, typename ItemType>
int Dictionary<KeyType, ItemType>::hash(const KeyType& key) const {
    if constexpr (is_integral_v<KeyType>) {
        return key % MAX_SIZE;
    }
    else if constexpr (is_same_v<KeyType, string>) {
        size_t hash_value = 0;
        for (char c : key) {
            hash_value = (hash_value * 31) + c;
        }
        return hash_value % MAX_SIZE;
    }
}

// Purpose: Add a key-value pair to the dictionary.
// Precondition: Key must be unique.
// Postcondition: Adds the key-value pair to the dictionary.
template <typename KeyType, typename ItemType>
bool Dictionary<KeyType, ItemType>::add(const KeyType& newKey, const ItemType& newItem) {
    int index = hash(newKey);  // Compute the hash index

    // Create a new node
    Node* newNode = new Node;
    newNode->key = newKey;
    newNode->item = newItem;
    newNode->next = items[index]; // Point to the current head of the list

    items[index] = newNode; // Insert new node at the head (standard chaining)
    size++;
    return true;
}

// Purpose: Retrieve the value associated with a key.
// Precondition: The key must exist in the dictionary.
// Postcondition: Returns the value associated with the key.
template <typename KeyType, typename ItemType>
ItemType& Dictionary<KeyType, ItemType>::get(const KeyType& key) {
    int index = hash(key);
    Node* current = items[index];

    while (current != nullptr) {
        if (current->key == key) {
            return current->item;  // Now returns a reference
        }
        current = current->next;
    }

    throw std::runtime_error("Key not found");  // Handle missing key properly
}


// Purpose: Retrieve all values in the dictionary.
// Precondition: None.
// Postcondition: Returnsall values in the dictionary.
template <typename KeyType, typename ItemType>
DoublyLinkedList<ItemType*> Dictionary<KeyType, ItemType>::getAllItems() const {
    DoublyLinkedList<ItemType*> itemList;
    for (int i = 0; i < MAX_SIZE; i++) {
        Node* current = items[i];
        while (current != nullptr) {
            itemList.add(&current->item);
            current = current->next;
        }
    }
    return itemList;
}

// Purpose: Retrieve all values in the dictionary and sorts it.
// Precondition: None.
// Postcondition: Returnsall values in the dictionary and sorts it.
template <typename KeyType, typename ItemType>
DoublyLinkedList<ItemType*> Dictionary<KeyType, ItemType>::getAllItemsSorted(bool (*compare)(ItemType*, ItemType*)) const {
    DoublyLinkedList<ItemType*> itemList = getAllItems();
    itemList.sort(compare);
    return itemList;
}

// Purpose: Check if a key exists in the dictionary.
// Precondition: None.
// Postcondition: Returns true if the key exists; otherwise, returns false.
template <typename KeyType, typename ItemType>
bool Dictionary<KeyType, ItemType>::contains(const KeyType& key) const {
    int index = hash(key);
    Node* current = items[index];

    while (current != nullptr) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }

    return false;
}


// Purpose: Check if the dictionary is empty.
// Precondition: None.
// Postcondition: Returns true if the dictionary is empty; otherwise, returns false.
template <typename KeyType, typename ItemType>
bool Dictionary<KeyType, ItemType>::isEmpty() const {
    return size == 0;
}

// Purpose: Check the size of the dictionary.
// Precondition: None.
// Postcondition: Returns the number of items currently in the dictionary.
template <typename KeyType, typename ItemType>
int Dictionary<KeyType, ItemType>::getLength() const {
    return size;
}

// Purpose: Display all key-value pairs in the dictionary.
// Precondition: None.
// Postcondition: Prints all key-value pairs to the console.
template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::print() const {
    if (std::is_same_v<ItemType, Printable>) {
        for (int i = 0; i < MAX_SIZE; i++) {
            Node* current = items[i];
            while (current != nullptr) {
                cout << "Key: " << current->key << "\tItem: " << current->item << endl;
                current = current->next;
            }
        }
    }
    else {
        throw std::invalid_argument("ItemType is not Type Printable");
    }
}

template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::getCapacity() {
    int numElements = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        Node* current = items[i];
        while (current != nullptr) {
            numElements += 1;
            current = current->next;
        }
    }
    cout << numElements << endl;
}