// Done by: Rena Soong_Group4_S10258053C

// Dictionary.h - - Specification of Dictionary ADT
#pragma once
#include <string>
#include <iostream>
#include "Printable.h"
#include "DoublyLinkedList.h"
using namespace std;

const int MAX_SIZE = 101;

template <typename KeyType, typename ItemType> class Dictionary {
private:
    struct Node {
        KeyType key;       // search key
        ItemType item;    // data item
        Node* next;        // pointer to the next item

        //default constructor
        Node() : key(), item(), next(nullptr) {}
    };

    Node* items[MAX_SIZE]; // array of pointers to linked lists
    int size;              // number of items in the Dictionary
public:
    // Constructor
    Dictionary();

    // Destructor
    ~Dictionary();

    // Purpose: Generate a hash index for a given key.
    // Precondition: None.
    // Postcondition: Returns an index between 0 and MAX_SIZE - 1.
    int hash(const KeyType& key) const;

    // Purpose: Add a key-value pair to the dictionary.
    // Precondition: Key must be unique.
    // Postcondition: Adds the key-value pair to the dictionary.
    bool add(const KeyType& newKey, const ItemType& newItem);

    // Purpose: Remove a key-value pair from the dictionary.
    // Precondition: The key must exist in the dictionary.
    // Postcondition: Removes the key-value pair if it exists, returns true if successful.
    bool remove(const KeyType& key);

    // Purpose: Retrieve the value associated with a key.
    // Precondition: The key must exist in the dictionary.
    // Postcondition: Returns the value associated with the key.
    ItemType& get(const KeyType& key);

    // Purpose: Retrieve all values in the dictionary.
    // Precondition: None.
    // Postcondition: Returnsall values in the dictionary.
    DoublyLinkedList<ItemType*> getAllItems() const;

    // Purpose: Retrieve all values in the dictionary and sorts it.
    // Precondition: None.
    // Postcondition: Returnsall values in the dictionary and sorts it.
    DoublyLinkedList<ItemType*> getAllItemsSorted(bool (*compare)(ItemType*, ItemType*)) const;

    // Purpose: Check if a key exists in the dictionary.
    // Precondition: None.
    // Postcondition: Returns true if the key exists; otherwise, returns false.
    bool contains(const KeyType& key) const;


    // Purpose: Check if the dictionary is empty.
    // Precondition: None.
    // Postcondition: Returns true if the dictionary is empty; otherwise, returns false.
    bool isEmpty() const;

    // Purpose: Check the size of the dictionary.
    // Precondition: None.
    // Postcondition: Returns the number of items currently in the dictionary.
    int getLength() const;

    // Purpose: Display all key-value pairs in the dictionary.
    // Precondition: None.
    // Postcondition: Prints all key-value pairs to the console.
    void print() const;

    //for testing purposes
    void getCapacity();
};
#include "Dictionary.hpp"