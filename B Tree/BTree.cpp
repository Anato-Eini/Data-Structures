#include "BTree.h"

BTree::BTree(int maxChildren) : size(0), capacityElemNode(maxChildren + 1), root(nullptr) {}

BTreeNode *BTree::createNode(BTreeNode *parent) {
    return new BTreeNode(capacityElemNode, parent);
}

void BTree::insert(int key) {
    if(!root) {
        root = new BTreeNode{capacityElemNode};
        root->insertElem(key);
    }else{
        BTreeNode* curr = root;
        while(true){
            BTreeNode* child = curr->getChild(key);
            if(!child) {
                curr->insertElem(key);
                break;
            }else
                curr = child;
        }
        while(root->parent)
            root = root->parent;
    }
}
