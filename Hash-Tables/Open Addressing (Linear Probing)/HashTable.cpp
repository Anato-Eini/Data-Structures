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
void HashTable::reInsert(vector<pair<int, int>> &newArray) {

    for(pair<int, int> p: newArray){
        int i = 0;
        int index;
        //While loop will keep running until array[index] is empty for insertion
        while(array[(index = (hashFunction(p.first) + i++) % capacity)]){}

        array[index] = new Node{p};
    }

}

//Resize if it reaches the upper bound and lower bound of load factor
void HashTable::reHash() {
    if(size >= ceil(capacity * 0.75)) {
        //If the load factor reaches the upper bound ceiling, we will push the current capacity to the stack and
        //find new prime number for the capacity
        stack->push(capacity);

        vector<pair<int, int>> newArray = getAllElements();

        for(int i = 0; i < capacity; i++)
            delete array[i];

        while (!isPrime((capacity += 2))) {}

        array = (Node**) realloc(array, sizeof(Node*) * capacity);
        for(int i = 0; i < capacity; i++)
            array[i] = nullptr;

        reInsert(newArray);
    }else if (!stack->isEmpty() && size <= ceil(stack->peek() * 0.75)){
        //If the capacity is less than or equal to the previous prime number, we'll resize the capacity to the
        //previous prime number
        vector<pair<int, int>> newArray = getAllElements();

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
vector<pair<int, int>> HashTable::getAllElements() {
    vector<pair<int, int>> elements;

    for (int i = 0; i < capacity; ++i)
        if(array[i])
            elements.push_back(array[i]->keyValue);

    return elements;
}

int HashTable::hashFunction(int value) const {
    return value % capacity;
}

//Function for inserting elements
void HashTable::insertItem(pair<int, int>& keyValue) {
    int i = 0;
    int index = (hashFunction(keyValue.first) + i) % capacity;

    size++;
    reHash();

    while (array[index]) {

        if(array[index]->keyValue.first == keyValue.first){
            array[index]->keyValue = keyValue;
            size--;
            reHash();
            return;
        }

        index = (hashFunction(keyValue.first) + ++i) % capacity;
    }

    array[index] = new Node {keyValue};
}

//Function for deleting elements by key
void HashTable::deleteItem(int value) {
    int i = 0;
    int index = (hashFunction(value) + i) % capacity;

    while(i < capacity){

        if(array[index] && array[index]->keyValue.first == value) {
            delete array[index];
            array[index] = nullptr;
            --size;
            reHash();
            return;
        }

        index = (hashFunction(value) + ++i) % capacity;
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
    int i = 0;
    int index = (hashFunction(key) + i) % capacity;

    while(i < capacity){

        if(array[index] && array[index]->keyValue.first == key) {
            cout << "The value of key " << key << " is " << array[index]->keyValue.second << '\n';
            return;
        }

        index = (hashFunction(key) + ++i) % capacity;
    }

    cout << "Element with key " << key << " doesn't exist\n";
}

HashTable::~HashTable() {
    delete stack;
    for(int i = 0; i < capacity; i++)
        delete array[i];

    delete[] array;
}