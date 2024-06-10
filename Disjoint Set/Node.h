#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node
{
    Node* element;
    T name;
    size_t size{};

    Node() : element(nullptr), name((T){}), size(1) {}

    explicit Node(const T & name) : element(nullptr), name(name), size(1){}
};


#endif //NODE_H
