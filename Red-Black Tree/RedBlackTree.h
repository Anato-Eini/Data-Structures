#ifndef TREES_AND_HEAPS_REDBLACKTREE_H
#define TREES_AND_HEAPS_REDBLACKTREE_H

#include <iostream>
#include "Node.h"
using namespace std;
class RedBlackTree {
    Node* root, *null;
    unsigned long long size;
    Node* newNode(Node*, int);
    Node* minimumNode(Node*);
    Node* searchHelper(Node*, int);
    void rotateLeft(Node*);
    void rotateRight(Node*);
    void printTreeHelper(Node*, string, bool);
    void insertHelper(Node*, int);
    void insertFix(Node*);
    void rbTransplant(Node* , Node*);
    void deleteFix(Node*);
public:
    RedBlackTree() : size(0), null(new Node{0, true, nullptr, nullptr}) {
        root = null;
    }
    Node* search(int);
    Node* nullNode();
    void insert(int);
    void deleteNode(Node*);
    void printTree();
    bool isEmpty();
    int treeHeight();
    int nodeHeight(Node*);
    int nodeDepth(Node*);
    int minimumValue();
};


#endif //TREES_AND_HEAPS_REDBLACKTREE_H
