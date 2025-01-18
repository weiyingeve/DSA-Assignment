// Dictionary.h - - Specification of Dictionary ADT
#include<string>
#include<iostream>
using namespace std;

const int MAX_SIZE = 101;
typedef string ItemType;
typedef string KeyType;

struct Node
{
	KeyType  key;   // search key
	ItemType item;	// data item
	Node* next;	// pointer pointing to next item
};

class Dictionary
{
private:
	Node* items[MAX_SIZE];
	int  size;			// number of items in the Dictionary

public:
	// constructor
	Dictionary();

	// destructor
	~Dictionary();

	// Purpose: Generate a hash index for a given key.
	// Precondition: None.
	// Postcondition: Returns an index between 0 and tableSize - 1.
	int hash(const KeyType key) const;

	// Purpose: Add a key-value pair to the dictionary.
	// Precondition: Key must be unique.
	// Postcondition: Adds the key-value pair, or updates the value if the key already exists.
	bool add(const KeyType newKey, ItemType newItem);

	// Purpose: Remove a key-value pair from the dictionary.
	// Precondition: The key must exist in the dictionary.
	// Postcondition: Removes the key-value pair if it exists, returns true if successful.
	void remove(const KeyType key);

	// Purpose: Retrieve the value associated with a key.
	// Precondition: The key must exist in the dictionary.
	// Postcondition: Returns the value associated with the key.
	ItemType get(const KeyType key) const;

	// Purpose: Check if a key exists in the dictionary.
	// Precondition: None.
	// Postcondition: Returns true if the key exists; otherwise, returns false.
	bool contains(const KeyType& key);

	// Purpose: Check if the dictionary is empty.
	// Precondition: None.
	// Postcondition: Returns true if the dictionary is empty; otherwise, returns false.
	bool isEmpty();

	// Purpose: Check the size of the dictionary.
	// Precondition: None.
	// Postcondition: Returns the number of items currently in the dictionary.
	int getLength();

	// Purpose: Display all key-value pairs in the dictionary.
	// Precondition: None.
	// Postcondition: Prints all key-value pairs to the console.
	void print();
};
