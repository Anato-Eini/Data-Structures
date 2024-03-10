#ifndef HASH_TABLES_HASHTABLE_H
#define HASH_TABLES_HASHTABLE_H
#include "Stack.h"
class HashTable {
    Stack* stack;
    Node **array;
    int totalSize, size;
    [[nodiscard]] int hashFunction(int) const; // formula (hashFunction + hashFunction2) % size
    [[nodiscard]] int hashFunction2(int, int) const;
    void reHash();
    void reInsert(pair<int, int>*);
    pair<int, int>* getAllElements();
    static bool isPrime(int);
public:
    HashTable() : size(1), array(new Node*[1]), totalSize(0), stack(new Stack()) {
        array[0] = nullptr;
        stack->push(1);
    }
    void insertItem(pair<int, int>&);
    void deleteItem(int);
    void print();
    void getValue(int key);
};
#endif //HASH_TABLES_HASHTABLE_H