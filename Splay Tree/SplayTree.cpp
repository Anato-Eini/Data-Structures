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
    cout << node->value << " rotated to the left\n";
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
    cout << node->value << " rotated to the right\n";
}

Node* SplayTree::search(int value) {
    splay(root, value);
    return root;
}

void SplayTree::deleteNode(int value) {
    splay(root, value);
    if(root->value != value){
        cout << "Value doesn't exists\n";
        return;
    }
    Node* leftSubtree = root->left, *rightSubtree = root->right;
    delete root;
    if(!leftSubtree)
        root = rightSubtree;
    else if(!rightSubtree)
        root = leftSubtree;
    else{
        splay(root->left, rightSubtree->value);
        leftSubtree->right = rightSubtree;
        root = leftSubtree;
    }
    size--;
}

void SplayTree::insertNode(int value) {
    if(!root)
        root = createNode(nullptr, value);
    else{
        splay(root, value);
        Node *newNode;
        if (root->value > value) {
            newNode = new Node{value, root->left, root, nullptr};
            if (root->left)
                root->left->parent = newNode;
            root->left = nullptr;
        } else {
            newNode = new Node{value, root, root->right, nullptr};
            if (root->right)
                root->right->parent = newNode;
            root->right = nullptr;
        }
        root->parent = newNode;
        root = newNode;
    }
    size++;
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
            rightRotate(node->parent);
            return;
        }else if(node->left->value < value){
            splay(node->left->right, value);
            if(node->left->right)
                leftRotate(node->left);
            rightRotate(node);
        }else if(node->parent)
            splay(node->parent, value);
        else
            rightRotate(node);
    }else{
        if(!node->right)
            return;

        if(node->right->value < value){
            splay(node->right->right, value);
            leftRotate(node);
            leftRotate(node->parent);
            return;
        }else if(node->right->value > value){
            splay(node->right->left, value);
            if(node->right->left)
                rightRotate(node->right);
            leftRotate(node);
        }else if(node->parent)
            splay(node->parent, value);
        else
            leftRotate(node);
    }
}

void SplayTree::printTreeHelper(Node *node, string indent, bool isRight) const {
    if(node){
        cout << indent;
        if(isRight){
            cout << "R----";
            indent += "   ";
        }else{
            cout << "L----";
            indent += "|  ";
        }
        cout << node->value  << (node->parent ? " has parent": " no parent") << "\n";
        printTreeHelper(node->left, indent, false);
        printTreeHelper(node->right, indent, true);
    }
}

void SplayTree::printTree() const{
    cout << "Size: " << size << '\n';
    if(root)
        printTreeHelper(root, "", true);
    else
        cout << "Tree is empty\n";
}

int SplayTree::height(int value) const {
    Node* searchedNode = searchNodeHelper(root, value);
    return searchedNode ? treeHeightHelper(searchedNode) : -1;
}

int SplayTree::treeHeight() const{
    return treeHeightHelper(root) + 1;
}

int SplayTree::treeHeightHelper(Node *node) const{
    if(!node)
        return 0;
    return max(treeHeightHelper(node->left), treeHeightHelper(node->right)) + 1;
}

Node* SplayTree::searchNodeHelper(Node *node, int value) const {
    if(!node || node->value == value)
        return node;
    else if(node->value > value)
        searchNodeHelper(node->left, value);
    else
        searchNodeHelper(node->right, value);
}

Node* SplayTree::searchNode(int value) const{
    return searchNodeHelper(root, value);
}

bool SplayTree::isEmpty() const {
    return size == 0;
}

int SplayTree::depthHelper(Node *node, int value) const {
    if(!node)
        return -size;
    else if(node->value == value)
        return 0;
    return node->value > value ? depthHelper(node->left, value) + 1 : depthHelper(node->right, value) + 1;
}

int SplayTree::depth(int value) const{
    return depthHelper(root, value);
}