#ifndef SEGMENTTREE_H
#define SEGMENTTREE_H

#include <ostream>

#include "vector"

#include "Node.h"

class SegmentTree final {
    Node * root;
    int size{};

    static void clearTreeHelper(const Node* node);

    static Node* generateTreeHelper(int array[], int left, int right);

    static Node* generateTreeHelper(std::vector<int>& array, int left, int right);

    static void print(std::ostream & ostream, bool isLeft, std::string string, const Node* node);

    static int queryHelper(const Node* node, const int & left, const int & right, int rangeLeft, int rangeRight);

public:
    SegmentTree();

    SegmentTree & generateTree(int array[], const int & n);

    SegmentTree & generateTree(std::vector<int> & array);

    SegmentTree & clearTree();

    /**
     * @param left starting index
     * @param right end index
     * @return sum from starting index up to end index
     */
    [[nodiscard]]int query(const int & left, const int & right) const;

    ~SegmentTree();

    friend std::ostream & operator<<(std::ostream & ostream, const SegmentTree* tree);
};

std::ostream & operator<<(std::ostream & ostream, const SegmentTree* tree);

#endif //SEGMENTTREE_H
