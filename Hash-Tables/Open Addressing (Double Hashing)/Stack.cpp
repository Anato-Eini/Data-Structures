#include "Stack.h"

Stack::Stack(): head(new StackNode{0, nullptr}), size(0){}

Stack* Stack::push(int value) {
    head->next = new StackNode{value, head->next};
    size++;
    return this;
}

int Stack::pop() {
    int valueOfTop = head->next->value;
    StackNode* dNode = head->next;
    head->next = head->next->next;
    size--;
    delete dNode;
    return valueOfTop;
}

int Stack::peek() {
    return head->next->value;
}

[[nodiscard]] bool Stack::isEmpty() const {
    return size == 0;
}

Stack::~Stack() {
    while(!isEmpty())
        pop();
    delete head;
}