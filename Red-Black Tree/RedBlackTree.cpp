#include "RedBlackTree.h"
void RedBlackTree::insertHelper(Node *node, int value) {
    if(node->value > value) {
        if(node->left)
            insertHelper(node->left, value);
        else {
            node->left = newNode;
            newNode->parent = node;
        }
    }else{
        if(node->right)
            insertHelper(node->right, value);
        else{
            node->right = newNode;
            newNode->parent = node;
        }
    }
    if(newNode->parent->parent){
        insertFix(newNode);
    }
}

void RedBlackTree::insert(int value) {
    if(!root)
        root = new Node{value, true, nullptr, nullptr, nullptr};
    else
        insertHelper(root, value);
    size++;
}

void RedBlackTree::insertFix(Node *node) {
    Node* currentNode = node;
    while(!currentNode->parent->isBlack){
        Node* grandParent = currentNode->parent->parent;
        if(currentNode->parent == grandParent->left){

        }else{

        }
        if(currentNode == root) break;
    }
    root->isBlack = true;
}

Node* RedBlackTree::searchHelper(Node *node, int value) {
    if(!node || node->value == value)
        return node;
    else if(node->value > value)
        return searchHelper(node->left, value);
    else
        return searchHelper(node->right, value);
}

Node* RedBlackTree::search(int value) {
    return searchHelper(root, value);
}