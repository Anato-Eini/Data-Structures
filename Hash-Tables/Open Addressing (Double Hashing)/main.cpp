#include <iostream>
#include "HashTable.h"
using namespace std;
int main(){
    auto* hashTable = new HashTable();
    char operation;
    int number, number2;
    pair<int, int> p;
    do{
        cout << "Op: ";
        cin >> operation;
        switch (operation) {
            case '+':
                cin >> number >> number2;
                p = make_pair(number, number2);
                hashTable->insertItem(p);
                break;
            case '-':
                cin >> number;
                hashTable->deleteItem(number);
                break;
            case 'p':
                hashTable->print();
                break;
            case 'g':
                cin >> number;
                hashTable->getValue(number);
                break;
            default:
                break;
        }
    } while (operation == '+' || operation == '-' || operation == 'p' || operation == 'g');
    return 0;
}