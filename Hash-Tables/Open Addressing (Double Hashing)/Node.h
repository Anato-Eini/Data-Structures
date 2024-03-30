#ifndef HASH_TABLES_NODE_H
#define HASH_TABLES_NODE_H

#include <utility>

using namespace std;

struct Node{
    pair<int, int> keyValue;
};

struct StackNode{
    int value;
    StackNode* next;
};
#endif //HASH_TABLES_NODE_H
