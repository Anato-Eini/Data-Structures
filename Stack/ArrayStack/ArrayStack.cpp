#ifndef ARRAYSTACK_CPP
#define ARRAYSTACK_CPP
#include "ArrayStack.h"

template <typename Object>
ArrayStack<Object>::ArrayStack() : index(0){}

template <typename Object>
void ArrayStack<Object>::push(Object&& object)
{
    vector_.emplace_back(object);

    index++;
}

template <typename Object>
void ArrayStack<Object>::push(Object& object)
{
    vector_.emplace_back(object);

    index++;
}

template <typename Object>
Object& ArrayStack<Object>::pop()
{
    return vector_[++index];
}

template <typename Object>
bool ArrayStack<Object>::isEmpty()
{
    return size() == 0;
}

template <typename Object>
size_t ArrayStack<Object>::size()
{
    return index;
}

template <typename Object>
Object& ArrayStack<Object>::peek()
{
    return vector_[index - 1];
}

#endif
