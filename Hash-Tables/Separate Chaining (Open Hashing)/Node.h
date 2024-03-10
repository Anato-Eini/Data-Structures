#ifndef HASH_TABLES_NODE_H
#define HASH_TABLES_NODE_H
#include <utility>
struct Node{
    std::pair<int, int> pair;
    int height;
    Node* left, *right, *parent;
};

struct StackNode{
    int value;
    StackNode* next;
};
#endif //HASH_TABLES_NODE_H
