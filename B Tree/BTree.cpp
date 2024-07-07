#include "BTree.h"
#include "iostream"

BTree::BTree(const int & maxChildren) : size(0), capacityElemNode(maxChildren + 1), root(nullptr) {}

void BTree::insert(const int & key) {
    if(!root) {
        root = new BTreeNode{capacityElemNode, true};
        root->insert(key);
    }else{
        getGroupNode(key)->insert(key);

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

//TODO Adjust Root when deleting
void BTree::deleteKey(const int & key) {
    BTreeNode* curr = getGroupNode(key);
    curr->deleteKey(key);
    size--;
}

bool BTree::search(const int & key) const
{
    return root ? getGroupNode(key)->keyPresent(key) : false;
}

std::ostream& operator<<(std::ostream& os, const BTree* tree){
    os << "Size: " << tree->size << "\n";
    os << tree->root << '\n';
    return os;
}

BTree::~BTree() {
    delete root;
}
