#include <algorithm>
#include "AVLTree.h"
Node* AVLTree::minimumValue(Node *node) {
    return node->left ? minimumValue(node->left) : node;
}

Node* AVLTree::createNode(Node *parent, int value) {
    return new Node{value, 1, nullptr, nullptr, parent};
}

void AVLTree::nodeTransplant(Node *u, Node *v) {
    if(u == root)
        root = v;
    else if(u->parent->left == u) {
        u->parent->left = v;
        u->parent->height = max(nodeHeight(u->parent->left), nodeHeight(u->parent->right)) + 1;
    }else {
        u->parent->right = v;
        u->parent->height = max(nodeHeight(u->parent->left), nodeHeight(u->parent->right)) + 1;
    }
    if(v)
        v->parent = u->parent;
}

void AVLTree::rotateLeft(Node *node) {
    Node* rightNode = node->right;
    Node* rightLeft = rightNode->left;
    if(node == root)
        root = rightNode;
    else if(node->parent->left == node)
        node->parent->left = rightNode;
    else
        node->parent->right = rightNode;
    rightNode->left = node;
    rightNode->parent = node->parent;
    node->parent = rightNode;
    node->right = rightLeft;
    node->height = max(nodeHeight(node->right), nodeHeight(node->left)) + 1;
    rightNode->height = max(nodeHeight(rightNode->right), nodeHeight(rightNode->left)) + 1;
    if(rightLeft)
        rightLeft->parent = node;
}

void AVLTree::rotateRight(Node *node) {
    Node* leftNode = node->left;
    Node* leftRight = leftNode->right;
    if(node == root)
        root = leftNode;
    else if(node->parent->left == node)
        node->parent->left = leftNode;
    else
        node->parent->right = leftNode;
    leftNode->right = node;
    leftNode->parent = node->parent;
    node->parent = leftNode;
    node->left = leftRight;
    node->height = max(nodeHeight(node->left), nodeHeight(node->right)) + 1;
    leftNode->height = max(nodeHeight(leftNode->left), nodeHeight(leftNode->right)) + 1;
    if(leftRight)
        leftRight->parent = node;
}

void AVLTree::reBalanceTree(Node *node, int value) {
    node->height = max(nodeHeight(node->left), nodeHeight(node->right)) + 1;
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
        if (node->left->value < value)
            rotateLeft(node->left);
        rotateRight(node);
    } else if (balanceFactor < -1) {
        if (node->right->value > value)
            rotateRight(node->right);
        rotateLeft(node);
    }
}

void AVLTree::insertHelper(Node *node, int value) {
    if(node->value > value){
        if(node->left)
            insertHelper(node->left, value);
        else
            node->left = createNode(node, value);
    }else{
        if(node->right)
            insertHelper(node->right, value);
        else
            node->right = createNode(node, value);
    }
    reBalanceTree(node, value);
}

void AVLTree::insertNode(int value) {
    if(!root)
        root = createNode(nullptr, value);
    else
        insertHelper(root, value);
    size++;
}

void AVLTree::deleteNodeHelper(Node *node) {
    Node* replacementNode;
    if(!node->left){
        replacementNode = node->right;
        nodeTransplant(node, replacementNode);
    }else if(!node->right){
        replacementNode = node->left;
        nodeTransplant(node, replacementNode);
    }else{
        Node* minimumNode = minimumValue(node->right);
        node->value = minimumNode->value;
        deleteNodeHelper(minimumNode);
    }
}

void AVLTree::deleteNode(int value) {
    Node* node = searchNode(value);
    if(node)
        deleteNodeHelper(node);
    else
        cout << value << " not found\n";
}

Node* AVLTree::searchNodeHelper(Node* node, int value) {
    if(!node || node->value == value)
        return node;
    else if(node->value > value)
        searchNodeHelper(node->left, value);
    else
        searchNodeHelper(node->right, value);
}

Node* AVLTree::searchNode(int value) {
    searchNodeHelper(root, value);
}

int AVLTree::nodeHeight(Node *node) {
    return node ? node->height : 0;
}

int AVLTree::getBalanceFactor(Node *node) {
    return nodeHeight(node->left) - nodeHeight(node->right);
}

void AVLTree::printTreeHelper(Node *node, string indent, bool isRight) {
    if(node){
        cout << indent;
        if (isRight) {
            cout << "R----";
            indent += "    ";
        } else {
            cout << "L----";
            indent += "|   ";
        }
        cout << node->value << " Height(" << node->height << ")\n";
        printTreeHelper(node->left, indent, false);
        printTreeHelper(node->right, indent, true);
    }
}

void AVLTree::printTree() {
    cout << "Size: " << size << '\n';
    if(size == 0)
        cout << "Tree is empty.\n";
    printTreeHelper(root, "", true);
}