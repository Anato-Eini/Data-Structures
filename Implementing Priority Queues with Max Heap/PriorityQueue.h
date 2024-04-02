#include "abstract.h"
#include <vector>
using namespace std;
class PriorityQueue: public AbstractPriorityQueue{
    vector<Queue> queue;
    void swap(Queue *a, Queue *b){
        auto c = *a;
        *a = *b;
        *b = c;
    }
    void heapifyUp(int num){
        while(num > 0){
            if(queue[num].priority > queue[(num - 1) / 2].priority){
                swap(& queue[num], &queue[(num - 1) / 2]);
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
        heapifyUp((int)queue.capacity() - 1);
    }
    int dequeue(){
        int num = queue[0].value;
        swap(&queue[0], &queue[queue.capacity() - 1]);
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