#include "SplayTree.h"


Node* SplayTree::createNode(Node *parent, int value) {
    return new Node{value, nullptr, nullptr, parent};
}

void SplayTree::leftRotate(Node* node){
    Node* rightNode = node->right, *rightLeftNode = rightNode->left;
    if(node == root)
        root = rightNode;
    else if(node == node->parent->right)
        node->parent->right = rightNode;
    else
        node->parent->left = rightNode;
    rightNode->parent = node->parent;
    rightNode->left = node;
    node->right = rightLeftNode;
    node->parent = rightNode;
    if(rightLeftNode)
        rightLeftNode->parent = node;
}
void SplayTree::rightRotate(Node* node){
    Node* leftNode = node->left, *leftRightNode = leftNode->right;
    if(node == root)
        root = leftNode;
    else if(node == node->parent->right)
        node->parent->right = leftNode;
    else
        node->parent->left = leftNode;
    leftNode->parent = node->parent;
    leftNode->right = node;
    node->left = leftRightNode;
    node->parent = leftNode;
    if(leftRightNode)
        leftRightNode->parent = node;
}

void SplayTree::search(int value) {
    splay(root, value);
}

void SplayTree::splay(Node *node, int value) {
    if(!node || node->value == value)
        return;

    if(node->value > value){
        if(!node->left)
            return;

        if(node->left->value > value){
            splay(node->left->left, value);
            rightRotate(node);
            splay(node->parent, value);
        }else if(node->left->value < value){
            splay(node->left->right, value);
            if(node->left->right)
                leftRotate(node->left);
            splay(node, value);
        }else
            rightRotate(node->left);
    }else{
        if(!node->right)
            return;

        if(node->right->value < value){
            splay(node->right->right, value);
            leftRotate(node);
            splay(node->parent, value);
        }else if(node->right->value > value){
            splay(node->right->left, value);
            if(node->right->left)
                rightRotate(node->right);
            splay(node, value);
        }else
            leftRotate(node->right);
    }
}

void SplayTree::printTreeHelper(Node *node, string indent, bool isRight) {
    if(node){
        cout << indent;
        if(isRight){
            cout << "R----";
            indent += "   ";
        }else{
            cout << "L----";
            indent += "|  ";
        }
        cout << node->value << "\n";
        printTreeHelper(node->left, indent, false);
        printTreeHelper(node->right, indent, true);
    }
}

void SplayTree::printTree() {
    cout << "Size: " << size << '\n';
    if(root)
        printTreeHelper(root, "", true);
    else
        cout << "Tree is empty\n";
}