#include "BTree.h"

BTree::BTree(int maxChildren) : size(0), capacityElemNode(maxChildren + 1), root(nullptr) {}

void BTree::insert(int key) {
    if(!root) {
        root = new BTreeNode{capacityElemNode};
        root->insertNonLeaf(key, nullptr);
    }else{
        BTreeNode *curr = getGroupNode(key);
        curr->insertNonLeaf(key, nullptr);
        while(root->parent)
            root = root->parent;
    }
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


