#pragma once
#include <iostream>
using namespace std;
#include "Printable.h"

template <typename T> class DoublyLinkedList {
private:
    int size;
public:
    struct Node {
        T item;
        Node* next;
        Node* prev;

        //default constructor
        Node() : item(), next(nullptr), prev(nullptr) {}
    };
    Node* firstNode;
    Node* lastNode;

    Node* mergeSort(Node* head, bool (*compare)(T, T));
    Node* merge(Node* first, Node* second, bool (*compare)(T, T));
    Node* getMiddle(Node* head);

    // Constructor
    DoublyLinkedList();

    // Destructor
    ~DoublyLinkedList();

    //retrieve first node
    Node* getFirstNode() { return firstNode; }

    // Purpose: Add an item to the back of the list.
    // Precondition: The item must be a valid ItemType value.
    // Postcondition: The item is added to the list. The size of the list increases by 1.
    bool add(const T item);

    // Purpose: Remove an item at a specified position in the list.
    // Precondition: The index must be between 0 and the current size of the list - 1 (inclusive).
    // Postcondition: The item at the specified index is removed. The size of the list decreases by 1.
    void remove(int index);

    // Purpose: Check if an item exists in the list.
    // Precondition: The list is non-empty (although it works for empty lists as well).
    // Postcondition: Returns true if the item exists in the list; otherwise, returns false.
    bool search(const T item);

    // Purpose: Retrieves an item in the list based on the index.
    // Precondition: The list is non-empty (although it works for empty lists as well).
    // Postcondition: Returns the item from the list.
    T& get(int index);

    // Purpose: Places an item in the list based on the index.
    // Precondition: None.
    // Postcondition: Returns if set was successful.
    bool set(int index, T item);

    // Purpose: Check if the list is empty.
    // Precondition: None.
    // Postcondition: Returns true if the list is empty; otherwise, returns false.
    bool isEmpty() const;

    // Purpose: Check the size of the list.
    // Precondition: None.
    // Postcondition: Returns the number of items currently in the list.
    int getLength() const;

    // Purpose: Display all the items in the list.
    // Precondition: None.
    // Postcondition: The items in the list are printed to the console in order.
    void print() const;

    //merge sort function
    void mergeSort(bool (*compare)(T, T));

    //for comparison reasons
    bool operator<(const DoublyLinkedList<T>& other) const;

    void sortDescending(bool (*compare)(T, T));
    static bool compareDescending(T a, T b);
};

#include "DoublyLinkedList.hpp";