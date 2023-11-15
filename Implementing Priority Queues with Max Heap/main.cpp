#include<iostream>
#include "PriorityQueue.h"

using namespace std;

int main(){
    AbstractPriorityQueue* priorityQueue = new PriorityQueue();
    int input, num, priority;
    do{
        cout << "Enter operation: ";
        cin >> input;
        switch (input) {
            case 1:
                cout << "Enter element to add: ";
                cin >> num;
                cout << "Enter element priority: ";
                cin >> priority;
                priorityQueue->enqueue(num, priority);
                cout << endl;
                break;
            case 2:
                cout << "Element with value " << priorityQueue->dequeue() << " dequeued." << endl << endl;
                break;
            case 3:
                cout << "Enter element to search: ";
                cin >> num;
                if(priorityQueue->exists(num)){
                    cout << num << " exists in the queue." << endl << endl;
                }else
                    cout << num << " does not exist in the queue." << endl << endl;
                break;
            case 4:
                cout << "Program stopped.";
                break;
        }
    } while (input != 4);
    return 0;
}