#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

template <typename T> class LinkedList {
public:
    // NestedClass
    struct Node {
        T data;
        Node* next = nullptr;
        Node* prev = nullptr;
        Node(T data) : data(data), next(nullptr), prev(nullptr) {}
    };
    ////////////////////////////////// Behaviors //////////////////////////////////
    void PrintForward()  {
        // Iterator through all of the nodes and print out their values, one a time
        if (node_count > 0) {
            // set loop starting point
            Node* currentNode = head;
            // break loop when currentNode points to nullptr
            while (currentNode != nullptr) {
                // print the data
                cout << currentNode->data << endl;
                // point the currentNode to the next node
                currentNode = currentNode->next;                
            }
        }
    }
    void PrintReverse() const {
        //Exactly the same as PrintForward, except completely the opposite.
        if (node_count > 0) {
            // set loop starting point
            Node* currentNode = tail;
            // break loop when currentNode points to nullptr
            while (currentNode != nullptr) {
                // print the data
                cout << currentNode->data << endl;
                // point the currentNode to the next node
                currentNode = currentNode->prev;                
            }
        }
    }
    /* void PrintForwardRecursive(const Node* node) const {
        This function takes in a pointer to a Node—a starting node. From
        that node, recursively visit each node that follows, in forward order,
        and print their values. This function MUST be implemented using
        recursion, or tests using it will be worth no points. Check your
        textbook for a reference on recursion.

    }
    void PrintReverseRecursive(const Node* node) const {
        //Same deal as PrintForwardRecursive, but in reverse.

    } */

    ////////////////////////////////// Accessors //////////////////////////////////
    unsigned int NodeCount() const {
        return node_count;
    }
    /* void FindAll(vector<Node*>& outData, const T& value) const {

    }
    const Node* Find(const T& data) const {

    }
    const Node* GetNode(unsigned int index) const {

    }
    Node* GetNode(unsigned int index) {

    }
    Node* Head() {
        return head;
    }
    //const Node* Head() const {
    //    return const head;
    }
    Node* Tail() {
        return tail;
    }
    //const Node* Tail() const {
    //    return tail;
    } */

    ////////////////////////////////// Insertion //////////////////////////////////
    void AddHead(const T& newdata) {
        
        Node newHead = new Node;
        Node* newHeadptr = &newHead;
        newHead->data = newdata;
        newHead->next = head;
        head->prev = newHeadptr;
        head = newHeadptr;
        if (tail == nullptr) tail = newHeadptr;
        node_count++;
    }
     void AddTail(const T& newdata) {
        Node newTail = new Node;
        Node* newTailptr = &newTail;
        newTail->data = newdata;
        newTail->prev = tail;
        tail->next = newTailptr;
        tail = newTailptr;
        if (head == nullptr) head = newTailptr;
        node_count++;
    }
    void AddNodesHead(const T* data, unsigned int count) {
        for (int i = count - 1; i >= 0; i--) {
            AddHead(data[i]);
            node_count++;
        }
    }
    void AddNodesTail(const T* data, unsigned int count) {
        for (int i = 0; i < count; i++) {
            AddTail(data[i]);
            node_count++;
        }
    }
    /* void InsertAfter (Node* node, const T& data) {

    } 
    void InsertBefore(Node* node, const T& data) {
        
    }
    void InsertAt (const T& data, unsigned int index) {

    } */

    /////////////////////////////////// Removal ///////////////////////////////////
    /* bool RemoveHead(); bool RemoveTail() {
        
    }
    int Remove(const T&data) {

    } 
    bool RemoveAt (unsigned int index) {

    } */
    void Clear() {
        Node* currentNode = Head();
        Node* nextNode = nullptr;
        while (currentNode!=nullptr) {
            nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }
    }

    ////////////////////////////////// Operators //////////////////////////////////
    /* const T& operator[](unsigned int index) const {

    }
    T& operator[](unsigned int index) {

    }
    bool operator==(const LinkedList<T>& rhs) const {

    }
    LinkedList<T>& operator=(const LinkedList<T>& rhs) {

    } */

    /////////////////////////// Construction/Destruction ///////////////////////////
    LinkedList() {
        node_count = 0;
        head = nullptr;
        tail = nullptr;
    }
    /* LinkedList(const LinkedList<T>& list) {               
        node_count = list->node_count;
        Node* currentlistNode = list->head;
        while (currentlistNode != nullptr) {
            // create a new node identical to the current list node
            AddTail(currentlistNode->data);
            // point the currentlistNode to the next list node
            currentlistNode = currentlistNode->next;
        }
        delete currentlistNode;
        head = Head();
        tail = Tail();

    } */
    ~LinkedList() {
        if (node_count > 0) {
            // set loop starting point
            Node* currentNode = head;
            
            while (node_count > 0) {
                // store the pointer to the next node
                Node* nextNode = currentNode->next;
                // deconstruct current node
                delete currentNode->data;
                delete currentNode->next;
                delete currentNode->prev;
                // point the currentNode to the next node
                currentNode = nextNode;
                delete nextNode;
                // break if you reach nullptr
                if (currentNode == nullptr) break;
                node_count--;
            }
        }
    }

private:
    Node* head = nullptr;
    Node* tail = nullptr;
    unsigned int node_count;
};


