#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template <typename T> 
class LinkedList {
public:
    //////////////////////////////// Nested Class /////////////////////////////////
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(T data) : data(data), next(nullptr), prev(nullptr) {}
    };

    ////////////////////////////////// Behaviors //////////////////////////////////
    void PrintForward() const;
    void PrintReverse() const;
    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;

    ////////////////////////////////// Accessors //////////////////////////////////
    unsigned int NodeCount() const;
    void FindAll(vector<Node*>& outData, const T& value) const;
    const Node* Find(const T& data) const;
    Node* Find(const T& data);
    const Node* GetNode(unsigned int index) const;
    Node* GetNode(unsigned int index);
    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;

    ////////////////////////////////// Insertion //////////////////////////////////
    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);
    void InsertAfter (Node* node, const T& data);
    void InsertBefore(Node* node, const T& data);
    void InsertAt (const T& data, unsigned int index);

    /////////////////////////////////// Removal ///////////////////////////////////
    bool RemoveHead(); 
    bool RemoveTail();
    unsigned int Remove(const T&data); 
    bool RemoveAt (unsigned int index);
    void Clear();

    ////////////////////////////////// Operators //////////////////////////////////
    const T& operator[](unsigned int index) const;
    T& operator[](unsigned int index);
    bool operator==(const LinkedList<T>& rhs) const;
    LinkedList<T>& operator=(const LinkedList<T>& rhs);

    ////////////////////////// Construction/Destruction ///////////////////////////
    LinkedList();
    LinkedList(const LinkedList<T>& list);
    ~LinkedList();

private:
    Node *head;
    Node *tail;
    unsigned int node_count;
};

/*------------------------- FUNCTION DEFINITIONS --------------------------------*/

//////////////////////////////////// Behaviors ////////////////////////////////////
template <typename T>
void LinkedList<T>::PrintForward() const {
    // Traverse the list and print each node's data
    Node* current = this->head;
    while (current->next != nullptr) {
        cout << current->data << endl;
        current = current->next;
    }
    cout << current->data << endl;
}
template <typename T>
void LinkedList<T>::PrintReverse() const {
    // Traverse the list and print each node's data
    Node* current = this->tail;
    while (current->prev != nullptr) {
        cout << current->data << endl;
        current = current->prev;
    }
    cout << current->data << endl;
}
template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {
    if (node != nullptr) {
        cout << node->data << endl;
        PrintForwardRecursive(node->next);
    }
}
template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {
    if (node != nullptr) {
        cout << node->data << endl;
        PrintReverseRecursive(node->prev);
    }
}

//////////////////////////////////// Accessors ////////////////////////////////////
template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
    return node_count;
}
template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            outData.push_back(current);
        }
        current = current->next;
    }
}
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
    if (index >= node_count) {
        throw out_of_range("Error: List index out of range!");
    }
    Node* current = head;
    for (unsigned int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current;
}
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
    if (index >= node_count) {
        throw out_of_range("Error: List index out of range!");
    }
    Node* current = head;
    for (unsigned int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current;
}
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
    return head;
}
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
    return head;
}
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
    return tail;
}
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
    return tail;
}

//////////////////////////////////// Insertion ////////////////////////////////////
template <typename T>
void LinkedList<T>::AddHead(const T& data) {
    Node* newNode = new Node(data);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } 
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    node_count++;
}
template <typename T>
void LinkedList<T>::AddTail(const T& data) {
    Node* newNode = new Node(data);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } 
    else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    node_count++;
}
template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
    for (int i = count - 1; i >= 0; i--) {
        AddHead(data[i]);
    }
}
template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
    for (int i = 0; i < count; i++) {
        AddTail(data[i]);
    }
}
template <typename T>
void LinkedList<T>::InsertAfter (Node* node, const T& data) {
    Node* newNode = new Node(data);
    // if given node is the tail
    if (node == tail) {
        node->next = newNode;
        newNode->prev = node;
        tail = newNode;
    }
    // otherwise
    else {
        Node* temp = node->next;
        node->next = newNode;
        newNode->prev = node;
        newNode->next = temp;
        temp->prev = newNode;
    }
    node_count++;
}
template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {
    Node* newNode = new Node(data);
    // if given node is the head
    if (node == head) {
        node->prev = newNode;
        newNode->next = node;
        head = newNode;
    }
    // otherwise
    else {
        Node* temp = node->prev;
        node->prev = newNode;
        newNode->next = node;
        newNode->prev = temp;
        temp->next = newNode;
    }
    node_count++;
}
template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
    // if index is larger than node count, throw an error
    if (index > node_count) { 
        throw out_of_range("Error: List index out of range.");
    }
    // if index is the head
    if (index == 0) {
        AddHead(data);
    } 
    // if index is the tail
    else if (index == node_count) { 
        AddTail(data);
    } 
    // otherwise
    else {
        Node* node = GetNode(index);
        InsertBefore(node, data);
    }
}

///////////////////////////////////// Removal /////////////////////////////////////
template <typename T>
bool LinkedList<T>::RemoveHead() {
    if (head == nullptr) return false;
    Node* temp = head;
    head = head->next;
    if (head != nullptr) head->prev = nullptr;
    else tail = nullptr;
    delete temp;
    node_count--;
    return true;
} 
template <typename T>
bool LinkedList<T>::RemoveTail() {
    if (tail == nullptr) return false;
    Node* temp = tail;
    tail = tail->prev;
    if (tail != nullptr) tail->next = nullptr;
    else head = nullptr;
    delete temp;
    node_count--;
    return true;
}
template <typename T>
unsigned int LinkedList<T>::Remove(const T& data) {
    unsigned int count = 0;
    Node* current = head;
    while (current != nullptr) {
        if (current->data == data) {
            Node* toDelete = current;
            if (current->prev) current->prev->next = current->next;
            if (current->next) current->next->prev = current->prev;
            if (current == head) head = current->next;
            if (current == tail) tail = current->prev;
            current = current->next;
            delete toDelete;
            node_count--;
            count++;
        } else {
            current = current->next;
        }
    }
    return count;
}
template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
    if (index >= node_count) return false;
    Node* toDelete = GetNode(index);
    if (toDelete->prev) toDelete->prev->next = toDelete->next;
    if (toDelete->next) toDelete->next->prev = toDelete->prev;
    if (toDelete == head) head = toDelete->next;
    if (toDelete == tail) tail = toDelete->prev;
    delete toDelete;
    node_count--;
    return true;
}
template <typename T>
void LinkedList<T>::Clear() {
    // Traverse the list and delete each node to free memory
    Node* current = head;
    while(current != nullptr) {
        // assign temp to current
        Node* temp = current;
        // assign current to next
        current = current->next;
        // delete current
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    node_count = 0;
}

//////////////////////////////////// Operators ////////////////////////////////////
template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
    return GetNode(index)->data;
}
template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
    return GetNode(index)->data;
}
template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
    if (this == &rhs) {
        return true; // same object
    }

    if (node_count != rhs.node_count) {
        return false; // different sizes
    }

    Node* current_self = head;
    Node* current_rhs = rhs.head;

    while (current_self != nullptr) {
        if (current_self->data != current_rhs->data) {
            return false; // different data
        }
        current_self = current_self->next;
        current_rhs = current_rhs->next;
    }

    return true; // all nodes are identical
}
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
    if (this != &rhs) {  // Self-assignment check
        // first delete all nodes
        Clear();
        // copy each node from the provided list
        Node* current = rhs.head;
        while (current != nullptr) {
            AddTail(current->data);
            current = current->next;
        }
    }
    return *this;
}

//////////////////////////// Construction/Destruction /////////////////////////////
template <typename T>
LinkedList<T>::LinkedList() {
    node_count = 0;
    head = nullptr;
    tail = nullptr;
}
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    node_count = 0;
    head = nullptr;
    tail = nullptr;
    // copy each node from the provided list
    Node* current = list.head;
    while (current != nullptr) {
        AddTail(current->data);
        current = current->next;
    }
}
template <typename T>
LinkedList<T>::~LinkedList() {
    Clear();
}
