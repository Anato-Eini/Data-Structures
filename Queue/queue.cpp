#include <iostream>
#include<cstdlib>
using namespace std;
struct Node{
	int data;
	Node* next;
};
class LinkedList{
	int size;
	Node *head;
	Node *tail;
public:
	LinkedList(){
		size = 0;
		head = nullptr;
		tail = nullptr;
	}
	void add(int data){
        Node *node = new Node{data, nullptr};
		if(!head){
			head = node;
			tail = node;
		} else{
			tail->next = node;
			tail = node;
		}
		size++;
	}
	
	void addLast(int num){
		add(num);
	}

	void addFirst(int num){
		if(!head){
			add(num);
			return;
		}
		Node* node = new Node{num, head};
		head = node;
		size++;
	}

	int removeFirst(){
		if(size == 0){
			return -1;
		}
		int tempInt = head->data;
		Node* temp = head;
		head = head->next;
		free(temp);
		size--;
		return tempInt;
	}
	int get(int position){
		if(size == 0){
            return -1;
        }
		Node* curr = head;
        int a = 1;
        while(a != position){
            curr = curr->next;
            a++;
        }
		return curr->data;
	}

	int _size(){
		return size;
	}

	void print(){
		Node *p = head;
		while(p){
			cout << p->data << "->";
			p = p->next;
		}
		cout << endl;
		free(p);
	}
};

class Queue{
	LinkedList* list;
public:
	Queue(){
		list = new LinkedList();
	}
	void enqueue(int num){
		list->addLast(num);
	}
	int dequeue(){
		return list->removeFirst();
	}
	int peek(){
		return list->get(1);
	}
	int size() {
		return list->_size();
	}
	bool isEmpty() {
		return size() == 0;
	}
	void print() {
		list->print();
	}
	
};

int main(){
	Queue* queue = new Queue();
	char op;
	int num;
	while(true){
		cout << "Enter operation: ";
		cin >> op;
		switch(op){
			case 'e':
				cin >> num;
				queue->enqueue(num);
				break;
			case 'd':
				cout << (queue->isEmpty()? "Queue is empty!\n" : "Removed " + to_string(queue->dequeue()) + "\n");
				break;
			case 'p':
				cout << (queue->isEmpty()? "Queue is empty!\n" : "Front of the queue is " + to_string(queue->peek()) + "\n");
				break;
			case 's':
				cout << "Size of queue is " << queue->size() << endl;
				break;
		}
		if(op == 'x' || op == 'X'){
			cout << "Exiting";
			break;
		}
	}
    return 0;
}
