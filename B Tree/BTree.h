#ifndef DATA_STRUCTURES_BTREE_H
#define DATA_STRUCTURES_BTREE_H

#include <cstddef>
#include <ostream>
#include "BTreeNode.h"

class BTree {
    size_t size;
    int capacityElemNode;
public:
    BTreeNode* root;
    explicit BTree(int maxChildren);
    void insert(int key);

    friend std::ostream& operator<<(std::ostream& os, BTree* tree);
};

std::ostream& operator<<(std::ostream& os, BTree* tree);

#endif //DATA_STRUCTURES_BTREE_H
