#include "BTree.h"

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

void BTree::deleteKey(const int & key) {
    if(!root)
        return;

    if(getGroupNode(key)->deleteKey(key))
        size--;

    if(root->isEmpty())
        root = root->children[0];
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
