#include "HashTable.h"
#include <cmath>
bool HashTable::isPrime(int value) {
    for(int i = 2; i <= value / 2; i++)
        if(value % i == 0)
            return false;
    return true;
}

void HashTable::reHash() {
    if(totalSize >= ceil(size * 0.75)) {
        stack->push(size);
        pair<int, int>* newArray = getAllElements();
        while (!isPrime((size += 2))) {}
        array = (AVLTree**) realloc(array, sizeof(AVLTree*) * size);
        for (int i = 0; i < size; ++i)
            array[i] = new AVLTree();
        for (int i = 0; i < totalSize; ++i)
            array[hashFunction(newArray[i].first)]->insertNode(newArray[i]);
        delete newArray;
    }else if (!stack->isEmpty() && totalSize <= stack->peek()){
        pair<int, int>* newArray = getAllElements();
        size = stack->pop();
        array = (AVLTree**) realloc(array, sizeof(AVLTree*) * size);
        for(int i = 0; i < totalSize; ++i)
            array[hashFunction(newArray[i].first)]->insertNode(newArray[i]);
    }
}

pair<int, int>* HashTable::getAllElements() {
    auto* newArray = new pair<int, int>[totalSize];
    int index = 0;
    for (int i = 0; i < size; ++i)
        while (!array[i]->isEmpty())
            newArray[index++] = array[i]->removeRoot();
    return newArray;
}

int HashTable::hashFunction(int value) const {
    return value % size;
}

void HashTable::insertItem(pair<int, int>& keyValue) {
    array[hashFunction(keyValue.first)]->insertNode(keyValue);
    totalSize++;
    reHash();
}
void HashTable::deleteItem(int value) {
    if(array[hashFunction(value)]->searchNode(value)){
        array[hashFunction(value)]->deleteNode(value);
        totalSize--;
        reHash();
    }else
        cout << "Element does not exist\n";
}

void HashTable::print() {
    cout << "\nSize: " << totalSize << "\nCapacity: " << size << "\n\n";
    for (int i = 0; i < size; ++i) {
        cout << "table[" << i << "]";
        if(!(array[i]->isEmpty())) {
            cout << " --> ";
            array[i]->printTree();
        }else cout << '\n';
        cout << '\n';
    }
}

void HashTable::getValue(int key) {
    Node* node = array[hashFunction(key)]->searchNode(key);
    cout << (node ? to_string(node->pair.second ): "(None) ") << '\n';
}