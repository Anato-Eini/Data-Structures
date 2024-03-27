#ifndef TREES_AND_HEAPS_SPLAYTREE_H
#define TREES_AND_HEAPS_SPLAYTREE_H
#include <iostream>
using namespace std;
#include "Node.h"

class SplayTree {
    Node* root;
    int size;
    static Node* createNode(Node*, int);
    void leftRotate(Node*);
    void rightRotate(Node*);
    void splay(Node*, int);
    void printTreeHelper(Node*, string, bool) const;
    int treeHeightHelper(Node*) const;
    int depthHelper(Node*, int) const;
public:
    SplayTree(): root(nullptr), size(0){}
    Node* search(int);
    [[nodiscard]]bool isEmpty() const;
    void insertNode(int);
    void deleteNode(int);
    void printTree() const;
    [[nodiscard]] int depth(int) const;
    [[nodiscard]] int treeHeight() const;
    [[nodiscard]] int height(int) const;
};


#endif //TREES_AND_HEAPS_SPLAYTREE_H
