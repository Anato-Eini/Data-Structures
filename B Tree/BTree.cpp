#include "BTree.h"

BTree::BTree(int maxChildren) : size(0), capacityElemNode(maxChildren + 1), root(nullptr) {}

void BTree::insert(int key) {
    if(!root) {
        root = new BTreeNode{capacityElemNode};
        root->insertNonLeaf(key, nullptr);
    }else{
        BTreeNode* curr = root;
        while(true){
            BTreeNode* child = curr->getChild(key);
            if(!child) {
                curr->insertNonLeaf(key, nullptr);
                break;
            }else
                curr = child;
        }
        while(root->parent)
            root = root->parent;
    }
    size++;
}

std::ostream& operator<<(std::ostream& os, BTree* tree){
    os << tree->root;
    return os;
}
