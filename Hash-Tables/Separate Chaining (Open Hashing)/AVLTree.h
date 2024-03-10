#ifndef HASH_TABLES_AVLTREE_H
#define HASH_TABLES_AVLTREE_H

#include "Node.h"
#include <iostream>
#include "Node.h"
using namespace std;
class AVLTree {
    Node* root;
    long long size;
    static Node* minimumValue(Node*);
    Node* searchNodeHelper(Node*, int);
    static Node* createNode(Node*, pair<int, int>&);
    void rotateLeft(Node*);
    void rotateRight(Node*);
    void insertHelper(Node*, pair<int, int>&);
    void deleteNodeHelper(Node*);
    void insertFix(Node*, pair<int, int>&);
    void deleteFix(Node*);
    void nodeTransplant(Node*, Node*);
    void printTreeHelper(Node*, string, bool);
    static int nodeHeight(Node*);
    static int getBalanceFactor(Node*);
public:
    AVLTree() : root(nullptr), size(0) {}
    [[nodiscard]] bool isEmpty() const;
    Node* searchNode(int);
    void insertNode(pair<int, int>&);
    void deleteNode(int);
    void printTree();
    pair<int, int> removeRoot();
};


#endif //HASH_TABLES_AVLTREE_H
