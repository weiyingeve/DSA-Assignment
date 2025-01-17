#include "DoublyLinkedList.h"
#include <iostream>
using namespace std;

// Constructor
DoublyLinkedList::DoublyLinkedList() : firstNode(nullptr), lastNode(nullptr), size(0) {}

// Destructor
DoublyLinkedList::~DoublyLinkedList() {
	while (!isEmpty) {
		remove(1);
	}
}

// Purpose: Add an item to the back of the list. (may not be necessary will edit ltr)
// Precondition: The item must be a valid ItemType value.
// Postcondition: The item is appended to the end of the list. The size of the list increases by 1.
bool DoublyLinkedList::add(ItemType item) {
	Node* newNode = new Node;
	newNode->item = item;
	newNode->next = nullptr;
	newNode->prev = nullptr;

	if (isEmpty) {
		firstNode = newNode;
		lastNode = newNode;
	}
	else {
		lastNode->next = newNode;
		newNode->prev = lastNode;
		lastNode = newNode;
	}
	size++;
	return true;
}

// Purpose: Add an item at a specified position in the list (insert). (need to update)
// Precondition: The index must be between 0 and the current size of the list (inclusive).
// Postcondition: The item is inserted at the specified index. The size of the list increases by 1.
bool DoublyLinkedList::add(int index, ItemType item) {
	if (index > 0 && index <= size) {
		Node* newNode = new Node;
		newNode->item = item;
		newNode->next = nullptr;
		newNode->prev = nullptr;

		if (index == 1) {
			newNode->next = firstNode;
			firstNode->prev = newNode;
			firstNode = newNode;
		}

	}
}

// Purpose: Remove an item at a specified position in the list.
// Precondition: The index must be between 0 and the current size of the list - 1 (inclusive).
// Postcondition: The item at the specified index is removed. The size of the list decreases by 1.
void DoublyLinkedList::remove(int index) {

}

// Purpose: Get an item at a specified position of the list (retrieve).
// Precondition: The index must be between 0 and the current size of the list - 1 (inclusive).
// Postcondition: The item at the specified index is returned. The list remains unchanged.
ItemType DoublyLinkedList::get(int index) {

}

// Purpose: Check if the list is empty.
// Precondition: None.
// Postcondition: Returns true if the list is empty; otherwise, returns false.
bool DoublyLinkedList::isEmpty() {
	return size == 0;
}

// Purpose: Check the size of the list.
// Precondition: None.
// Postcondition: Returns the number of items currently in the list.
int DoublyLinkedList::getLength() {
	return size;
}

// Purpose: Display all the items in the list.
// Precondition: None.
// Postcondition: The items in the list are printed to the console in order.
void DoublyLinkedList::print() {
	Node* current = firstNode;
	while (current != nullptr) {
		cout << current->item << endl;
		current = current->next;
	}
	cout << endl;
}
