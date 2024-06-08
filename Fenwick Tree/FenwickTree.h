#ifndef FENWICKTREE_H
#define FENWICKTREE_H

class FenwickTree {
    int* array;

public:
    explicit FenwickTree(int size);

    FenwickTree & clearArray();

    ~FenwickTree();

};

#endif //FENWICKTREE_H
