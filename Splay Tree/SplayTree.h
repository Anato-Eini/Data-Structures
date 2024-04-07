#ifndef TREES_AND_HEAPS_SPLAYTREE_H
#define TREES_AND_HEAPS_SPLAYTREE_H
#include <iostream>
using namespace std;
#include "Node.h"

class SplayTree {
    Node* root;
    int size;
    [[nodiscard]] Node* searchNode(int) const;
    static Node* createNode(Node*, int);
    Node* searchNodeHelper(Node*, int) const;
    void leftRotate(Node*);
    void rightRotate(Node*);
    void splay(Node*, int);
    void printTreeHelper(Node*, string, bool, ostream&) const;
    int treeHeightHelper(Node*) const;
    int depthHelper(Node*, int) const;
public:
    SplayTree(): root(nullptr), size(0){}
    Node* search(int);
    [[nodiscard]]bool isEmpty() const;
    void insertNode(int);
    void deleteNode(int);
    [[nodiscard]] int depth(int) const;
    [[nodiscard]] int treeHeight() const;
    [[nodiscard]] int height(int) const;
    friend ostream& operator<<(ostream&, const SplayTree*);
};

ostream& operator<<(ostream&, const SplayTree*);

#endif //TREES_AND_HEAPS_SPLAYTREE_H
