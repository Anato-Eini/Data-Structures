#ifndef TREES_AND_HEAPS_REDBLACKTREE_H
#define TREES_AND_HEAPS_REDBLACKTREE_H

#include <iostream>
#include "Node.h"
using namespace std;
class RedBlackTree {
    Node* root;
    unsigned long long size;
    static Node* newNode(Node*, int);
    static void rotateLeft(Node*);
    static void rotateRight(Node*);
    void insertHelper(Node*, int);
    void insertFix(Node*);
    static Node* searchHelper(Node*, int);
    void printHelper(Node* root, string indent, bool last) {
        if (root) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            } else {
                cout << "L----";
                indent += "|  ";
            }

            string sColor = !root->isBlack ? "RED" : "BLACK";
            cout << root->value << "(" << sColor << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }
public:
    RedBlackTree() : root(nullptr), size(0) {}
    void insert(int);
    Node* search(int);
    int treeHeight();
    int nodeHeight(Node*);
    int nodeDepth(Node*);
    void printTree() {
        if (root) {
            printHelper(this->root, "", true);
        }
    }
};


#endif //TREES_AND_HEAPS_REDBLACKTREE_H
