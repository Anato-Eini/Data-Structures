#include "abstract.h"
#include <iostream>
using namespace std;
class QueueList: public Queue{
    SinglyNode* sentinel, *dequeuer;
public:
    QueueList(){
        sentinel = new SinglyNode{nullptr, nullptr};
        dequeuer = new SinglyNode{nullptr, nullptr};
    }
    bool isEmpty() override{
        return !dequeuer->next;
    }
    void enqueue(Node* node) override{
        auto *newNode = new SinglyNode{node, nullptr};
        if(isEmpty()){
            sentinel->next = newNode;
            dequeuer->next = newNode;
        }else{
            sentinel->next->next = newNode;
            sentinel->next = newNode;
        }
    }
    Node* dequeue() override{
        if(!isEmpty()){
            Node* node = dequeuer->next->value;
            SinglyNode *deleter = dequeuer->next;
            dequeuer->next = dequeuer->next->next;
            delete deleter;
            return node;
        }else{
            cout << "Queue is empty" << endl;
            return nullptr;
        }
    }
};