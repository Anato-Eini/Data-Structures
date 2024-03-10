#include <algorithm>
#include "AVLTree.h"
Node* AVLTree::minimumValue(Node *node) {
    return node->left ? minimumValue(node->left) : node;
}

Node* AVLTree::createNode(Node *parent, pair<int, int>& keyValue) {
    return new Node{keyValue, 1, nullptr, nullptr, parent};
}

void AVLTree::deleteFix(Node *node) {
    node->height = max(nodeHeight(node->left), nodeHeight(node->right)) + 1;
    int balanceFactor = getBalanceFactor(node);
    if(balanceFactor > 1){
        if(getBalanceFactor(node->left) < 0)
            rotateLeft(node->left);
        rotateRight(node);
    }else if(balanceFactor < -1){
        if(getBalanceFactor(node->right) > 0)
            rotateRight(node->right);
        rotateLeft(node);
    }
}

void AVLTree::nodeTransplant(Node *u, Node *v) {
    if(u == root)
        root = v;
    else if(u->parent->left == u) {
        u->parent->left = v;
        u->parent->height = max(nodeHeight(u->parent->left), nodeHeight(u->parent->right)) + 1;
    }else{
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

void AVLTree::insertFix(Node *node, pair<int, int> &keyValue) {
    node->height = max(nodeHeight(node->left), nodeHeight(node->right)) + 1;
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
        if (node->left->pair.first < keyValue.first)
            rotateLeft(node->left);
        rotateRight(node);
    } else if (balanceFactor < -1) {
        if (node->right->pair.first > keyValue.first)
            rotateRight(node->right);
        rotateLeft(node);
    }
}

void AVLTree::insertHelper(Node *node, pair<int, int>& keyValue) {
    if(node->pair.first > keyValue.first){
        if(node->left)
            insertHelper(node->left, keyValue);
        else
            node->left = createNode(node, keyValue);
    }else{
        if(node->right)
            insertHelper(node->right, keyValue);
        else
            node->right = createNode(node, keyValue);
    }
    insertFix(node, keyValue);
}

void AVLTree::insertNode(pair<int, int>& keyValue) {
    if(!root)
        root = createNode(nullptr, keyValue);
    else
        insertHelper(root, keyValue);
    size++;
}

void AVLTree::deleteNodeHelper(Node *node) {
    Node* replacementNode, *curr = node, *deleteNode;
    deleteNode = curr;
    if (!node->left)
        replacementNode = node->right;
    else if (!node->right)
        replacementNode = node->left;
    else {
        deleteNode = curr = minimumValue(node->right);
        node->pair = curr->pair;
        replacementNode = curr->right;
    }
    nodeTransplant(curr, replacementNode);
    curr = curr->parent;
    while(curr){
        deleteFix(curr);
        curr = curr->parent;
    }
    delete deleteNode;
}

void AVLTree::deleteNode(int value) {
    Node* node = searchNode(value);
    if(node) {
        deleteNodeHelper(node);
        size--;
    }else
        cout << value << " not found\n";
}

Node* AVLTree::searchNodeHelper(Node* node, int value) {
    if(!node || node->pair.first == value)
        return node;
    else if(node->pair.first > value)
        return searchNodeHelper(node->left, value);
    else
        return searchNodeHelper(node->right, value);
}

Node* AVLTree::searchNode(int value) {
    return searchNodeHelper(root, value);
}

int AVLTree::nodeHeight(Node *node) {
    return node ? node->height : 0;
}

int AVLTree::getBalanceFactor(Node *node) {
    return nodeHeight(node->left) - nodeHeight(node->right);
}

pair<int, int> AVLTree::removeRoot() {
    pair<int, int> valueOfRoot = root->pair;
    deleteNode(valueOfRoot.first);
    return valueOfRoot;
}

bool AVLTree::isEmpty() const {
    return size == 0;
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
        cout << "< " << node->pair.first << ", " << node->pair.second << " >"<< "\n\t\t";
        printTreeHelper(node->left, indent, false);
        printTreeHelper(node->right, indent, true);
    }
}

void AVLTree::printTree() {
    printTreeHelper(root, "", true);
}