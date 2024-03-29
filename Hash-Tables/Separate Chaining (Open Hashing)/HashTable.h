#ifndef HASH_TABLES_HASHTABLE_H
#define HASH_TABLES_HASHTABLE_H

#include "AVLTree.h"
#include "Stack.h"
class HashTable {
    AVLTree** array; //An array of pointers to nodes
    Stack* stack; //Used for traversing between prime numbers
    int size, capacity; //Current size and maximum capacity
    [[nodiscard]] int hashFunction(int) const;
    void reHash();
    pair<int, int>* getAllElements();
    static bool isPrime(int);
public:
    HashTable();
    void insertItem(pair<int, int>&);
    void deleteItem(int);
    void print();
    void getValue(int key);
};

#endif //HASH_TABLES_HASHTABLE_H