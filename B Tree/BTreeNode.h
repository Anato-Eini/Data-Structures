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
    BTreeNode* getChild(int key);
    BTreeNode* removeChild(int index);
    void insertNonLeaf(int key, BTreeNode* node);
    void moveHalf(BTreeNode* node);
    void splitNode();
    void deleteElem(int key);
    bool isFull();
    bool isEmpty();
    int getPosFromParent();//Only applicable in deleting nodes
    std::pair<BTreeNode*, BTreeNode*> getSiblings();
    int getCapacity() const;
    int removeElem(int index);
    int getSize() const;
    friend std::ostream& operator<<(std::ostream& os, BTreeNode* node);
    friend class BTree;
};

std::ostream& operator<<(std::ostream& os, BTreeNode* node);

#endif //DATA_STRUCTURES_BTREENODE_H
