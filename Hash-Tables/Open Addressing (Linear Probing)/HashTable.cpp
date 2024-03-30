#include "HashTable.h"
#include <iostream>
#include <cmath>

//Constructor for Hashtable
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

//Function for inserting the elements to a new hashtable from an array without increasing the capacity;
void HashTable::reInsert(pair<int, int> *newArray) {

    for(int i = 0; i < size; i++){
        int index = hashFunction(newArray[i].first);
        //While loop will keep running until array[index] is empty for insertion
        while(array[index])
            index = ++index % capacity;

        array[index] = new Node{newArray[i]};
    }

    delete newArray;
}

//Resize if it reaches the upper bound and lower bound of load factor
void HashTable::reHash() {
    if(size > ceil(capacity * 0.75)) {
        //If the load factor reaches the upper bound ceiling, we will push the current capacity to the stack and
        //find new prime number for the capacity
        stack->push(capacity);

        pair<int, int>* newArray = getAllElements();

        for(int i = 0; i < capacity; i++)
            delete array[i];

        while (!isPrime((capacity += 2))) {}

        array = (Node**) realloc(array, sizeof(Node*) * capacity);
        for(int i = 0; i < capacity; i++)
            array[i] = nullptr;

        reInsert(newArray);
    }else if (!stack->isEmpty() && size <= stack->peek()){
        //If the capacity is less than or equal to the previous prime number, we'll resize the capacity to the
        //previous prime number
        pair<int, int>* newArray = getAllElements();

        for(int i = 0; i < capacity; i++)
            delete array[i];

        capacity = stack->pop();

        array = (Node**) realloc(array, sizeof(Node*) * capacity);
        for(int i = 0; i < capacity; i++)
            array[i] = nullptr;

        reInsert(newArray);
    }
}

//Function for getting all the elements of the hashtable and return an array of pairs
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

//Function for inserting elements
void HashTable::insertItem(pair<int, int>& keyValue) {
    int index = hashFunction(keyValue.first);

    size++;
    reHash();

    while (array[index]) {
        if(array[index]->keyValue.first == keyValue.first){
            array[index]->keyValue = keyValue;

            return;
        }
        index = ++index % capacity;
    }
    array[index] = new Node {keyValue};
    size++;
}

//Function for deleting elements by key
void HashTable::deleteItem(int value) {
    int index = hashFunction(value), traverse = 0;
    while(traverse < capacity && array[index]){
        if(array[index]->keyValue.first == value) {
            while (index + 1 < capacity && array[index + 1 ] && array[index + 1]->keyValue.first == value)
                array[index++] = array[index + 1];
            array[index] = nullptr;
            --size;
            reHash();
            return;
        }
        index = (++traverse + index) % capacity;
    }
    cout << "Element with key " << value << " doesn't exist\n";
}

//Print the HashTable
void HashTable::print() {
    cout << "\nSize: " << size << "\nCapacity: " << capacity << "\n";
    for (int i = 0; i < capacity; ++i) {
        cout << "table[" << i << "] --> " + (array[i] ? "< " + to_string(array[i]->keyValue.first) + ", " +
            to_string(array[i]->keyValue.second ) + " >": "(none)");
        cout << '\n';
    }
}

//Function for getting the value by key
void HashTable::getValue(int key) {
    Node* node = nullptr;
    int traverse = 0;
    int index = hashFunction(key);
    while(traverse < capacity && array[index]){
        if(array[index]->keyValue.first == key) {
            node = array[index];
            break;
        }
        index = (++traverse + index) % capacity;
    }
    cout << (node ? to_string(node->keyValue.second): "(None) ") << '\n';
}

HashTable::~HashTable() {
    delete stack;
    for(int i = 0; i < capacity; i++)
        delete array[i];

    delete[] array;
}