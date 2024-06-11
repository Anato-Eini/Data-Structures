#include "BTree.h"

BTree::BTree(const int & maxChildren) : size(0), capacityElemNode(maxChildren + 1), root(nullptr) {}

void BTree::insert(const int & key) {
    if(!root) {
        root = new BTreeNode{capacityElemNode, true};
        root->insert(key);
    }else{
        BTreeNode* curr = getGroupNode(key);
        while(root->parent)
            root = root->parent;

        curr->insert(key);
    }
    size++;
}

BTreeNode *BTree::getGroupNode(const int & key) const {
    BTreeNode* curr = root;
    while(BTreeNode* child = curr->getChild(key))
    {
        curr = child;
    }
    return curr;
}

void BTree::deleteKey(const int & key) {
    BTreeNode* curr = getGroupNode(key);

    size--;
}

std::ostream& operator<<(std::ostream& os, BTree* tree){
    os << "Size: " << tree->size << "\n";
    os << tree->root;
    return os;
}


