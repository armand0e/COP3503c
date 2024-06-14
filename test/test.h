///////////////////////////////////////////////////////////////////////////////
///////////////////////ONLY WORK IN THIS FILE//////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <iostream>
using namespace std;

const float scale_factor = 2.0;

template <class T> class ABS {
private:
    unsigned int capacity;
    unsigned int size;
    T* data;

public:
    ABS();
    ABS(int capacity);
    ABS(const ABS &d);
    ABS &operator=(const ABS &d);
    ~ABS();
    void push(T data);
    T pop();
    T peek();
    unsigned int getSize();
    unsigned int getMaxCapacity();
    T* getData();

};

template <class T> ABS<T>::ABS()
{
    this->capacity = 1;
    this->current_size  = 0;
    this->data = new T[this->capacity];
}

template <class T> ABS<T>::ABS(int capacity)
{
    this->capacity = capacity;
    this->current_size = 0;
    this->data = new T[this->capacity];

}

template <class T> ABS<T>::ABS(const ABS &d)
{
    this->capacity = d->capacity;
    this->current_size = d->current_size;
    this->data = new T[this->current_size];
    for(int i = 0; i < this->current_size; i++) this->data[i] = d->data[i];
}

template <class T> ABS<T>::&operator=(const ABS &d)
{
    if(this != &d)
       {
            delete[] this->data;
            this->capacity = d->capacity;
            this->size = d->size;
            this->data = new T[this->capacity];
            for(int i = 0; i < this->current_size;i++) data[i] = d->data[i];
       }
       return *this;
}

template <class T> ABS<T>::~ABS()
{
    delete[] this->data;
}

template <class T> void ABS<T>::push(T data)
{
    // first check size
    if(this->current_size==this->capacity)
    {
        // if at capacity, create a new array with a capacity of 'this->capacity*scale_factor'    
        T *new_data = new T[(int)(this->capacity*scale_factor)];
        for(int i = 0; i < this->current_size; i++) temp[i] = this->data[i];
        this->capacity = this->capacity*scale_factor;
        delete [] this->data;
        this->data = new_data;
        // the original data on the heap is deleted from memory
        // an identical data set is created with twice the size
    }
    this>data[this->current_size] = data;
    this->current_size++;
}

template <class T> T ABS<T>::pop() 
{
    // first check size and make sure its not empty
    // if empty, throw runtime error
    if (this->current_size == 0) throw runtime_error("Error: Stack is empty! Can't pop what doesn't exit!");

    // remove last element  
    T obj = this->data[this->current_size - 1]
    this->current_size--;


}

template <class T> T ABS<T>::peek() 
{

}

template <class T> unsigned int ABS<T>::getSize() 
{

}

template <class T> unsigned int ABS<T>::getMaxCapacity() 
{

}

T* ABS<T>::getData()
{
    return this->data;
}