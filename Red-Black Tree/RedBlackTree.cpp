#include "RedBlackTree.h"
Node *RedBlackTree::newNode(Node *parent, int value) {
    return new Node{value, false, nullptr, nullptr, parent};
}

Node* RedBlackTree::minimumNode(Node *node) {
    if(node->left)
        return minimumNode(node->left);
    return node;
}

void RedBlackTree::rbTransplant(Node *node1, Node *node2) {
    if(!node1->parent)
        root = node2;
    else if(node1->parent->left == node1)
        node1->parent->left = node2;
    else
        node1->parent->right = node2;
    node2->parent = node1->parent;
}

void RedBlackTree::rotateLeft(Node *node) {
    Node* rightNode = node->right;
    Node* rightLeftNode = rightNode->left;
    if(node->parent && node == node->parent->right)
        node->parent->right = rightNode;
    else if(node->parent && node == node->parent->left)
        node->parent->left = rightNode;
    rightNode->parent = node->parent;
    rightNode->left = node;
    node->right = rightLeftNode;
    node->parent = rightNode;
    if(rightLeftNode)
        rightLeftNode->parent = node;
}

void RedBlackTree::rotateRight(Node *node) {
    Node* leftNode = node->left;
    Node* leftRightNode = leftNode->right;
    if(node->parent && node == node->parent->right)
        node->parent->right = leftNode;
    else if(node->parent && node == node->parent->left)
        node->parent->left = leftNode;
    leftNode->parent = node->parent;
    leftNode->right = node;
    node->left = leftRightNode;
    node->parent = leftNode;
    if(leftRightNode)
        leftRightNode->parent = node;
}

void RedBlackTree::colorFix(Node *node) {
    Node* currentNode = node;
    while(!currentNode->parent->isBlack && !currentNode->isBlack
    && currentNode->parent->parent && currentNode->parent){
        Node* gp = currentNode->parent->parent;
        if(currentNode->parent == gp->left){
            if(gp->right && !gp->right->isBlack){
                gp->right->isBlack = true;
                gp->isBlack = false;
                currentNode->parent->isBlack = true;
                currentNode = gp;
            }else{
                if(currentNode == currentNode->parent->right){
                    currentNode->isBlack = true;
                    rotateLeft(currentNode->parent);
                    if(currentNode->parent == root)
                        root = currentNode;
                    currentNode->parent->isBlack = false;
                    rotateRight(currentNode->parent);
                }else{
                    currentNode->parent->isBlack = true;
                    gp->isBlack = false;
                    if(gp == root)
                        root = currentNode->parent;
                    rotateRight(gp);
                    currentNode = currentNode->parent;
                }
            }
        }else{
            if(gp->left && !gp->left->isBlack){
                gp->left->isBlack = true;
                gp->isBlack = false;
                currentNode->parent->isBlack = true;
                currentNode = gp;
            }else{
                if(currentNode == currentNode->parent->left){
                    currentNode->isBlack = true;
                    rotateRight(currentNode->parent);
                    if(currentNode->parent == root)
                        root = currentNode;
                    currentNode->parent->isBlack = false;
                    rotateLeft(currentNode->parent);
                }else{
                    currentNode->parent->isBlack = true;
                    gp->isBlack = false;
                    if(gp == root)
                        root = currentNode->parent;
                    rotateLeft(gp);
                    currentNode = currentNode->parent;
                }
            }
        }
        if(currentNode == root)
            break;
    }
    root->isBlack = true;
}

void RedBlackTree::insertHelper(Node *node, int value) {
    if(node->value > value) {
        if(node->left)
            insertHelper(node->left, value);
        else {
            node->left = newNode(node, value);
            colorFix(node->left);
        }
    }else{
        if(node->right)
            insertHelper(node->right, value);
        else {
            node->right = newNode(node, value);
            colorFix(node->right);
        }
    }
}

void RedBlackTree::insert(int value) {
    if(!root)
        root = new Node{value, true, nullptr, nullptr, nullptr};
    else
        insertHelper(root, value);
    size++;
}


void RedBlackTree::deleteNode(Node* node) {
    bool isDeletedNodeBlack = node->isBlack;
    Node* replacementNode = nullptr;
    if(!node->left && !node->right) {
        if(!node->parent)
            root = nullptr;
        else if(node->parent->left == node){
            node->parent->left = nullptr;
            node->parent = nullptr;
        }else{
            node->parent->right = nullptr;
            node->parent = nullptr;
        }
    }else if(!node->left) {
        replacementNode = node->right;
        rbTransplant(node, node->right);
    }else if(!node->right) {
        replacementNode = node->left;
        rbTransplant(node, node->left);
    }else{
        Node* minimum = minimumNode(node->right);
        replacementNode = minimum->right;
        node->value = minimum->value;
        node->isBlack = minimum->isBlack;
        deleteNode(minimum);
    }
    delete node;
    if(replacementNode && isDeletedNodeBlack)
        colorFix(replacementNode);
    size--;
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

void RedBlackTree::printTreeHelper(Node *node, string indent, bool isRight) {
    if(node){
        cout << indent;
        if(isRight){
            cout << "R----";
            indent += "   ";
        }else{
            cout << "L----";
            indent += "|  ";
        }
        cout << node->value << " (" << (node->isBlack ? "Black" : "Red") << ")\n";
        printTreeHelper(node->left, indent, false);
        printTreeHelper(node->right, indent, true);
    }
}

void RedBlackTree::printTree() {
    cout << "Size: " << size << '\n';
    if(root)
        printTreeHelper(root, "", true);
    else
        cout << "Tree is empty\n";
}

int RedBlackTree::treeHeight() {
    return nodeHeight(root) + 1;
}

int RedBlackTree::nodeHeight(Node *node) {
    if(!node) return -1;
    return max(nodeHeight(node->right), nodeHeight(node->left)) + 1;
}

int RedBlackTree::nodeDepth(Node *node) {
    if(!node) return -1;
    return nodeDepth(node->parent) + 1;
}