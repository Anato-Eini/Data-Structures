#ifndef HASH_TABLES_HASHTABLE_H
#define HASH_TABLES_HASHTABLE_H
#include "Stack.h"
#include <vector>
class HashTable {
    Stack* stack; //Used for traversing between prime numbers
    Node **array; //An array of pointers to nodes
    int capacity, size; //Current size and maximum capacity
    [[nodiscard]] int hashFunction(int) const;
    [[nodiscard]] int hashFunction2(int) const;
    void reHash();
    void reInsert(vector<pair<int, int>>&);
    vector<pair<int, int>> getAllElements();
    static bool isPrime(int);
public:
    HashTable();
    void getValue(int);
    void insertItem(pair<int, int>&);
    void deleteItem(int);
    void print();
    ~HashTable();
};
#endif //HASH_TABLES_HASHTABLE_H