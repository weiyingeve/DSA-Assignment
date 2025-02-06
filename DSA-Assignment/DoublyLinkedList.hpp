#pragma once
#include <iostream>
#include "Printable.h"
using namespace std;

// Constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : firstNode(nullptr), lastNode(nullptr), size(0) {}

// Destructor
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (!isEmpty()) {
        remove(firstNode->item);
    }
}

// Purpose: Add an item to the back of the list.
// Precondition: The item must be a valid ItemType value.
// Postcondition: The item is added to the list. The size of the list increases by 1.
template <typename T>
bool DoublyLinkedList<T>::add(const T item) {
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

// Purpose: Remove an item at a specified position in the list.
// Precondition: The index must be between 0 and the current size of the list - 1 (inclusive).
// Postcondition: The item at the specified index is removed. The size of the list decreases by 1.
template <typename T>
bool DoublyLinkedList<T>::remove(const T item) {
    if (isEmpty()) {
        cout << "The list is empty, there is nothing to remove." << endl;
        return false;
    }
    Node* current = firstNode;

    while (current != nullptr && current->item < item) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Item not found in list." << endl;
        return false;
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

    //delete current;
    size--;
    //cout << "Item removed from doubly linked list successfully." << endl;
    return true;
}

// Purpose: Check if an item exists in the list.
// Precondition: The list is non-empty (although it works for empty lists as well).
// Postcondition: Returns true if the item exists in the list; otherwise, returns false.
template <typename T>
bool DoublyLinkedList<T>::search(const T item) {
    Node* current = firstNode;

    while (current != nullptr) {
        if (current->item == item) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Purpose: Retrieves an item in the list based on the index.
// Precondition: The list is non-empty (although it works for empty lists as well).
// Postcondition: Returns the item from the list.
template <typename T>
T& DoublyLinkedList<T>::get(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }

    Node* current = firstNode;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current->item;
}

// Purpose: Places an item in the list based on the index.
// Precondition: None.
// Postcondition: Returns if set was successful.
template <typename T>
bool DoublyLinkedList<T>::set(int index, T item) {
    if (index < 0 || index >= size) {
        return false;
    }

    Node* current = firstNode;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    current->item = item;
    return true;
}

// Purpose: Check if the list is empty.
// Precondition: None.
// Postcondition: Returns true if the list is empty; otherwise, returns false.
template <typename T>
bool DoublyLinkedList<T>::isEmpty() const {
    return size == 0;
}

// Purpose: Check the size of the list.
// Precondition: None.
// Postcondition: Returns the number of items currently in the list.
template <typename T>
int DoublyLinkedList<T>::getLength() const {
    return size;
}

// Purpose: Display all the items in the list.
// Precondition: None.
// Postcondition: The items in the list are printed to the console in order.
template <typename T>
void DoublyLinkedList<T>::print() const {
    if constexpr (std::is_base_of_v<Printable, T>) {
        Node* current = firstNode;
        while (current != nullptr) {
            T element = current->item;
            element.print();
            current = current->next;
        }
    }
    else {
        throw std::invalid_argument("T is not Type Printable");
    }
}