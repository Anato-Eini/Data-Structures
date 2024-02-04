#ifndef TREES_AND_HEAPS_AVLTREE_H
#define TREES_AND_HEAPS_AVLTREE_H

#include <iostream>
#include "Node.h"
using namespace std;
class AVLTree {
    Node* root;
    long long size;
    static Node* minimumValue(Node*);
    Node* searchNodeHelper(Node*, int);
    static Node* createNode(Node*, int);
    void rotateLeft(Node*);
    void rotateRight(Node*);
    void insertHelper(Node*, int);
    void deleteNodeHelper(Node*);
    void reBalanceTree(Node*, int);
    void nodeTransplant(Node*, Node*);
    void printTreeHelper(Node*, string, bool);
    static int nodeHeight(Node*);
    static int getBalanceFactor(Node*);
public:
    AVLTree() : root(nullptr), size(0) {}
    Node* searchNode(int);
    void insertNode(int);
    void deleteNode(int);
    void printTree();
    int depth(Node*);
    int height(Node*);
    int treeHeight();
};


#endif //TREES_AND_HEAPS_AVLTREE_H
