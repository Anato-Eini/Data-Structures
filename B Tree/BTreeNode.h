#ifndef DATA_STRUCTURES_BTREENODE_H
#define DATA_STRUCTURES_BTREENODE_H

#include <ostream>

class BTreeNode {
    int size, capacity;
public:
    int* elem;
    BTreeNode **children, *parent;

    explicit BTreeNode(int capacity);
    explicit BTreeNode(int capacity, BTreeNode* parent);
    void insertElem(int key);
    void splitNode();
    bool isFull();
    int getCapacity() const;

    /// This will return a child of this node from a key.
    /// \param key
    /// \return child
    BTreeNode* getChild(int key);

    /// Remove an element by its index.
    /// \param index
    /// \return
    int removeElem(int index);

    /// Insert
    /// \param child
    void insertLastChild(BTreeNode* child);

    BTreeNode* removeChild(int index);

    int getSize() const;

    friend std::ostream& operator<<(std::ostream& os, BTreeNode* node);
};

std::ostream& operator<<(std::ostream& os, BTreeNode* node);

#endif //DATA_STRUCTURES_BTREENODE_H
