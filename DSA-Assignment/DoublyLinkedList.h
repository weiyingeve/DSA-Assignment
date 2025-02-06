#pragma once
#include <iostream>
using namespace std;
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

template <typename T> class DoublyLinkedList {
public:
    struct Node {
        T item;
        Node* next;
        Node* prev;

        //default constructor
        Node() : item(), next(nullptr), prev(nullptr) {}
    };
    int size;
    Node* firstNode;
    Node* lastNode;

    // Constructor
    DoublyLinkedList() : firstNode(nullptr), lastNode(nullptr), size(0) {}

    // Destructor
    ~DoublyLinkedList() {
        while (!isEmpty()) {
            remove(firstNode->item);
        }
    }

    // Purpose: Add an item to the back of the list.
    // Precondition: The item must be a valid ItemType value.
    // Postcondition: The item is added to the list. The size of the list increases by 1.
    bool add(const T item) {
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
    bool remove(const T item) {
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
    bool search(const T item) {
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
    bool isEmpty() const {
        return size == 0;
    }

    // Purpose: Check the size of the list.
    // Precondition: None.
    // Postcondition: Returns the number of items currently in the list.
    int getLength() const {
        return size;
    }

    // Purpose: Display all the items in the list.
    // Precondition: None.
    // Postcondition: The items in the list are printed to the console in order.
    void print() const {
        Node* current = firstNode;
        while (current != nullptr) {
            current->item.print();
            current = current->next;
        }
    }
};

#endif //DOUBLYLINKEDLIST.H