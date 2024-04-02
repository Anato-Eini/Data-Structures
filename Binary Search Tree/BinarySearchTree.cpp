#include "BinarySearchTree.h"
#include <deque>

BinarySearchTree::BinarySearchTree(): root{nullptr}, size{0}{}

Node* BinarySearchTree::minimumNode(Node *node) {
    if(node->left)
        return minimumNode(node->left);
    return node;
}

void BinarySearchTree::nodeTransplant(Node *u, Node *v) {
    if(u->parent){
        if(u->parent->left == u)
            u->parent->left = v;
        else
            u->parent->right = v;
    }else
        root = v;

    if(v)
        v->parent = u->parent;
}

Node* BinarySearchTree::createNode(int value, Node *parent) {
    return new Node{value, nullptr, nullptr, parent};
}

void BinarySearchTree::insertNodeHelper(Node *node, int value) {
    if(node->value > value){
        if(node->left)
            insertNodeHelper(node->left, value);
        else
            node->left = createNode(value, node);
    }else{
        if(node->right)
            insertNodeHelper(node->right, value);
        else
            node->right = createNode(value, node);
    }
}

void BinarySearchTree::insertNode(int value) {
    if(!root)
        root = createNode(value, nullptr);
    else
        insertNodeHelper(root, value);

    size++;
}

Node* BinarySearchTree::searchNodeHelper(Node *node, int value) {
    if(!node || node->value == value)
        return node;
    else if(node->value > value)
        return searchNodeHelper(node->left, value);
    else
        return searchNodeHelper(node->right, value);
}

void BinarySearchTree::searchNode(int value) {
    Node* searchedNode = searchNodeHelper(root, value);
    cout << "Element " << value << (searchedNode ? "" : " does not") << " exists\n";
}

void BinarySearchTree::deleteNodeHelper(Node *node) {
    if(!node->left)
        nodeTransplant(node, node->right);
    else if(!node->right)
        nodeTransplant(node, node->left);
    else{
        Node* minNode = minimumNode(node->right);
        node->value = minNode->value;
        deleteNodeHelper(minNode);
        return;
    }

    delete node;
    --size;
}

void BinarySearchTree::deleteNode(int value) {
    Node* searchedNode = searchNodeHelper(root, value);
    if(searchedNode)
        deleteNodeHelper(searchedNode);
    else
        cout << "Element " << value << " does not exists\n";
}

void BinarySearchTree::sibling(int value) {
    Node* searchedNode = searchNodeHelper(root, value);

    if(!searchedNode)
        cout << "Element " << value << " does not exist\n";
    else if(!searchedNode->parent)
        cout << "Element " << value << " is a root node\n";
    else if(searchedNode->parent->left == searchedNode){
        if(!searchedNode->parent->right)
            cout << "Element " << value << " has no sibling\n";
        else
            cout << "Element " << value << "'s sibling is " << searchedNode->parent->right->value << '\n';
    }else{
        if(!searchedNode->parent->left)
            cout << "Element " << value << " has no sibling\n";
        else
            cout << "Element " << value << "'s sibling is " << searchedNode->parent->left->value << '\n';
    }
}

int BinarySearchTree::heightNodeHelper(Node *node) {
    if(!node)
        return -1;
    return max(heightNodeHelper(node->left), heightNodeHelper(node->right)) + 1;
}

int BinarySearchTree::treeHeight() {
    return heightNodeHelper(root) + 1;
}

int BinarySearchTree::heightNode(int value) {
    Node* searchedNode = searchNodeHelper(root, value);

    return !searchedNode ? -1: heightNodeHelper(searchedNode);
}

int BinarySearchTree::depthNodeHelper(Node *node, int value) {
    if(!node)
        return -size;
    else if(node->value == value)
        return 0;
    else if(node->value > value)
        return depthNodeHelper(node->left, value) + 1;
    else
        return depthNodeHelper(node->right, value) + 1;
}

int BinarySearchTree::depthNode(int value) {
    return depthNodeHelper(root, value);
}

void BinarySearchTree::printTreeHelper(Node *node, string indent, bool isRight) {
    if(node){
        cout << indent;
        if (isRight) {
            cout << "R----";
            indent += "   ";
        } else {
            cout << "L----";
            indent += "|  ";
        }

        cout << node->value <<'\n';
        printTreeHelper(node->left, indent, false);
        printTreeHelper(node->right, indent, true);
    }
}

void BinarySearchTree::printTree() {
    cout << "Size: " << size << '\n';
    if(size != 0)
        printTreeHelper(root, "", true);
    else
        cout << "Tree is empty\n";
}

void BinarySearchTree::printInorderHelper(Node *node) {
    if(node){
        printInorderHelper(node->left);
        cout << node->value << ' ';
        printInorderHelper(node->right);
    }
}

void BinarySearchTree::printInorder() {
    printInorderHelper(root);
}

void BinarySearchTree::printPostOrderHelper(Node *node) {
    if(node){
        printPostOrderHelper(node->left);
        printPostOrderHelper(node->right);
        cout << node->value << ' ';
    }
}

void BinarySearchTree::printPostOrder() {
    printPostOrderHelper(root);
}

void BinarySearchTree::printPreOrderHelper(Node *node) {
    if(node){
        cout << node->value << ' ';
        printPreOrderHelper(node->left);
        printPreOrderHelper(node->right);
    }
}

void BinarySearchTree::printPreOrder() {
    printPreOrderHelper(root);
}

void BinarySearchTree::printBFS() {
    if(!root){
        return;
    }
    deque<Node*> queue;
    queue.push_back(root);

    while(!queue.empty()){
        Node* node = queue.front();
        cout << node->value << ' ';
        queue.pop_front();
        if(node->left)
            queue.push_back(node->left);
        if(node->right)
            queue.push_back(node->right);
    }
}