#include "DoublyLinkedList.h"
#include <iostream>
using namespace std;

// Constructor
DoublyLinkedList::DoublyLinkedList() : firstNode(nullptr), lastNode(nullptr), size(0) {}

// Destructor
DoublyLinkedList::~DoublyLinkedList() {
	while (!isEmpty()) {
		remove(firstNode->item);
	}
}

// Purpose: Add an item to the list in alphabetical order
// Precondition: The item must be a valid ItemType value.
// Postcondition: The item is added to the list, size of the list increases by 1.
bool DoublyLinkedList::add(const ItemType item) {
	Node* newNode = new Node;
	newNode->item = item;
	newNode->prev = nullptr;
	newNode->next = nullptr;

	if (isEmpty()) {
		firstNode = newNode;
		lastNode = newNode;
	}
	else {
		Node* current = firstNode;
		Node* previous = nullptr;

		while (current != nullptr && current->item < item) {
			previous = current;
			current = current->next;
		}
		if (previous == nullptr) {
			newNode->next = firstNode;
			firstNode->prev = newNode;
			firstNode = newNode;
		}
		else if (current == nullptr) {
			previous->next = newNode;
			newNode->prev = previous;
			lastNode = newNode;
		}
		else {
			previous->next = newNode;
			newNode->prev = previous;
			newNode->next = current;
			current->prev = newNode;
		}
	}

	size++;
	return true;
}

// Purpose: Remove an item.
// Precondition: None.
// Postcondition: The item is removed. The size of the list decreases by 1.
void DoublyLinkedList::remove(const ItemType item) {
	if (isEmpty()) {
		cout << "The list is empty, there is nothing to remove." << endl;
		return;
	}
	Node* current = firstNode;

	while (current != nullptr && current->item != item) {
		current = current->next;
	}

	if (current == nullptr) {
		cout << "Item not found in list." << endl;
		return;
	}

	if (current == firstNode) {
		firstNode = firstNode->next;
		if (firstNode != nullptr) {
			firstNode->prev = nullptr;
		}
		else {
			lastNode = nullptr;
		}
	}
	else if (current == lastNode) {
		lastNode = lastNode->prev;
		lastNode->next = nullptr;
	}
	else {
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}

	delete current;
	size--;
	cout << "Item removed successfully." << endl;
}

// Purpose: Check if an item exists in the list.
// Precondition: The list is non-empty (although it works for empty lists as well).
// Postcondition: Returns true if the item exists in the list; otherwise, returns false.
bool DoublyLinkedList::search(const ItemType item) {
	Node* current = firstNode;

	while (current != nullptr) {
		if (current->item == item) {
			return true;
		}
		current = current->next;
	}
	return false;
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
