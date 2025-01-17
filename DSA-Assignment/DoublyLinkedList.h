#pragma once
using namespace std;
#include <string>;

typedef string ItemType;

class DoublyLinkedList {
private:
    struct Node {
        ItemType item;
        Node* next;
        Node* prev;
    };
    Node* firstNode;
    Node* lastNode;
    int size;

public:
    // Constructor
    DoublyLinkedList();

    // Destructor
    ~DoublyLinkedList();

    // Purpose: Add an item to the back of the list.
    // Precondition: The item must be a valid ItemType value.
    // Postcondition: The item is appended to the end of the list. The size of the list increases by 1.
    bool add(const ItemType item);

    // Purpose: Remove an item at a specified position in the list.
    // Precondition: The index must be between 0 and the current size of the list - 1 (inclusive).
    // Postcondition: The item at the specified index is removed. The size of the list decreases by 1.
    void remove(const ItemType item);

    // Purpose: Check if an item exists in the list.
    // Precondition: The list is non-empty (although it works for empty lists as well).
    // Postcondition: Returns true if the item exists in the list; otherwise, returns false.
    bool search(const ItemType item);

    // Purpose: Check if the list is empty.
    // Precondition: None.
    // Postcondition: Returns true if the list is empty; otherwise, returns false.
    bool isEmpty();

    // Purpose: Check the size of the list.
    // Precondition: None.
    // Postcondition: Returns the number of items currently in the list.
    int getLength();

    // Purpose: Display all the items in the list.
    // Precondition: None.
    // Postcondition: The items in the list are printed to the console in order.
    void print();
};
