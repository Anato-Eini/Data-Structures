#ifndef TREES_AND_HEAPS_REDBLACKTREE_H
#define TREES_AND_HEAPS_REDBLACKTREE_H

#include <iostream>
#include "Node.h"
using namespace std;
class RedBlackTree {
    unsigned long long size;
    Node* root, *null;
    Node* newNode(Node*, int);
    Node* minimumNode(Node*);
    Node* searchHelper(Node*, int);
    void rotateLeft(Node*);
    void rotateRight(Node*);
    void printTreeHelper(Node*, string, bool, ostream&) const;
    void insertHelper(Node*, int);
    void insertFix(Node*);
    void rbTransplant(Node*, Node*);
    void deleteFix(Node*);
public:
    RedBlackTree();
    Node* search(int);
    Node* nullNode();
    void insert(int);
    void deleteNode(Node*);
    bool isEmpty() const;
    int treeHeight();
    int nodeHeight(Node*);
    int nodeDepth(Node*);
    friend ostream& operator<<(ostream&, const RedBlackTree*);
};

ostream& operator<<(ostream&, const RedBlackTree*);

#endif //TREES_AND_HEAPS_REDBLACKTREE_H
