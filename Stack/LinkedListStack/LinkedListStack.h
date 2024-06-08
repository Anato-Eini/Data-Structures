#ifndef LINKEDLISTSTACK_H
#define LINKEDLISTSTACK_H

#include "../AbstractStack.h"

template <typename Object>
class LinkedListStack final : AbstractStack<Object>
{
    struct Node
    {
        Object element;
        Node* next;
    };

    Node* head;

    size_t _size{};

public:
    LinkedListStack();

    void push(Object&& object) override;

    void push(Object& object) override;

    Object& pop() override;

    Object& peek() override;

    [[nodiscard]] bool isEmpty() override;

    [[nodiscard]] size_t size() override;

    ~LinkedListStack() override = default;
};

#include "LinkedListStack.cpp"

#endif //LINKEDLISTSTACK_H
