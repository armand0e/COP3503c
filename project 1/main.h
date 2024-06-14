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
            T data;
            Node* next = nullptr;
            Node* prev = nullptr;
        public:
            Node();
            void setData(T new_data);
            void setNext(T new_data);
            void setPrev(T new_data);
            T* getNext();
            T* getPrev();
            T* getData();
            
    };
    /////////////////////////// Construction/Destruction ///////////////////////////

    // Constructor
    LinkedList() 
    {

    }
    // Copy Constructor
    LinkedList(const LinkedList<t>& list)
    {

    }
    // Destructor
    ~LinkedList() 
    {

    }

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

    ////////////////////////////////// Insertion //////////////////////////////////
    void AddHead(const T& data)
    {
      Node()
    }
    void AddTail(const T& data)
    {
      
    }
    void AddNodesHead(const T* data, unsigned int count)
    {

    }
    void AddNodesTail(const T* data, unsigned int count)
    {

    }
    void InsertAfter (Node* node, const T& data) 
    {

    } 
    void InsertBefore(Node* node, const T& data)
    {
        
    }
    void InsertAt (const T& data, unsigned int index)
    {

    }
/*==l=l Removal ＝ニニニ*/
bool RemoveHead(); bool RemoveTail();
unsigned int Remove(const T&data); bool RemoveAt (unsigned int index);
void Clear);
/*==== Operators ====*/
const T& operator[](unsigned int index) const;
T& operator[](unsigned int index);
bool operator==(const LinkedList<T>& rhs) const;
LinkedList<T>& operator=(const LinkedList<T>& rhs);
private:
    Node *head = nullptr;
    Node *tail = nullptr;
    int node_count = 0;
    vector<Node*> node_list;
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
