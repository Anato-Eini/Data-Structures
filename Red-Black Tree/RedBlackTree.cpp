#include "RedBlackTree.h"
Node *RedBlackTree::newNode(Node *parent, int value) {
    return new Node{value, false, nullptr, nullptr, parent};
}

Node* RedBlackTree::minimumNode(Node *node) {
    if(node->left)
        return minimumNode(node->left);
    return node;
}

void RedBlackTree::rbTransplant(Node *u, Node *v) {
    if(!u->parent)
        root = v;
    else if(u->parent->left == u)
        u->parent->left = v;
    else
        u->parent->right = v;
    if(v)
        v->parent = u->parent;
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

void RedBlackTree::insertFix(Node *node) {
    Node* currentNode = node;
    while(!currentNode->parent->isBlack){
        Node* gp = currentNode->parent->parent;
        if(currentNode->parent == gp->left){
            if(gp->right && !gp->right->isBlack){
                gp->right->isBlack = true;
                gp->isBlack = false;
                currentNode->parent->isBlack = true;
                currentNode = gp;
            }else{
                if(currentNode == currentNode->parent->right){
                    currentNode = currentNode->parent;
                    rotateLeft(currentNode);
                }
                currentNode->parent->isBlack = true;
                gp->isBlack = false;
                if(gp == root)
                    root = currentNode->parent;
                rotateRight(gp);
            }
        }else{
            if(gp->left && !gp->left->isBlack){
                gp->left->isBlack = true;
                gp->isBlack = false;
                currentNode->parent->isBlack = true;
                currentNode = gp;
            }else{
                if(currentNode == currentNode->parent->left){
                    currentNode = currentNode->parent;
                    rotateRight(currentNode);
                }
                currentNode->parent->isBlack = true;
                gp->isBlack = false;
                if(gp == root)
                    root = currentNode->parent;
                rotateLeft(gp);
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
            insertFix(node->left);
        }
    }else{
        if(node->right)
            insertHelper(node->right, value);
        else {
            node->right = newNode(node, value);
            insertFix(node->right);
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

void RedBlackTree::deleteFix(Node *node) {
    Node* currentNode = node;
    while(currentNode != root && currentNode->parent){
        if(currentNode->parent->left == currentNode){
            Node* sibling = currentNode->parent->right;
            if(sibling->isBlack){
                if(sibling->right && !sibling->right->isBlack){
                    sibling->right->isBlack = true;
                    rotateLeft(currentNode->parent);
                } else if(sibling->left && !sibling->left->isBlack){
                    sibling->left->isBlack = true;
                    rotateRight(sibling);
                    if(currentNode->parent == root)
                        root = sibling->parent;
                    rotateLeft(currentNode->parent);
                } else{
                    sibling->isBlack = false;
                    if(sibling->parent->isBlack)
                        currentNode = currentNode->parent;
                }
            }else{

            }
        }else{

        }
    }
    root->isBlack = true;
}

void RedBlackTree::deleteNode(Node* node) {
    bool isDeletedBlack = node->isBlack;
    Node *replacementNode = nullptr, *minimum = node;
    if(!node->left){
        replacementNode = node->right;
        rbTransplant(node, node->right);
    }else if(!node->right){
        replacementNode = node->left;
        rbTransplant(node, node->left);
    }else{
        minimum = minimumNode(node->right);
        replacementNode = minimum->right;
        node->value = minimum->value;
        isDeletedBlack = node->isBlack = minimum->isBlack;
        rbTransplant(minimum, minimum->right);
    }
    if(replacementNode && !replacementNode->isBlack)
        replacementNode->isBlack = true;
    else if(!replacementNode && isDeletedBlack)
        deleteFix(minimum);
    else if(isDeletedBlack)
        deleteFix(replacementNode);
    size--;
    delete node;
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