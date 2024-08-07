#ifndef DATA_STRUCTURES_BTREENODE_H
#define DATA_STRUCTURES_BTREENODE_H

#include <ostream>

class BTreeNode final {
    int size, capacity;

    int *elem;

    BTreeNode **children, *parent;

    bool isLeaf;

    static void printInorder(std::ostream& os, const BTreeNode* node, int && level);

    explicit BTreeNode(const int & capacity, const bool & isLeaf);

    explicit BTreeNode(const int & capacity, BTreeNode* parent, const bool & isLeaf);

    [[nodiscard]] BTreeNode* getChild(const int & key) const;

    void insert(const int & key);

    void insertFromChild(const int & key, BTreeNode * newChild);

    void moveHalf(BTreeNode* node);

    void splitNode();

    [[nodiscard]] static BTreeNode* getSuccessor(BTreeNode* node);

    [[nodiscard]] static BTreeNode* getPredecessor(BTreeNode* node);

    bool deleteKey(const int & key);

    [[nodiscard]] bool keyPresent(const int & key) const;

    /**
     * this node merges with its sibling
     * @param sibling
     */
    void mergeChild(BTreeNode* node);

    void mergeNode(BTreeNode* src, BTreeNode* dest);

    static void mergeContents(const BTreeNode * src, BTreeNode * dest, const int & elementIndex);

    /**
     * @warning Must be used for leaf nodes.
     */
    void underFlow();

    [[nodiscard]] bool isFull() const;

    [[nodiscard]] bool isEmpty() const;

    int removeElem(const int & index);

    ~BTreeNode();

    friend std::ostream& operator<<(std::ostream& os, BTreeNode* node);

    friend class BTree;
};

std::ostream& operator<<(std::ostream& os, BTreeNode *node);

#endif //DATA_STRUCTURES_BTREENODE_H
