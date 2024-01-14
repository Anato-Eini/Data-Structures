#ifndef TREES_AND_HEAPS_NODE_H
#define TREES_AND_HEAPS_NODE_H

struct Node{
    int value;
    bool isBlack;
    Node *left, *right, *parent;
};

#endif //TREES_AND_HEAPS_NODE_H
