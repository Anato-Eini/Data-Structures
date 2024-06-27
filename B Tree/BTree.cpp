#include "BTree.h"

BTree::BTree(const int & maxChildren) : size(0), capacityElemNode(maxChildren + 1), root(nullptr) {}

void BTree::insert(const int & key) {
    if(!root) {
        root = new BTreeNode{capacityElemNode, true};
        root->insert(key);
    }else{
        BTreeNode* curr = getGroupNode(key);
        curr->insert(key);

        while(root->parent)
            root = root->parent;
    }
    size++;
}

BTreeNode *BTree::getGroupNode(const int & key) const {
    BTreeNode* curr = root;
    while(BTreeNode* child = curr->getChild(key))
        curr = child;

    return curr;
}

void BTree::deleteKey(const int & key) {
    BTreeNode* curr = getGroupNode(key);
    curr->deleteKey(key);
    size--;
}

std::ostream& operator<<(std::ostream& os, const BTree* tree){
    os << "Size: " << tree->size << "\n";
    os << tree->root << '\n';
    return os;
}

void BTree::clearTreeHelper(const BTreeNode *node) {
    if(node){
        for(int i = 0; i <= size; i++)
            clearTreeHelper(node->children[i]);

        delete this;
    }
}

void BTree::clearTree() {
    clearTreeHelper(root);
}

BTree::~BTree() {
    clearTree();
}
