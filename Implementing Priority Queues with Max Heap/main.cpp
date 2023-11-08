#include<iostream>
#include <vector>
using namespace std;
struct Queue{
    int value, priority;
};

void swap(Queue *a, Queue *b){
    auto c = *a;
    *a = *b;
    *b = c;
}

class PriorityQueue{
    vector<Queue> queue;
    void heapifyUp(int num){
        while(num > 0){
            if(queue[num].priority > queue[(num - 1) / 2].priority){
                swap(queue[num], queue[(num - 1) / 2]);
                num = (num - 1) / 2;
                continue;
            }
            break;
        }
    }
    void heapifyDown(int n){
        int size = queue.size(), largest = n, left = 2 * n + 1, right = 2 * n + 2;
        while(true){
            if(left < size && queue[largest].priority < queue[left].priority){
                largest = left;
            }
            if(right < size & queue[largest].priority < queue[right].priority){
                largest = right;
            }
            if(n != largest){
                heapifyDown(largest);
            }
            return;
        }
    }
public:
    void enqueue(int num, int priority){
        queue.push_back({num, priority});
        heapifyUp((int)queue.size() - 1);
    }
    int dequeue(){
        int num = queue[0].value;
        swap(queue[0], queue[queue.size() - 1]);
        queue.pop_back();
        heapifyDown(0);
        return num;
    }
    bool exists(int num){
        for(Queue q: queue){
            if(q.value == num)
                return true;
        }
        return false;
    }
};

int main(){
    PriorityQueue priorityQueue;
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
                priorityQueue.enqueue(num, priority);
                cout << endl;
                break;
            case 2:
                cout << "Element with value " << priorityQueue.dequeue() << " dequeued." << endl << endl;
                break;
            case 3:
                cout << "Enter element to search: ";
                cin >> num;
                if(priorityQueue.exists(num)){
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