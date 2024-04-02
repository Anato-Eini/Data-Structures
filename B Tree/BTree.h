#ifndef DATA_STRUCTURES_BTREE_H
#define DATA_STRUCTURES_BTREE_H
#include "BTreeNode.h"
class BTree {
    BTreeNode *root;
    int t;

public:
    explicit BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    void traverse() {
        if (root != nullptr)
            root->traverse();
    }

    void insertion(int k);

    void deletion(int k);
};


#endif //DATA_STRUCTURES_BTREE_H
