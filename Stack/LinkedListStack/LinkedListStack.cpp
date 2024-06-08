#ifndef LINKEDLISTSTACK_CPP
#define LINKEDLISTSTACK_CPP

#include "LinkedListStack.h"

#include <algorithm>

template <typename Object>
LinkedListStack<Object>::LinkedListStack() : head(new Node{{}, nullptr}), _size(0) {}

template <typename Object>
void LinkedListStack<Object>::push(Object&& object)
{
    head->next = new Node{std::move(object), head->next};
    _size++;
}

template <typename Object>
void LinkedListStack<Object>::push(Object& object)
{
    head->next = new Node{object, head->next};
    _size++;
}

template <typename Object>
Object& LinkedListStack<Object>::pop()
{
    Object & object = head->next->element;
    const Node* node = head->next;
    head->next = head->next->next;
    delete node;
    _size--;
    return object;
}

template <typename Object>
Object& LinkedListStack<Object>::peek()
{
    return head->next->element;
}

template <typename Object>
size_t LinkedListStack<Object>::size()
{
    return _size;
}

template <typename Object>
bool LinkedListStack<Object>::isEmpty()
{
    return size() == 0;
}

#endif