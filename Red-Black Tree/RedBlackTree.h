#ifndef TREES_AND_HEAPS_REDBLACKTREE_H
#define TREES_AND_HEAPS_REDBLACKTREE_H

#include <iostream>
#include "Node.h"
using namespace std;
class RedBlackTree {
    Node* root;
    unsigned long long size;
    static Node* newNode(Node*, int);
    static Node* searchHelper(Node*, int);
    static void printTreeHelper(Node*, string, bool);
    static void rotateLeft(Node*);
    static void rotateRight(Node*);
    void insertHelper(Node*, int);
    void insertFix(Node*);
    void deleteNodeHelper(Node*, int);
    void deleteNodeFix(Node*);

public:
    RedBlackTree() : root(nullptr), size(0) {}
    void insert(int);
    void deleteNode(int);
    Node* search(int);
    int treeHeight();
    int nodeHeight(Node*);
    int nodeDepth(Node*);
    void printTree();
};


#endif //TREES_AND_HEAPS_REDBLACKTREE_H
