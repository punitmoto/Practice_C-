#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct Node {
    int data;
    Node* next;
    Node(int value);
};

class LinkedList {
public:
    Node* head;

    LinkedList();
    ~LinkedList();

    // Adds an element at the end of the list
    void addElement(int value);

    // Displays the list (for testing)
    void display();
};

#endif // LINKEDLIST_H
