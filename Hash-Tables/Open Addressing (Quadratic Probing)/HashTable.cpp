#include "HashTable.h"
#include <iostream>
#include <cmath>

HashTable::HashTable() : capacity(1), array(new Node*[1]), size(0), stack(new Stack()) {
    array[0] = nullptr;
    stack->push(1);
}

//Function for finding prime. We will skip prime number 2 for now
bool HashTable::isPrime(int value) {
    for(int i = 2; i <= value / 2; i++)
        if(value % i == 0)
            return false;
    return true;
}

void HashTable::reInsert(pair<int, int> *newArray) {
    for(int i = 0; i < size; i++){
        int traverse = 0, hashValue = hashFunction(newArray[i].first), index;
        while(array[index]) {
            index = (hashValue + traverse * traverse) % capacity;
            traverse++;
        }
        array[index] = new Node{newArray[i]};
    }
    delete newArray;
}

void HashTable::reHash() {
    if(size >= ceil(capacity * 0.75)) {
        stack->push(capacity);
        pair<int, int>* newArray = getAllElements();
        while (!isPrime((capacity += 2))) {}
        array = (Node**) realloc(array, sizeof(Node*) * capacity);
        for(int i = 0; i < capacity; i++)
            array[i] = nullptr;
        reInsert(newArray);
    }else if (!stack->isEmpty() && size <= stack->peek()){
        pair<int, int>* newArray = getAllElements();
        capacity = stack->pop();
        array = (Node**) realloc(array, sizeof(Node*) * capacity);
        for(int i = 0; i < capacity; i++)
            array[i] = nullptr;
        reInsert(newArray);
    }
}

pair<int, int>* HashTable::getAllElements() {
    auto* newArray = new pair<int, int>[size];
    int index = 0;
    for (int i = 0; i < capacity; ++i)
        if(array[i])
            newArray[index++] = array[i]->keyValue;
    return newArray;
}

int HashTable::hashFunction(int value) const {
    return value % capacity;
}

void HashTable::insertItem(pair<int, int>& keyValue) {
    reHash();
    int traverse = 0, hashValue = (hashFunction(keyValue.first) + traverse * traverse) % capacity;
    while (array[hashValue]) {
        hashValue = (hashValue + traverse * traverse) % capacity;
        traverse++;
    }
    array[hashValue] = new Node {keyValue};
    size++;
}

void HashTable::deleteItem(int value) {
    int traverse = 0, index = (hashFunction(value) + traverse * traverse) % capacity, nextIndex;
    while(traverse < capacity && array[index]){
        if(array[index]->keyValue.first == value) {
            traverse++;
            nextIndex = (index + traverse * traverse) % capacity;
            while(traverse < capacity && array[nextIndex] && array[nextIndex]->keyValue.first == value){
                array[index] = array[nextIndex];
                index = nextIndex;
                traverse++;
                nextIndex = (nextIndex + traverse * traverse) % capacity;
            }
            array[index] = nullptr;
            --size;
            reHash();
            return;
        }
        traverse++;
        index = (index + traverse * traverse) % capacity;
    }
    cout << "Element with key " << value << " doesn't exist\n";
}

void HashTable::print() {
    cout << "\nSize: " << size << "\nCapacity: " << capacity << "\n";
    for (int i = 0; i < capacity; ++i) {
        cout << "table[" << i << "] --> " + (array[i] ? "< " + to_string(array[i]->keyValue.first) + ", " +
                                                        to_string(array[i]->keyValue.second ) + " >": "(none)");
        cout << '\n';
    }
}

void HashTable::getValue(int key) {
    Node* node = nullptr;
    int traverse = 0, hashValue = hashFunction(key);
    int index;
    while(traverse < capacity && array[index]){
        index = (hashValue + traverse * traverse) % capacity;
        if(array[index]->keyValue.first == key) {
            node = array[index];
            break;
        }
        traverse++;
    }
    cout << (node ? to_string(node->keyValue.second): "(None) ") << '\n';
}