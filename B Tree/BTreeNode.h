#ifndef DATA_STRUCTURES_BTREENODE_H
#define DATA_STRUCTURES_BTREENODE_H

#include <ostream>

class BTreeNode final {
    int size, capacity;

    int *elem;

    BTreeNode **children, *parent;

    bool isLeaf;

    void printInorder(std::ostream& os, BTreeNode* node);

    explicit BTreeNode(const int & capacity, const bool & isLeaf);

    explicit BTreeNode(const int & capacity, BTreeNode* parent, const bool & isLeaf);

    [[nodiscard]] BTreeNode* getChild(const int & key) const;

    [[nodiscard]] BTreeNode* removeChild(const int & index) const;

    void insert(const int & key);

    void insertFromChild(const int & key, BTreeNode * newChild);

    void moveHalf(BTreeNode* node);

    void splitNode();

    void deleteElem(const int & key);

    [[nodiscard]] bool isFull() const;

    [[nodiscard]] bool isEmpty() const;

    //Only applicable in deleting nodes
    [[nodiscard]] int getPosFromParent() const ;

    [[nodiscard]] std::pair<BTreeNode*, BTreeNode*> getSiblings() const ;

    [[nodiscard]] int getCapacity() const;

    int removeElem(const int & index);

    [[nodiscard]] int getSize() const;

    friend std::ostream& operator<<(std::ostream& os, BTreeNode* node);

    friend class BTree;
};

std::ostream& operator<<(std::ostream& os, BTreeNode* node);

#endif //DATA_STRUCTURES_BTREENODE_H
