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
    void printTreeHelper(Node*, string, bool);
public:
    SplayTree(): root(nullptr), size(0){}
    void search(int);
    bool isEmpty();
    void insertNode(int);
    void deleteNode(int);
    void printTree();
    int depth(int);
    int height(int);
    int treeHeight();
    Node* getRoot(){
        return root;
    }
    void setRoot(Node* node){
        root = node;
    }
};


#endif //TREES_AND_HEAPS_SPLAYTREE_H
