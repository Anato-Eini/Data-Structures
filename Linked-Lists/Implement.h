#include <iostream>
#include <cmath>
#include <unordered_map>
#include "Abstract.h"
#include <map>
using namespace std;
class SinglyLinkedList: public SinglyList{
    SinglyNode* head, *tail; // Sentinels
    int size;
public:
    SinglyLinkedList(){
        head = new SinglyNode{0, nullptr};
        tail = new SinglyNode{0, nullptr};
        size = 0;
    }
    void addLast(int num){
        auto* n = new SinglyNode{num, nullptr};
        if(size == 0){
            head->next = n;
            tail->next = n;
        }else{
            tail->next->next = n;
            tail->next = n;
        }
        size++;
    }
    void addFirst(int num){
        SinglyNode* n = new SinglyNode{num, head->next};
        if(size == 0){
            head->next = n;
            tail->next = n;
        }else{
            n->next = head->next;
            head->next = n;
        }
        size++;
    }
    void flip(){
        if(size == 0){
            cout << "Empty List" << endl;
        }else{
            SinglyNode* prev = nullptr, *curr = head->next, *forw = head->next;
            while(forw){
                forw = forw->next;
                curr->next = prev;
                prev = curr;
                curr = forw;
            }
            SinglyNode* temp = head->next;
            head->next = tail->next;
            tail->next = temp;
        }
    }
    void removeNode(int num){
        if(size == 0){
            cout << "The list is empty" << endl;
            return;
        }else if(num < 0 || num >= size){
            cout << "Invalid Position" << endl;
        }else{
            SinglyNode* curr = head->next, *prev = head;
            int i = 0;
            while(i < num){
                prev = curr;
                curr = curr->next;
                i++;
            }
            prev->next = curr->next;
            if(curr == tail->next){
                tail->next = prev;
            }
            size--;
        }
    }

    void removeAt(int i) override {
        if(i < 1 || i > size) {
            cout << "Invalid position" << endl;
            return;
        }
        int a = 1;
        SinglyNode* curr = head->next, *prev = head;
        while(a < i){
            a++;
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
        size--;
    }

    //This function concatenates 2 Linkedlists
    void combineLists(SinglyLinkedList* linkedList){
        if(linkedList->size == 0){
            return;
        }else if(size == 0){
            size = linkedList->size;
            linkedList->size = 0;
            head = linkedList->head;
            tail = linkedList->tail;
        }else{
            tail->next->next = linkedList->head->next;
            tail->next = linkedList->tail->next;
        }
    }
    void rotateNodes(){
        SinglyNode* curr = head->next->next, *prev = head->next;
        while(curr){
            int temp = prev->elem;
            prev->elem = curr->elem;
            curr->elem = temp;
            prev = curr->next;
            if(!prev){
                break;
            }
            curr = prev->next;
        }
    }

    //Selection sort
    void sortList(){
        SinglyNode* curr = head->next;
        while (curr->next){
            SinglyNode* walker = curr->next, *temp = curr;
            while(walker){
                if(walker->elem < temp->elem){
                    temp = walker;
                }
                walker = walker->next;
            }
            if(temp != curr){
                int tempInt = temp->elem;
                temp->elem = curr->elem;
                curr->elem = tempInt;
            }
            curr = curr->next;
        }
    }
    void addAt(int num, int pos){
        if(pos > size + 1 || pos < 1){
            cout << "Invalid position" << endl;
            return;
        }
        int a = 1;
        SinglyNode* curr = head->next, *prev = head;
        while(a < pos){
            prev = curr;
            curr = curr->next;
            a++;
        }
        prev->next = new SinglyNode{num, curr};
    }
    void print(){
        if(size == 0){
            cout << "List is empty";
        }else{
            SinglyNode* curr = head->next;
            while(curr){
                cout << curr->elem << " ";
                curr = curr->next;
            }
            delete curr;
        }
        cout << endl;
    }
    int getSize(){
        return size;
    }

    int mostRepeatedElement() override {
        unordered_map<int, int> map;
        SinglyNode* curr = head->next;
        int mostRepeatedElement = curr->elem, frequency = 1;
        while (curr){
            map[curr->elem]++;
            if(map[curr->elem] > frequency){
                frequency = map[curr->elem];
                mostRepeatedElement = curr->elem;
            }
            curr = curr->next;
        }
        return mostRepeatedElement;
    }

    bool isPresent(int num) override {
        SinglyNode* curr = head->next;
        while (curr){
            if(curr->elem == num) return true;
            curr = curr->next;
        }
        return false;
    }

    ~SinglyLinkedList(){
        SinglyNode* curr = head, *deleter = head;
        while(curr){
            curr = curr->next;
            delete deleter;
            deleter = curr;
        }
        delete deleter;
        delete curr;
        delete tail;
        cout << "Linked list has been deleted.";
    }
};


class DoublyLinkedList: public DoublyList{
DoublyNode *head, *tail;
int size;
void addBetween(int num, DoublyNode* forward, DoublyNode* backward){
    auto* n = new DoublyNode{num, forward, backward};
    forward->prev = n;
    backward->next = n;
    size++;
}
public:
    DoublyLinkedList(){
        head = new DoublyNode;
        tail = new DoublyNode;
        head->next = tail;
        head->prev = nullptr;
        tail->prev = head;
        tail->next = nullptr;
        size = 0;
    }

    void addLast(int num) {
        addBetween(num, tail, tail->prev);
    }

    void addFirst(int num){
        addBetween(num, head->next, head);
    }

    int nthNodeFromLast(int num){
        int i = 1;
        DoublyNode* curr = tail->prev;
        while(i < num){
            curr = curr->prev;
            i++;
        }
        return curr->elem;
    }

    bool isPalindrome() override {
        DoublyNode* first = head->next, *last = tail->prev;
        while(first->next != last && first != last){
            if(first->elem != last->elem) return false;
            first = first->next;
            last = last->prev;
        }
        return true;
    }

    void print(){
        if(size != 0){
            DoublyNode *curr = head->next;
            while (curr != tail) {
                cout << curr->elem << " ";
                curr = curr->next;
            }
            cout << endl;
        }else
            cout << "List is empty" << endl;
    }
};