#ifndef DATA_STRUCTURES_BTREENODE_H
#define DATA_STRUCTURES_BTREENODE_H

#include <ostream>

class BTreeNode final {
    int size, capacity;

    int *elem;

    BTreeNode **children, *parent;

    bool isLeaf;

    static void printInorder(std::ostream& os, const BTreeNode* node);

    explicit BTreeNode(const int & capacity, const bool & isLeaf);

    explicit BTreeNode(const int & capacity, BTreeNode* parent, const bool & isLeaf);

    [[nodiscard]] BTreeNode* getChild(const int & key) const;

    [[nodiscard]] BTreeNode* removeChild(const int & index) const;

    void insert(const int & key);

    void insertFromChild(const int & key, BTreeNode * newChild);

    void moveHalf(BTreeNode* node);

    void splitNode();

    [[nodiscard]] static BTreeNode* getSuccessor(BTreeNode* node);

    [[nodiscard]] static BTreeNode* getPredecessor(BTreeNode* node);

    void deleteKey(const int & key);

    /**
     * this node merges with its sibling
     * @param sibling
     */
    void mergeChild(BTreeNode* node);

    static void mergeContents(const BTreeNode * src, BTreeNode * dest, const int & elementIndex);

    /**
     * @warning Must be used for leaf nodes.
     */
    void underFlow();

    [[nodiscard]] bool isFull() const;

    [[nodiscard]] bool isEmpty() const;

    int removeElem(const int & index);

    [[nodiscard]] int getSize() const;

    ~BTreeNode();

    friend std::ostream& operator<<(std::ostream& os, const BTreeNode* node);

    friend class BTree;
};

std::ostream& operator<<(std::ostream& os, const BTreeNode* node);

#endif //DATA_STRUCTURES_BTREENODE_H
