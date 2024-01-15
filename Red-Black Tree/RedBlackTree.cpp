#include "RedBlackTree.h"
Node *RedBlackTree::newNode(Node *parent, int value) {
    return new Node{value, false, nullptr, nullptr, parent};
}

void RedBlackTree::rotateLeft(Node *node) {
    Node* rightNode = node->right;
    Node* rightLeftNode = rightNode->left;
    node->parent->left = rightNode;
    rightNode->parent = node->parent;
    rightNode->left = node;
    node->right = rightLeftNode;
    node->parent = rightNode;
    rightLeftNode->parent = node;
}

void RedBlackTree::rotateRight(Node *node) {
    Node* leftNode = node->left;
    Node* leftRightNode = leftNode->right;
    node->parent->right = leftNode;
    leftNode->parent = node->parent;
    leftNode->right = leftRightNode;
    node->left = leftRightNode;
    node->parent = leftNode;
    leftRightNode->parent = node;
}

void RedBlackTree::insert(int value) {
    if(!root)
        root = new Node{value, true, nullptr, nullptr, nullptr};
    else
        insertHelper(root, value);
    size++;
}

void RedBlackTree::insertHelper(Node *node, int value) {
    if(node->value > value) {
        if(node->left)
            insertHelper(node->left, value);
        else {
            node->left = newNode(node, value);
            if(node->parent)
                insertFix(node->left);
        }
    }else{
        if(node->right)
            insertHelper(node->right, value);
        else {
            node->right = newNode(node, value);
            if(node->parent)
                insertFix(node->right);
        }
    }
}

void RedBlackTree::insertFix(Node *node) {
    Node* currentNode = node;
    while(!currentNode->parent->isBlack){
        Node* gp = currentNode->parent->parent;
        if(currentNode->parent == gp->left){
            if(!gp->right->isBlack){
                gp->right->isBlack = true;
                gp->isBlack = false;
                currentNode->parent->isBlack = false;
                currentNode = currentNode->parent->parent;
            }else{

            }
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
