#ifndef DATA_STRUCTURES_BTREENODE_H
#define DATA_STRUCTURES_BTREENODE_H

#include <ostream>

class BTreeNode {
    int size, capacity;
    int* elem;
    BTreeNode **children, *parent;
    void printInorder(std::ostream& os, BTreeNode* node);
public:
    explicit BTreeNode(int capacity);
    explicit BTreeNode(int capacity, BTreeNode* parent);
    void insertNonLeaf(int key, BTreeNode* node);
    void moveHalf(BTreeNode* node);
    BTreeNode* getChild(int key);
    BTreeNode* removeChild(int index);
    void splitNode();
    bool isFull();
    bool isEmpty();
    int getCapacity() const;
    int removeElem(int index);
    int getSize() const;
    friend std::ostream& operator<<(std::ostream& os, BTreeNode* node);
    friend class BTree;
};

std::ostream& operator<<(std::ostream& os, BTreeNode* node);

#endif //DATA_STRUCTURES_BTREENODE_H
