// Done by: Isabelle Tan_Group 4_S10257093F

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
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (!isEmpty()) {
        remove(0);
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

        // Traverse the list to find the correct insertion point
        while (current != nullptr && current->item < item) {
            previous = current;
            current = current->next;
        }
        if (previous == nullptr) { // Insert at the beginning
            newNode->next = firstNode;
            firstNode->prev = newNode;
            firstNode = newNode;
        }
        else if (current == nullptr) { // Insert at the end
            previous->next = newNode;
            newNode->prev = previous;
            lastNode = newNode;
        }
        else { // Insert in the middle
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
void DoublyLinkedList<T>::remove(int index) {
    if (index < 0 || index >= size || size == 0) { // Fixed boundary check
        return;
    }

    Node* temp = nullptr;

    if (index == 0) {
        temp = firstNode;
        firstNode = firstNode->next;
        if (firstNode) {
            firstNode->prev = nullptr;
        }
        else {
            lastNode = nullptr;
        }
    }
    else if (index == size - 1) {
        temp = lastNode;
        lastNode = lastNode->prev;
        if (lastNode) {
            lastNode->next = nullptr;
        }
        else {
            firstNode = nullptr;
        }
    }
    else {
        Node* prevNode = firstNode;
        for (int i = 0; i < index - 1; ++i) {
            prevNode = prevNode->next;
        }
        temp = prevNode->next;
        prevNode->next = temp->next;
        if (temp->next) {
            temp->next->prev = prevNode;
        }
    }

    size--;
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

// merge two sorted linked lists
template <typename T>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::merge(Node* left, Node* right, bool (*compare)(T, T)) {
    if (!left) return right;
    if (!right) return left;

    Node* head = nullptr;
    if (compare(left->item, right->item)) {
        head = left;
        left = left->next;
    }
    else {
        head = right;
        right = right->next;
    }

    Node* tail = head;
    while (left && right) {
        if (compare(left->item, right->item)) {
            tail->next = left;
            left = left->next;
        }
        else {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }

    tail->next = left ? left : right;

    return head;
}

// get the node in the middle of the list
template <typename T>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::getMiddle(Node* head) {
    if (!head) return head;

    Node* slow = head;
    Node* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// recursive merge sort 
template <typename T>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::mergeSort(Node* head, bool (*compare)(T, T)) {
    if (!head || !head->next) return head;

    Node* middle = getMiddle(head);
    Node* afterMiddle = middle->next;
    middle->next = nullptr;

    Node* left = mergeSort(head, compare);
    Node* right = mergeSort(afterMiddle, compare);

    return merge(left, right, compare);
}

// merge sort function
template <typename T>
void DoublyLinkedList<T>::mergeSort(bool (*compare)(T, T)) {
    firstNode = mergeSort(firstNode, compare);
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