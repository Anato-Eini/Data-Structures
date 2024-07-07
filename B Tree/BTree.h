#ifndef DATA_STRUCTURES_BTREE_H
#define DATA_STRUCTURES_BTREE_H

#include <cstddef>
#include <ostream>
#include "BTreeNode.h"

class BTree {
    size_t size;

    BTreeNode* root;

    int capacityElemNode;

public:

    explicit BTree(const int & maxChildren);

    void insert(const int & key);

    void deleteKey(const int & key);

    [[nodiscard]] BTreeNode *getGroupNode(const int & key) const;

    ~BTree();

    [[nodiscard]] bool search(const int & key) const;

    friend std::ostream& operator<<(std::ostream& os, const BTree* tree);
};

std::ostream& operator<<(std::ostream& os, const BTree* tree);

#endif //DATA_STRUCTURES_BTREE_H
