#pragma once
#include "DoublyLinkedList.h"
#include <iostream>
#include "Printable.h"
using namespace std;

// Constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : firstNode(nullptr), lastNode(nullptr), size(0) {}

// Destructor
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {}

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

    size--;
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

    if (current == nullptr) {
        throw std::runtime_error("Attempted to dereference a null pointer.");
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

template <typename T>
void DoublyLinkedList<T>::sort(bool (*compare)(T, T)) {
    if (!firstNode || !firstNode->next) return; // Already sorted or empty

    firstNode = mergeSort(firstNode, compare);

    // Update lastNode after sorting
    lastNode = firstNode;
    while (lastNode->next) {
        lastNode = lastNode->next;
    }
}

// Merge Sort Helper Function
template <typename T>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::mergeSort(Node* head, bool (*compare)(T, T)) {
    if (!head || !head->next) {
        return head;
    }

    Node* mid = split(head);
    Node* left = mergeSort(head, compare);
    Node* right = mergeSort(mid, compare);

    return merge(left, right, compare);
}

// Function to split a doubly linked list into two halves
template <typename T>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::split(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* mid = slow->next;
    slow->next = nullptr;
    if (mid) mid->prev = nullptr;
    return mid;
}

// Merge two sorted linked lists
template <typename T>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::merge(Node* first, Node* second, bool (*compare)(T, T)) {
    if (!first) return second;
    if (!second) return first;

    if (compare(first->item, second->item)) {
        first->next = merge(first->next, second, compare);
        if (first->next) first->next->prev = first;
        first->prev = nullptr;
        return first;
    }
    else {
        second->next = merge(first, second->next, compare);
        if (second->next) second->next->prev = second;
        second->prev = nullptr;
        return second;
    }
}

//for comparison reasons
template <typename T>
bool DoublyLinkedList<T>::operator<(const DoublyLinkedList<T>& other) const {
    if (!this->firstNode) return true;  // Empty list is "smaller"
    if (!other.firstNode) return false; // Non-empty is "bigger"
    return *(this->firstNode->item) < *(other.firstNode->item);  // Compare first elements
}

template <typename T>
void DoublyLinkedList<T>::sortDescending(bool (*compare)(T, T)) {
    if (!firstNode || !firstNode->next) return; // Already sorted or empty

    firstNode = mergeSort(firstNode, compare);

    // Update lastNode after sorting
    lastNode = firstNode;
    while (lastNode->next) {
        lastNode = lastNode->next;
    }
}


template <typename T>
bool DoublyLinkedList<T>::compareDescending(T a, T b) {
    return a > b; // Sorting in descending order
}