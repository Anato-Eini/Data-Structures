#ifndef HASH_TABLES_STACK_H
#define HASH_TABLES_STACK_H
#include "Node.h"
class Stack {
    StackNode* head;
    int size;
public:
    Stack(): head(new StackNode{0, nullptr}), size(0){}
    void push(int);
    int pop();
    int peek();
    [[nodiscard]] bool isEmpty() const;
};

#endif //HASH_TABLES_STACK_H