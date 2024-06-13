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

    explicit BTree(const int & maxChildren);

    void insert(const int & key);

    void deleteKey(const int & key);

    [[nodiscard]] BTreeNode *getGroupNode(const int & key) const;

    ~BTree();

    void clearTreeHelper(const BTreeNode* node);

    void clearTree();

    friend std::ostream& operator<<(std::ostream& os, const BTree* tree);
};

std::ostream& operator<<(std::ostream& os, const BTree* tree);

#endif //DATA_STRUCTURES_BTREE_H
