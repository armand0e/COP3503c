#pragma once
#include <iostream>
using namespace std;
#include <stdexcept>

template <typename T>
class LinkedList {
private:
    // Nested Node class
    class Node {
    public:
        T data;
        Node* next;

        Node(T data) : data(data), next(nullptr) {}
    };

    Node* head;

public:
    LinkedList();
    ~LinkedList();

    void append(T data);
    Node* getNode(int index) const;
    void printList() const;
    void remove(int index);
    void addToHead(T data);
};

// TODO: Implement the LinkedList constructor
template <typename T>
LinkedList<T>::LinkedList(){
      // TODO: Create an empty list
      head = nullptr;
}


// Destructor to clean up memory
template <typename T>
LinkedList<T>::~LinkedList() {
    // TODO: Traverse the list and delete each node to free memory
    Node* current = head;
    while(current != nullptr){
        Node* temp = current;
        current = current->next;
        delete temp;
    }

}

// Method to add a new node at the end of the list
template <typename T>
void LinkedList<T>::append(T data) {
    // TODO: Create a new node with the given data and add it to the end of the list
    Node* newNode = new Node(data);
    
    // If the list is empty
    if(head == nullptr){
        head = newNode;
        return;
    }
    // If the list is not empty
    Node* current = head;
    while(current->next != nullptr){
        current = current->next;
    }
    current->next = newNode;
}

// Method to get a node at a specific index
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getNode(int index) const {
    // TODO: Traverse the list to find the node at the given index and throw out of range exception otherwise
    // if the list is empty
    if(head == nullptr){
        throw out_of_range("out of range index (head == nullptr)\n");
    }
    // if the list is not empty
    int counter = 1;
    Node* current = head;
    while(current != nullptr){
        if(counter == index){
            return current;
        }else{
            current = current->next;
            counter++;
        }
    }
    throw out_of_range("out of range index!\n");
}

// Method to print the list
template <typename T>
void LinkedList<T>::printList() const {
    // TODO: Traverse the list and print each node's data add "->" between nodes and last node points to nullptr
    Node* traverse = head;

    while(traverse->next != nullptr) {
        
        cout << traverse->data << " -> ";
        traverse = traverse->next;
    }
    cout << traverse->data << endl;
}