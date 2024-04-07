#ifndef DATA_STRUCTURES_BINARYSEARCHTREE_H
#define DATA_STRUCTURES_BINARYSEARCHTREE_H

#include "Node.h"
#include <iostream>

using namespace std;
class BinarySearchTree {
    int size;
    Node* root;
    Node* createNode(int, Node*);
    Node* searchNodeHelper(Node*, int);
    Node* minimumNode(Node*);
    void insertNodeHelper(Node*, int);
    void deleteNodeHelper(Node*);
    void nodeTransplant(Node*, Node*);
    void printTreeHelper(Node*, string, bool, ostream&) const;
    void printInorderHelper(Node*);
    void printPostOrderHelper(Node*);
    void printPreOrderHelper(Node*);
    int depthNodeHelper(Node*, int);
    int heightNodeHelper(Node*);
public:
    BinarySearchTree();
    void insertNode(int);
    void searchNode(int);
    void deleteNode(int);
    void sibling(int);
    int treeHeight();
    int heightNode(int);
    int depthNode(int);
    void printInorder();
    void printPostOrder();
    void printPreOrder();
    void printBFS();
    friend ostream& operator<<(ostream&, const BinarySearchTree*);
};

ostream& operator<<(ostream&, const BinarySearchTree*);

#endif //DATA_STRUCTURES_BINARYSEARCHTREE_H
