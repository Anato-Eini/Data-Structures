#include "FenwickTree.h"

FenwickTree::FenwickTree(int size) : array(new int[size]){}

FenwickTree & FenwickTree::clearArray() {
    delete[] array;

    return *this;
}

FenwickTree::~FenwickTree(){
    delete[] array;
}