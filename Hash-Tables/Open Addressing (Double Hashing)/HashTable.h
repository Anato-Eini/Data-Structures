#ifndef HASH_TABLES_HASHTABLE_H
#define HASH_TABLES_HASHTABLE_H
#include "Stack.h"
class HashTable {
    Stack* stack;//Used for traversing between prime numbers
    Node **array;//An array of pointers to nodes
    int size, capacity;//Current size and maximum capacity
    [[nodiscard]] int hashFunction(int) const;
    [[nodiscard]] int hashFunction2(int) const;
    void reHash();
    void reInsert(pair<int, int>*);
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