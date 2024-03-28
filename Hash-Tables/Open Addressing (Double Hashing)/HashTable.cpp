#include "HashTable.h"
#include <iostream>
#include <cmath>

//Constructor for Hashtable
HashTable::HashTable(): capacity(1), array(new Node*[1]), size(0), stack(new Stack()){
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

//Function for inserting the elements to a new hashtable from an array without increasing the size;
void HashTable::reInsert(pair<int, int> *newArray) {
    for(int i = 0; i < size; i++){
        int j = 1, index;
        //While loop will keep running until array[index] is empty for insertion
        while (array[(index = (hashFunction(newArray->first) + j++ * hashFunction2(newArray->first)) % capacity)]){}

        array[index] = new Node{newArray[i]};
    }
    delete newArray;
}

//Resize if it reaches the upper bound and lower bound of load factor
void HashTable::reHash() {
    if(size >= ceil(capacity * 0.75)) {
        //If the load factor reaches the upper bound ceiling, we will push the current capacity to the stack and
        //find new prime number for the capacity
        stack->push(capacity);

        pair<int, int>* newArray = getAllElements();

        while (!isPrime((capacity += 2))) {}

        array = (Node**) realloc(array, sizeof(Node*) * capacity);
        for(int i = 0; i < capacity; i++)
            array[i] = nullptr;

        reInsert(newArray);
    }else if (!stack->isEmpty() && size <= stack->peek()){
        //If the size is less than or equal to the previous prime number, we'll resize the capacity to the
        //previous prime number
        pair<int, int>* newArray = getAllElements();

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

int HashTable::hashFunction(int key) const {
    return key % capacity;
}

int HashTable::hashFunction2(int key) const {
    if(stack->isEmpty())
        stack->push(1);
    return stack->peek() - (key % stack->peek());
}


//Function for inserting elements
void HashTable::insertItem(pair<int, int>& keyValue) {
    reHash();
    int i = 1, index;
    //While loop will keep running until array[index] is empty for insertion
    while (array[(index = (hashFunction(keyValue.first) + i++ * hashFunction2(keyValue.first)) % capacity)]){}

    array[index] = new Node {keyValue};

    size++;
}

void HashTable::deleteItem(int key) {
    int i = 1, index = (hashFunction(key) + i * hashFunction2(key)) % capacity;
    //i <= capacity determines if we already scan all possible indexes given that each hash values are unique
    while(i <= capacity && array[index]){

        if(array[index]->keyValue.first == key) {
            int nextIndex = (hashFunction(key) + i++ * hashFunction(key)) % capacity;

            while (i <= capacity && array[nextIndex] && array[nextIndex]->keyValue.first == key) {
                array[index] = array[nextIndex];
                index = nextIndex;
                nextIndex = (hashFunction(key) + i++ * hashFunction2(key)) % capacity;
            }

            array[index] = nullptr;
            --size;
            reHash();
            return;
        }

        index = (hashFunction(key) + ++i * hashFunction2(key)) % capacity;
    }
    cout << "Element with key " << key << " doesn't exist\n";
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
    int i = 1, index = (hashFunction(key) + hashFunction2(i++)) % capacity;

    while(i <= capacity && array[index]){

        if(array[index]->keyValue.first == key) {
            node = array[index];
            break;
        }

        index = (hashFunction(key) + i++ * hashFunction2(key)) % capacity;
    }

    cout << (node ? to_string(node->keyValue.second): "(None) ") << '\n';
}
