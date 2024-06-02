#include "BTree.h"

BTree::BTree(int maxChildren) : size(0), capacityElemNode(maxChildren + 1), root(nullptr) {}

void BTree::insert(int key) {
    BTreeNode* curr;
    if(!root) {
        curr = root = new BTreeNode{capacityElemNode};
        root->insertNonLeaf(key, nullptr);
    }else{
        curr = getGroupNode(key);
        while(root->parent)
            root = root->parent;
    }
    curr->insertNonLeaf(key, nullptr);
    size++;
}

BTreeNode *BTree::getGroupNode(int key) const {
    BTreeNode* curr = root;
    while(true){
        BTreeNode* child = curr->getChild(key);
        if(!child)
            break;
        else
            curr = child;
    }
    return curr;
}

void BTree::deleteKey(int key) {
    BTreeNode* curr = getGroupNode(key);

    size--;
}

std::ostream& operator<<(std::ostream& os, BTree* tree){
    os << "Size: " << tree->size << "\n";
    os << tree->root;
    return os;
}


