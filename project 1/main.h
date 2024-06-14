#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <typename T> class LinkedList
{
public:
    // nested class
    class Node
    {
        private:
            T* self = nullptr;
            T* next = nullptr;
            T* prev = nullptr;
        public:
            Node();
            void setSelf(T* data);
            void setNext(T* data);
            void setPrev(T* data);
            T* getNext();
            T* getPrev();
            T* getSelf();
            
    };

    
    /////////////////////////// Construction/Destruction ///////////////////////////

    // Constructor
    LinkedList();
    // Copy Constructor
    LinkedList(const LinkedList &d);
    // Destructor
    ~LinkedList();

    ////////////////////////////////// Behaviors //////////////////////////////////

    void PrintForward() const;
    // Iterator through all of the nodes and print out their values, one a time.
    void PrintReverse() const;
    //Exactly the same as PrintForward, except completely the opposite.
    void PrintForwardRecursive(const Node* node) const;
    /*This function takes in a pointer to a Node—a starting node. From
    that node, recursively visit each node that follows, in forward order,
    and print their values. This function MUST be implemented using
    recursion, or tests using it will be worth no points. Check your
    textbook for a reference on recursion.*/
    void PrintReverseRecursive(const Node* node) const;
    //Same deal as PrintForwardRecursive, but in reverse.

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

private:
    Node *head = nullptr;
    Node *tail = nullptr;
    Node *next = nullptr;
    int node_count = 0;
};





/*
class Example 
{
    public:
        struct NestedClass
        {
          int x, y, z;
          int Function();  
        };
    private:
        NestedClass *somePtr;
        NestedClass myData[5];
        float values[10];
};
*/
