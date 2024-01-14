#include <iostream>
#include "MinHeap.h"
using namespace std;
int main () {
    MinHeap* minHeap = new MinHeapOperations();
    int operation,input, elementPeeked;
    do {
        cout << "Enter operation: ";
        cin >> operation;

        switch (operation) {
            case 1:
                cout << "Enter element to add: ";
                cin >> input;
                minHeap->insert(input);
                break;
            case 2:
                elementPeeked = minHeap->peek();
                if (elementPeeked != -1) {
                    cout << "Minimum element is: " << elementPeeked << endl;
                }else {
                    cout << endl << "Heap is empty" << endl;
                }
                break;
            case 3:
                cout << "Enter element to delete: ";
                cin >> input;
                minHeap->deleteNode(input);
                cout << endl;
                minHeap->printHeapTree();
                break;
            case 4:
                cout << "Minimum element removed is: " << minHeap->removeMin() << endl << endl;
                minHeap->printHeapTree();
                break;
            default:
                minHeap->printHeapTree();
                break;
        }
        cout << endl;
    }while(operation != 0);
    minHeap->printHeapTree();
}