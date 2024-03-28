#include "HashTable.h"
#include <iostream>
#include <cmath>
#include <cassert>
bool HashTable::isPrime(int value) {
    for(int i = 2; i <= value / 2; i++)
        if(value % i == 0)
            return false;
    return true;
}

void HashTable::reInsert(pair<int, int> *newArray) {
    for(int i = 0; i < totalSize; i++){
        int j = 1, index;
        while (array[(index = (hashFunction(newArray->first) + j++ * hashFunction2(newArray->first)) % size)]){}
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

int HashTable::hashFunction(int key) const {
    return key % size;
}

int HashTable::hashFunction2(int key) const {
    if(stack->isEmpty())
        stack->push(1);
    return stack->peek() - (key % stack->peek());
}

void HashTable::insertItem(pair<int, int>& keyValue) {
    reHash();
    int i = 1, index;
    while (array[(index = (hashFunction(keyValue.first) + i++ * hashFunction2(keyValue.first)) % size)]){}
    array[index] = new Node {keyValue};
    totalSize++;
}

void HashTable::deleteItem(int key) {
    int i = 1, index = (hashFunction(key) + i * hashFunction2(key)) % size;
    while(i <= size && array[index]){
        if(array[index]->keyValue.first == key) {
            int nextIndex = (hashFunction(key) + i++ * hashFunction(key)) % size;
            while (i <= size && array[nextIndex] && array[nextIndex]->keyValue.first == key) {
                array[index] = array[nextIndex];
                index = nextIndex;
                nextIndex = (hashFunction(key) + i++ * hashFunction2(key)) % size;
            }
            array[index] = nullptr;
            --totalSize;
            reHash();
            return;
        }
        index = (hashFunction(key) + ++i * hashFunction2(key)) % size;
    }
    cout << "Element with key " << key << " doesn't exist\n";
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
    int i = 1, index = (hashFunction(key) + hashFunction2(i++)) % size;
    while(i <= size && array[index]){
        if(array[index]->keyValue.first == key) {
            node = array[index];
            break;
        }
        index = (hashFunction(key) + i++ * hashFunction2(key)) % size;
    }
    cout << (node ? to_string(node->keyValue.second): "(None) ") << '\n';
}