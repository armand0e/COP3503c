#pragma once
#include <iostream>
#include <vector>
#include <string>
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
//void PrintForwardRecursive(const Node* node) const;
//void PrintReverseRecursive(const Node* node) const;

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
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
    if (index >= node_count) {
        throw out_of_range("out of range index!");
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
        throw out_of_range("out of range index!");
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
        node_count++;
    }
}
template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
    for (int i = 0; i < count; i++) {
        AddTail(data[i]);
        node_count++;
    }
}
//void InsertAfter (Node* node, const T& data);
//void InsertBefore(Node* node, const T& data);
//void InsertAt (const T& data, unsigned int index);

///////////////////////////////////// Removal /////////////////////////////////////
//bool RemoveHead(); 
//bool RemoveTail();
//unsigned int Remove(const T&data); 
//bool RemoveAt (unsigned int index);
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
    head = nullptr;  // Set head to nullptr after clearing
    tail = nullptr;  // Set tail to nullptr after clearing
    node_count = 0;  // Reset node_count to 0 after clearing
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
        return true; // Same object
    }

    if (node_count != rhs.node_count) {
        return false; // Different sizes
    }

    Node* current_self = head;
    Node* current_rhs = rhs.head;

    while (current_self != nullptr) {
        if (current_self->data != current_rhs->data) {
            return false; // Found differing data
        }
        current_self = current_self->next;
        current_rhs = current_rhs->next;
    }

    return true; // All nodes match
}
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
    if (this != &rhs) {  // Self-assignment check
        // Clear current contents
        Clear();
        // Deep copy each node from the provided list
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
    // Initialize members
    node_count = 0;
    head = nullptr;
    tail = nullptr;

    // Deep copy each node from the provided list
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
