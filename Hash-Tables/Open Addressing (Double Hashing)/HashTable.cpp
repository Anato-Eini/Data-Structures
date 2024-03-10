#include "HashTable.h"
#include <iostream>
#include <cmath>
bool HashTable::isPrime(int value) {
    for(int i = 2; i <= value / 2; i++)
        if(value % i == 0)
            return false;
    return true;
}

void HashTable::reInsert(pair<int, int> *newArray) {
    for(int i = 0; i < totalSize; i++){
        int j = 1,
            index = (hashFunction(newArray[i].first) + hashFunction2(j++, newArray[i].first)) % size;
        while(array[index])
            index = (hashFunction(newArray[i].first) + hashFunction2(j++, newArray[i].first)) % size;
        array[index] = new Node{newArray[i]};
    }
    delete newArray;
}

void HashTable::reHash() {
    if(totalSize >= ceil(size * 0.75)) {
        stack->push(size);
        pair<int, int>* newArray = getAllElements();
        while (!isPrime((size += 2))) {}
        array = (Node**) realloc(array, sizeof(Node*) * size);
        for(int i = 0; i < size; i++)
            array[i] = nullptr;
        reInsert(newArray);
    }else if (!stack->isEmpty() && totalSize <= stack->peek()){
        pair<int, int>* newArray = getAllElements();
        size = stack->pop();
        array = (Node**) realloc(array, sizeof(Node*) * size);
        for(int i = 0; i < size; i++)
            array[i] = nullptr;
        reInsert(newArray);
    }
}

pair<int, int>* HashTable::getAllElements() {
    auto* newArray = new pair<int, int>[totalSize];
    int index = 0;
    for (int i = 0; i < size; ++i)
        if(array[i])
            newArray[index++] = array[i]->keyValue;
    return newArray;
}

int HashTable::hashFunction(int value) const {
    return value % size;
}

int HashTable::hashFunction2(int i, int key) const {
    return i * (stack->peek() - (key % stack->peek()));
}

void HashTable::insertItem(pair<int, int>& keyValue) {
    reHash();
    int i = 1, index = (hashFunction(keyValue.first) + hashFunction2(i++, keyValue.first)) % size;
    while (array[index])
        index = (hashFunction(keyValue.first) + hashFunction2(i++, keyValue.first)) % size;
    array[index] = new Node {keyValue};
    totalSize++;
}

void HashTable::deleteItem(int value) {
    int index = hashFunction(value), traverse = 0;
    while(traverse < size && array[index]){
        if(array[index]->keyValue.first == value) {
            while (index + 1 < size && array[index + 1 ] && array[index + 1]->keyValue.first == value)
                array[index++] = array[index + 1];
            array[index] = nullptr;
            --totalSize;
            reHash();
            return;
        }
        index = (++traverse + index) % size;
    }
    cout << "Element with key " << value << " doesn't exist\n";
}

void HashTable::print() {
    cout << "\nSize: " << totalSize << "\nCapacity: " << size << "\n";
    for (int i = 0; i < size; ++i) {
        cout << "table[" << i << "] --> " + (array[i] ? "< " + to_string(array[i]->keyValue.first) + ", " +
            to_string(array[i]->keyValue.second ) + " >": "(none)");
        cout << '\n';
    }
}

void HashTable::getValue(int key) {
    Node* node = nullptr;
    int i = 1, index = (hashFunction(key) + hashFunction2(i++, key)) % size;
    while(i < size && array[index]){
        if(array[index]->keyValue.first == key) {
            node = array[index];
            break;
        }
        index = (hashFunction(key) + hashFunction2(i++, key)) % size;
    }
    cout << (node ? to_string(node->keyValue.second): "(None) ") << '\n';
}