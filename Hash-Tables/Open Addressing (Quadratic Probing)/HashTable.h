#ifndef HASH_TABLES_HASHTABLE_H
#define HASH_TABLES_HASHTABLE_H
#include "Stack.h"
class HashTable {
    Stack* stack;
    Node **array;
    int size, capacity;
    [[nodiscard]] int hashFunction(int) const;
    void reHash();
    void reInsert(pair<int, int>*);
    pair<int, int>* getAllElements();
    static bool isPrime(int);
public:
    HashTable() : capacity(1), array(new Node*[1]), size(0), stack(new Stack()) {
        array[0] = nullptr;
        stack->push(1);
    }
    void insertItem(pair<int, int>&);
    void deleteItem(int);
    void print();
    void getValue(int key);
};
#endif //HASH_TABLES_HASHTABLE_H