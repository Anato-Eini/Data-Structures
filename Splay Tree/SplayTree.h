#ifndef TREES_AND_HEAPS_SPLAYTREE_H
#define TREES_AND_HEAPS_SPLAYTREE_H
#include <iostream>
using namespace std;
#include "Node.h"

class SplayTree {
    Node* root;
    int size;
    static Node* minimumValue(Node*);
    Node* searchNodeHelper(Node*, int);
    static Node* createNode(Node*, int);
    void zag(Node*);
    void zig(Node*);
    void insertHelper(Node*, int);
    void deleteNodeHelper(Node*);
    void insertFix(Node*, int);
    void deleteFix(Node*);
    void nodeTransplant(Node*, Node*);
    void printTreeHelper(Node*, string, bool);
    static int nodeHeight(Node*);
public:
    SplayTree(): root(nullptr), size(0){}
    Node* searchNode(int);
    bool isEmpty();
    void insertNode(int);
    void deleteNode(int);
    void printTree();
    int depth(int);
    int height(int);
    int treeHeight();
};


#endif //TREES_AND_HEAPS_SPLAYTREE_H
