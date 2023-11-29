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
    bool isEmpty(){
        return !dequeuer->next;
    }
    void enqueue(Node* node){
        SinglyNode *newNode = new SinglyNode{node, nullptr};
        if(isEmpty()){
            sentinel->next = newNode;
            dequeuer->next = newNode;
        }else{
            sentinel->next->next = newNode;
            sentinel->next = newNode;
        }
    }
    Node* dequeue(){
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