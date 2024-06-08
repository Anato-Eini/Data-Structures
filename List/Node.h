#ifndef NODE_H
#define NODE_H

template <typename Object>
struct Node
{
    Object data;
    Node *prev;
    Node *next;

    explicit Node(const Object & d = Object{}, Node * p = nullptr, Node *n = nullptr) : data(d), prev(p), next(n) {}

    explicit Node(Object && d, Node * p = nullptr, Node * n = nullptr) : data(d), prev(p), next(n) {}
};
#endif //NODE_H
