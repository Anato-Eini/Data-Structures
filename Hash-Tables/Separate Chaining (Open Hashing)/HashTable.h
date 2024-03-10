#ifndef HASH_TABLES_HASHTABLE_H
#define HASH_TABLES_HASHTABLE_H

#include "AVLTree.h"
#include "Stack.h"
class HashTable {
    AVLTree** array;
    Stack* stack;
    int totalSize, size;
    [[nodiscard]] int hashFunction(int) const;
    void reHash();
    pair<int, int>* getAllElements();
    static bool isPrime(int);
public:
    HashTable() : size(1), array(new AVLTree*[1]), totalSize(0), stack(new Stack()) {
        for (int i = 0; i < 1; ++i)
            array[i] = new AVLTree();
        stack->push(1);
    }
    void insertItem(pair<int, int>&);
    void deleteItem(int);
    void print();
    void getValue(int key);
};

#endif //HASH_TABLES_HASHTABLE_H