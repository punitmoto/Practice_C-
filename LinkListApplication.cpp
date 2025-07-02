#ifndef APPLICATION_H
#define APPLICATION_H

#include<iostream>
#include<unordered_set>

struct Node {
    Node* next;
    int data;
    Node(int value):data(value), next(nullptr){};
};

class LinkList {
public:
    Node* head;

    LinkList():head(nullptr) {};
    ~LinkList() {
        if (head == nullptr)
            return;

        Node* current = head;
        while(current != nullptr){
            Node* temp = current;
            current = current->next;
            delete temp;
        }    
    }

    void addElementAtEnd(int value) {
        Node* newNode = new Node(value);

        if(head == nullptr) {
            head = newNode;
            return;
        }

        Node* currentNode = head;
        while(currentNode->next!=nullptr) {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;        
    }

    bool deleteElement(Node* node) {

        if(head == nullptr) {
            return false;
        }

        Node* currentNode = head;
        if(head == node) {
            delete currentNode;
            head = nullptr;
            return true;
        }

        while(currentNode != nullptr) {
            if(currentNode->next == node) {
                currentNode->data = node->data;
                currentNode->next = node->next;
                delete node;
                return true;
            }
            currentNode = currentNode->next;
        }        
    }

    bool deleteDup() {
        if(head == nullptr) {
            std::cout<<"EMpty List" <<std::endl;
            return false;
        }

        std::unordered_set<int> seen;
        Node* currentNode = head;
        Node* prev = nullptr;

        while(currentNode!= nullptr) {
            if(seen.find(currentNode->data)!= seen.end()) {
                // found the dup
                prev->next = currentNode->next;
                delete currentNode;
                currentNode = prev->next;
            }
            else {
                seen.insert(currentNode->data);
                prev = currentNode;
                currentNode = currentNode->next;
            }
        }
        return true;
    }

    void displayList() {
        Node* current = head;

        while(current!= nullptr) {
            std::cout << current->data <<"->";
            current = current->next;
        }
        std::cout << "null" << std::endl;
    }
};

int main() {
    LinkList list;

    list.addElementAtEnd(10);
    list.addElementAtEnd(20);
    list.displayList();
    return 0;
}

#endif

