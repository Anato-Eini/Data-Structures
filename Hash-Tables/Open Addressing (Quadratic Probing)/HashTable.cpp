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
        int traverse = 0, hashValue = hashFunction(newArray[i].first), index;
        while(array[index]) {
            index = (hashValue + traverse * traverse) % size;
            traverse++;
        }
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

void HashTable::insertItem(pair<int, int>& keyValue) {
    reHash();
    int traverse = 0, hashValue = (hashFunction(keyValue.first) + traverse * traverse) % size;
    while (array[hashValue]) {
        hashValue = (hashValue + traverse * traverse) % size;
        traverse++;
    }
    array[hashValue] = new Node {keyValue};
    totalSize++;
}

void HashTable::deleteItem(int value) {
    int traverse = 0, index = (hashFunction(value) + traverse * traverse) % size, nextIndex;
    while(traverse < size && array[index]){
        if(array[index]->keyValue.first == value) {
            traverse++;
            nextIndex = (index + traverse * traverse) % size;
            while(traverse < size && array[nextIndex] && array[nextIndex]->keyValue.first == value){
                array[index] = array[nextIndex];
                index = nextIndex;
                traverse++;
                nextIndex = (nextIndex + traverse * traverse) % size;
            }
            array[index] = nullptr;
            --totalSize;
            reHash();
            return;
        }
        traverse++;
        index = (index + traverse * traverse) % size;
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
    int traverse = 0, hashValue = hashFunction(key);
    int index;
    while(traverse < size && array[index]){
        index = (hashValue + traverse * traverse) % size;
        if(array[index]->keyValue.first == key) {
            node = array[index];
            break;
        }
        traverse++;
    }
    cout << (node ? to_string(node->keyValue.second): "(None) ") << '\n';
}